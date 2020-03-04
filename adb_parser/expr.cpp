/*
 * 
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
 * 
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 * 
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 * 
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 * 
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "expr.h"


char*Expr::str;
char*Expr::initial_arg;
Expr::status Expr::state;

/*
 * Number of elements in array
 */
#define numbel(x) (sizeof(x) / sizeof((x)[0]))

/*
 * Unary prefixes which present radix
 */
#define RADIX16    "0x"
#define RADIX2     "0b"

/*
 * Unary operations
 */
#define ULOGNOT    71   /* !    */
#define UMINUS     72   /* -    */
#define UNOT       73   /* ~    */
#define UPLUS      74   /* +    */
#define U2POW      75   /* :    */
#define U2POW_ALT  76   /* POW2 */
#define ULOG2      77   /* '    */
#define ULOG2_ALT  78   /* LOG2 */
#define SWAP32     79   /* SWAP32 */
#define SWAP16     80   /* SWAP16 */

/*
 * Binary operations
 */
#define AND       1     /* &&     */
#define BIT_AND   2     /* &      */
#define BIT_OR    3     /* |      */
#define BIT_XOR   4     /* ^      */
#define DIVID     5     /* /      */
#define EQ        6     /* ==     */
#define GREAT     7     /* >      */
#define GREAT_EQ  8     /* >=     */
#define LESS      9     /* <      */
#define LESS_EQ   10    /* <=     */
#define MINUS     11    /* -      */
#define MODUL     12    /* %      */
#define MULT      13    /* *      */
#define NOTEQ     14    /* !=     */
#define OR        15    /* ||     */
#define PLUS      16    /* +      */
#define SHIFT_L   17    /* <<     */
#define SHIFT_R   18    /* >>     */
#define XOR       19    /* log.xor*/

/*
 * Other token types
 */
#define VALUE     103   /* Name or constant */
#define EXPR_OK   0     /* Expression getted successfully */

/*
 * Miscellaneous constant
 */
#ifdef IGNORE
#undef IGNORE
#endif
#define IGNORE    " \t\n\r" /* Ignore in parsing */
#define HIGH_PRI  1
#define LOW_PRI   9

/*
 * Unary operations. Priority not applicable,
 * all unary operations have same priority.
 */
static Expr::table unar[] = {
    { U2POW,     0, ":"      },
    { U2POW_ALT, 0, "POW2"   },
    { ULOG2,     0, "'"      },
    { ULOG2_ALT, 0, "LOG2"   },
    { ULOGNOT,   0, "!"      },
    { UMINUS,    0, "-"      },
    { UNOT,      0, "~"      },
    { UPLUS,     0, "+"      },
    { SWAP32,    0, "SWAP32" },
    { SWAP16,    0, "SWAP16" }
};
static int Lunar = numbel(unar);

/*
 * Binary operations.
 */
static Expr::table binar[] = {
    { MODUL,    1, "%"        },
    { MULT,     1, "*"        },
    { DIVID,    1, "/"        },
    { PLUS,     2, "+"        },
    { MINUS,    2, "-"        },
    { SHIFT_L,  3, "<<"       },
    { SHIFT_L,  3, "SHIFT_L"  },
    { SHIFT_R,  3, ">>"       },
    { SHIFT_R,  3, "SHIFT_R"  },
    { GREAT,    4, ">"        },
    { GREAT,    4, "GREAT"    },
    { GREAT_EQ, 4, ">="       },
    { GREAT_EQ, 4, "GREAT_EQ" },
    { LESS,     4, "<"        },
    { LESS,     4, "LESS"     },
    { LESS_EQ,  4, "<="       },
    { LESS_EQ,  4, "LESS_EQ"  },
    { EQ,       5, "=="       },
    { EQ,       5, "EQ"       },
    { NOTEQ,    5, "!="       },
    { NOTEQ,    5, "NOTEQ"    },
    { BIT_AND,  6, "&"        },
    { BIT_AND,  6, "BIT_AND"  },
    { BIT_OR,   7, "|"        },
    { BIT_OR,   7, "BIT_OR"   },
    { BIT_XOR,  7, "^"        },
    { BIT_XOR,  7, "BIT_XOR"  },
    { AND,      8, "&&"       },
    { AND,      8, "AND"      },
    { OR,       9, "||"       },
    { OR,       9, "OR"       },
    { XOR,      9, "XOR"      }
};
static int Lbinar = numbel(binar);


/********************************************************
* routine:     expr
*
* description:
*     Main routine for expression evaluation. Do some interface
*     functions and call binary operation evaluation with lowest
*     priority.
*
* arguments:
*     pstr            pointer to string which contains expression to
*                     evaluation. After successfully evaluation expr
*                     moves this pointer to end of expression (first
*                     unparsed character).
*     result          pointer to unsigned long to put result of expression.
*     dr              default radix for numbers.
*     ErrorRep        pointer to callbeck routine for error reporting.
*                     arguments - like printf.
*
* return code:
*     >0              length of evaluated expression.
*     <0              error code, one of following:
*        ERR_RPAR_EXP   - Right parentheses expected.
*        ERR_VALUE_EXP  - Value expected.
*        ERR_BIN_EXP    - Binary operation expected. It is a normal situation
*                         on experssion end.
*        ERR_DIV_ZERO   - Divide zero attempt.
*        ERR_BAD_NUMBER - Bad constant syntax.
*        ERR_BAD_NAME   - Name not found in symbol table.
*
********************************************************/
int Expr::expr(char **pstr, u_int64_t *result)
{
    int rc = 0;
    int len = 0;

    str         = *pstr;
    initial_arg = *pstr;
    state       = was_bin;

    /* Operation(s) found, do really evaluation. */
    rc = GetBinaryOp(result, LOW_PRI);
    if (rc == EXPR_OK  ||
        rc == ERR_BIN_EXP) {
        len = (int)(str - *pstr);
        *pstr = str;
        return len;
    } else {
        return rc;
    }
}


/********************************************************
* routine:     GetBinaryOp
*
* description:
*     Executes binary operations with current priority level.
*     If priority great then constant HIGH_PRI, calls itself
*     recursive with decreased priority to get  operands for
*     expression, otherwise calls GetUnaryOp to get operands.
*
* arguments:
*     val             Pointer to unsigned long where result of
*                     operation will be placed.
*     priority        Execute operation only with this priority
*
* return code:
*     EXPR_OK         Binary operation was calculated successfully
*     ERR_DIV_ZERO    Zero divide attempt
*     otherwise       Error code from GetUnaryOp (see)
*
* side effects:
*     Attention, deep recursion...
*
********************************************************/
int Expr::GetBinaryOp(u_int64_t *val, int priority)
{
    char      *str_old;
    int rc = 0;
    int i = 0;
    u_int64_t left = 0;
    u_int64_t right = 0;
    token curr;
    status stat_old;

    rc = priority > HIGH_PRI ? GetBinaryOp(&left, priority - 1) :
         GetUnaryOp(&left);
    if (rc != EXPR_OK) {
        return rc;
    }

    for (;;) {
        str_old = str;
        stat_old = state;
        GetToken(&curr);
        for (i = 0; i < Lbinar; i++) {
            if (binar[i].type == curr.type  &&  binar[i].pri == priority) {
                rc = priority > HIGH_PRI ? GetBinaryOp(&right, priority - 1) :
                     GetUnaryOp(&right);
                if (rc != EXPR_OK) {
                    str = str_old;
                    state = stat_old;
                    return rc;
                }

                switch (curr.type)
                {
                case MODUL:
                    if (right == 0) {
                        ErrorReport("Zero modulo attempt.\n");
                        return ERR_DIV_ZERO;
                    }
                    left = left % right;
                    break;

                case MULT:
                    left = left * right;
                    break;

                case DIVID:
                    if (right == 0) {
                        ErrorReport("Zero divide attempt.\n");
                        return ERR_DIV_ZERO;
                    }
                    left = left / right;
                    break;

                case PLUS:
                    left = left + right;
                    break;

                case MINUS:
                    left = left - right;
                    break;

                case SHIFT_L:
                    left = (left << (int)right);
                    break;

                case SHIFT_R:
                    left = (left >> (int)right);
                    break;

                case GREAT:
                    left = (left > right);
                    break;

                case GREAT_EQ:
                    left = (left >= right);
                    break;

                case LESS:
                    left = (left < right);
                    break;

                case LESS_EQ:
                    left = (left <= right);
                    break;

                case EQ:
                    left = (left == right);
                    break;

                case NOTEQ:
                    left = (left != right);
                    break;

                case BIT_AND:
                    left = left & right;
                    break;

                case BIT_OR:
                    left = left | right;
                    break;

                case BIT_XOR:
                    left = left ^ right;
                    break;

                case AND:
                    left = (left && right);
                    break;

                case OR:
                    left = (left || right);
                    break;

                case XOR:
                    left = (left && !right)  ||  (!left && right);
                    break;
                }
                break;
            }
        }
        if (i >= Lbinar) {
            UngetToken(curr);
            *val = left;
            return EXPR_OK;
        }
    }
}


/********************************************************
* routine:     GetUnaryOp
*
* description:
*     Executes unary operations.
*
* arguments:
*     val             Pointer to unsigned long where result of
*                     operation will be placed.
*
* return code:
*     EXPR_OK         Binary operation was calculated successfully
*     otherwise       Error code from GetToken (see)
*
********************************************************/
int Expr::GetUnaryOp(u_int64_t *val)
{
    int rc, unary_op;
    u_int64_t tmp = 0;
    u_int64_t tmp1 = 0;
    token curr;
    u_int64_t tmpVal = *val;

    GetToken(&curr);
    switch (unary_op = curr.type)
    {
    case U2POW:
    case U2POW_ALT:
    case ULOG2:
    case ULOG2_ALT:
    case ULOGNOT:
    case UMINUS:
    case UNOT:
    case UPLUS:
    case SWAP32:
    case SWAP16:
        /*
         * Was unary operation - retrieve more token.
         */
        rc = GetUnaryOp(val);
        if (rc != EXPR_OK) {
            return rc;
        }

        /* OK, execute required unary operation. */
        switch (unary_op)
        {
        case U2POW_ALT:
        case U2POW:
            *val = (u_int64_t)1 << (int)(*val);
            break;

        case ULOG2_ALT:
        case ULOG2:
            if (*val != 0) {
                for (tmp = 1, tmp1 = 0; tmp < *val; tmp = tmp << 1)
                    ++tmp1;
                *val = tmp1;
            }
            break;

        case ULOGNOT:
            *val = !(*val);
            break;

        case UMINUS:
            *val = (u_int64_t)(-((int64_t)(*val)));
            break;

        case UNOT:
            *val = ~(*val);
            break;

        case UPLUS:
            break;

        case SWAP32:
            *val = ((tmpVal & 0x000000FFUL) << 24)  |
                   ((tmpVal & 0x0000FF00UL) << 8)   |
                   ((tmpVal & 0x00FF0000UL) >> 8)   |
                   ((tmpVal & 0xFF000000UL) >> 24);
            break;

        case SWAP16:
            *val = ((tmpVal & 0xFF000000U) >> 8) |
                   ((tmpVal & 0x00FF0000U) << 8) |
                   ((tmpVal & 0x0000FF00U) >> 8) |
                   ((tmpVal & 0x000000FFU) << 8);
            break;
        }
        break;

    case VALUE:
        /*
         * Unary operation is omitted. Assume no unary operations.
         */
        *val = curr.value;
        break;

    default:
        /*
         * Here we expect only unary operation or value.
         * Something other - error. Bring error code witch
         * present by curr.type to caller.
         */
        UngetToken(curr);
        return curr.type;
    }

    return EXPR_OK;
}

/********************************************************
* routine:     GetToken
*
* description:
*     Gets next token from static pointer str.
*
* arguments:
*     pt              pointer to token. GetToken fills in all
*                     field by this pointer.
*
* return code:
*     None
*
* side effects:
*     1. May insrease pointer str (if token getted successfully).
*     2. May change static variable state (if token getted
*        successfully and state was changed).
*
********************************************************/
void Expr::GetToken(token *pt)
{
    char *old_str, *p;
    int i, rc, oplen;

    /*
     * Skip all leading ignorable characters
     */
    do {
        old_str = str;
        for (p = (char*)IGNORE; *p; p++)
            if (*str == *p) {
                str++;
            }
    } while ((old_str != str) && *str);

    pt->beg = str;
    pt->sta = state;
    switch (state)
    {
    case was_bin:
        /*
         * Was binary operation (or begin of experssion).
         * Unary operation expected.
         * Try find unary operation with maximal length.
         */
        oplen = 0;
        for (i = 0; i < Lunar; i++)
            if (!strncmp(unar[i].st, str, strlen(unar[i].st))) {
                if ((int)strlen(unar[i].st) > oplen) {
                    pt->type = unar[i].type;
                    oplen = strlen(unar[i].st);
                }
            }
        if (oplen) {
            /* Unary operation found. */
            str += oplen;
            state = was_bin;
            return;
        }

        /*
         * Unary operation not found.
         * Number or name expected.
         */
        if (!strncmp(str, RADIX16, strlen(RADIX16))
            ||  !strncmp(str, RADIX2, strlen(RADIX2))) {
            /*
             * Number expected.
             */
            rc = GetNumb(&pt->value);
            if (rc == EXPR_OK) {
                pt->type = VALUE;
            } else {
                pt->type = rc;
                return;
            }
        } else if (valid_name(*str) || valid_digit(*str, def_radix)) {
            /*
             * Name or number expected.
             */
            rc = GetName(&pt->value);
            if (rc == EXPR_OK) {
                pt->type = VALUE;
            } else {
                pt->type = rc;
                return;
            }
        } else if (*str == '(') {
            /*
             * Parentheses expression expected.
             */
            old_str = str++;
            rc = GetBinaryOp(&pt->value, LOW_PRI);
            if (rc == EXPR_OK) {
                pt->type = VALUE;
            } else {
                pt->type = rc;
                return;
            }
            if (*str == ')') {
                str++;
            } else {
                /* error, right parentheses expected. */
                pt->type = ERR_RPAR_EXP;
                if (*str) {
                    ErrorReport("Instead of\"" + std::string(str) + "\" right parentheses expected.\n");
                } else {
                    ErrorReport("Unexpected end in expression \"" + std::string(initial_arg) + "\" - right parentheses expected.\n");
                }
                str = old_str;
                return;
            }
        } else {
            /* error, number or name or unary operation expected. */
            pt->type = ERR_VALUE_EXP;
            if (*str) {
                ErrorReport("Instead of \"" + std::string(str) + "\" value or unary operation expected.\n");
            } else {
                ErrorReport("Unexpected end in expression \"" + std::string(initial_arg) + "\" - value or unary operation expected.\n");
            }
            return;
        }
        state = was_opr;
        return;

    case was_opr:
        /*
         * Was operand. Binary operation expected
         * Try find binary operation with maximal length.
         */
        oplen = 0;
        for (i = 0; i < Lbinar; i++)
            if (!strncmp(binar[i].st, str, strlen(binar[i].st))) {
                if ((int)strlen(binar[i].st) > oplen) {
                    oplen = strlen(binar[i].st);
                    pt->type = binar[i].type;
                }
            }
        if (oplen) {
            /* Binary operation found. */
            str += oplen;
            state = was_bin;
            return;
        }

        /* error, binary operation expected. */
        pt->type = ERR_BIN_EXP;
        return;
    }
}

/********************************************************
* routine:     UngetToken
*
* description:
*     Ungets previously getted token.
*
* arguments:
*     t               token to unget
*
* return code:
*     None
*
* side effects:
*     1. Restores str as was before token.
*     2. Restores state as was before token
*
********************************************************/
void Expr::UngetToken(token t)
{
    str = t.beg;
    state = t.sta;
}


/********************************************************
* routine:     GetNumb
*
* description:
*     Gets constant from str. First character of constant may
*     be special value to set radix (% for 2, & for 10 and $ for 16).
*
* arguments:
*     val              pointer to unsigned long to put constatnt value.
*
* return code:
*     EXPR_OK        - Constant OK
*     ERR_BAD_NUMBER - Bad constant syntax
*
* side effects:
*     Moves pointer str to end of constant.
*
********************************************************/
int Expr::GetNumb(u_int64_t *val)
{
    int radix = def_radix;

    if (!strncmp(str, RADIX16, strlen(RADIX16))) {
        radix = 16;
        str += strlen(RADIX16);
    } else if (!strncmp(str, RADIX2, strlen(RADIX2))) {
        radix = 2;
        str += strlen(RADIX2);
    }

    if (!valid_digit(*str, radix)) {
        ErrorReport("\"" + std::string(str) + "\" -- bad constant syntax.\n");
        return ERR_BAD_NUMBER;
    }

    *val = 0L;
    for (; valid_digit(*str, radix); str++)
        *val = *val * radix +
               ( ('a' <= *str && *str <= 'f') ? *str - 'a' + 10 :
                                                ( ('A' <= *str && *str <= 'F') ? *str - 'A' + 10 :
                                                                                 *str - '0'));

    return EXPR_OK;
}


/********************************************************
* routine:     GetName
*
* description:
*     Gets name from str and tries to find it in symbol
*     table. If name looks as constant in "def_radix",
*     interprets it as constant rather than name.
*
* arguments:
*     val          - pointer to unsigned long to put value
*
* return code:
*     EXPR_OK      - Name successfully found in symbol table and
*                    substituted by its value.
*     ERR_BAD_NAME - Name not found in symbol table.
*
* side effects:
*     Moves pointer str to end of name.
*
********************************************************/
#define MAXNAM 100
int Expr::GetName(u_int64_t *val)
{
    static char name[MAXNAM];
    char        *p, *old_str;

    old_str = str;     /* Save start name position. */

    /* Get name. */
    for (p = name; valid_name(*str);)
        *p++ = *str++;
    *p++ = '\0';

    /* Try interpret as constant first. */
    for (p = name; *p; p++)
        if (!valid_digit(*p, def_radix)) {
            break;
        }
    if (!*p) {
        /*
         * All characters of this name are valid digit in radix
         * "def_radix". So, interpret this name as constant.
         */
        str = old_str;       /* unget name to common buffer */
        return GetNumb(val); /* and get it as number        */
    }

    /* Retrieve name from symbol table. */
    /* -------------------------------- */
    if (ResolveName(name, val) == 0) {
        return EXPR_OK;
    } else {
        ErrorReport("Symbolic name \"" +  std::string(name) + "\" not resolved.\n");
        return ERR_BAD_NAME;
    }
}

/********************************************************
* routine:     valid_name
*
* description:
*     Function checks if character may be part of symbolic name.
*
* arguments:
*     ch           - character to check
*
* return code:
*     0 - character is not valid
*     1 - character is valid
*
********************************************************/
int Expr::valid_name(char ch)
{
    return (ch == '_' || ch == '.') ? 1 : isalnum(ch);
}

/********************************************************
* routine:     valid_digit
*
* description:
*     Check validity of digit ch (in ASCII, ex. '1') according to radix 'radix'.
*
* arguments:
*     ch           - character to check
*     radix        - radix
*
* return code:
*     0 - character is not valid
*     1 - character is valid
*
********************************************************/
int Expr::valid_digit(char ch, int radix)
{
    switch (radix)
    {
    case 2:
        return (ch == '0' || ch == '1') ? 1 : 0;

    case 10:
        return isdigit(ch);

    case 16:
        return isxdigit(ch);

    default:
        return 1;
    }
}


/********************************************************
* routine:     ErrorReport
*
* description:
*     Error reporting
*
* arguments:
*     like printf
*
********************************************************/
void Expr::ErrorReport(const std::string& msg)
{

    Error(msg);
}

