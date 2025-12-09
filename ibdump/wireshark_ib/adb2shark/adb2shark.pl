#!/usr/bin/perl -w

# Note how here-docs in this file are parsed to use the specified tab-length. They are sensitive
# to the tabbing you use when updating the code. If you edit or create new here-docs, use ONLY
# 3 spaces as tab fields. Do not use the tab character or any other number of spaces as this
# will screw up formatting of the generated code.
# 
# With no attributes to guide us, all fields smaller than 64 bits are assumed to be unsigned integers
# and displayed in hexadecimal base. All other fields are assumed to be (not necessarily null-
# terminated) strings.
# 
# We assume that fields which are not bit-fields (fields whose size in bits is divisible by 8) are
# located on a byte-aligned border. Code generation for fields for which this is not the case is
# unsupported.

use strict;
use CSP;
use Switch;

# general constants for convenient code-updates
my $tb = 3;           # tab size to use in code
my $version = "v0.1"; # current version of the script

my $csp; # data structure that will hold that contents of the CSP file
my $ow_all = 0;   # will be set if user wishes to overwrite all files
my $verbosity = 0;   # verbosity level to use

# various values for names used throughout the generated program (assigned values are defaults)
my $proto_abbrev = "infiniband"; # protocol abbreviation to use when generating the code
my $def_tree = "tree";           # name for tree argument passed to function
my $tvb = "tvb";                 # name for tvb argument passed to function
my $offset = "offset";           # name for offset pointer passed as argument to the function
my $pinfo = "pinfo";             # packet info struct passed as argument to the function

# these variables hold different parts of the code while generation is in progress
my @field_vars;   # field id variables (all of type int)
my @subtree_vars; # subtree id variables (all of type int)
my %local_vars;   # variables local to the parsing function, saved as (<type> => <list of vars of that type>)
my @local_code;   # body of the parsing function
my @reg_code;     # registration code (elements for the hf_register_info array)

my $bit_offset = 0;       # keeps track of offsets in bits, for use with fields that are smaller than 1 byte in size
my $prev_field = "node";  # used later for better formatting the output .c file
my $uniq = "";            # unique name that will be part of the field/subtree variable names



# error function for internal use
sub perish {
   my $msg = shift || "Some error occured";
   my $errnum = shift || 1;

   print STDERR "-E- $msg\n";
   exit $errnum;
}


# ------------------ PARSING FUNCTIONS -----------------------------



sub parseAttr {
   my $field = shift;
   my %attributes;

   while ($field->{attr} =~ /([^=]+)=(.+?)( |$)/g) {
      $attributes{$1} = $2;
   }

   return %attributes;
}

# receives a field pointer and decides whether it represents a subtree or a specific
# field of the packet
sub isSubtree {
   my $field = shift;
   my %attrs = parseAttr($field);

   if (  defined($field->{array}) ||             # is an array
         defined($attrs{attr_field_type}) ||   # has a field_type listed, so definetely a field
         not $field->{subnode}) {              # is a leaf
      return 0;
   } else {
      return 1;
   }
}


# receives a point to a leaf field (not a subnode), and decides on what WS type should be used for it
sub decideType {
   my $field = shift;
   my $len = $field->{fsize};
   my %attrs = parseAttr($field);

   # if the field_type attribute is defined, decide according to it
   if (defined($attrs{attr_field_type})) {
      switch ($attrs{attr_field_type}) {
         case "i64" {
            return "FT_UINT64";
         }
         case "string" {
            return "FT_STRING";
         }
      }
   }

   # if attributes indicate this is an array, display as raw byte string
   if (defined($field->{array})) {
      return "FT_BYTES";
   }

   if ($len <= 8) {
      return "FT_UINT8";
   } elsif ($len > 8 && $len <= 16) {
      return "FT_UINT16";
   } elsif ($len > 16 && $len <= 24) {
      return "FT_UINT24";
   } elsif ($len > 24 && $len <= 32) {
      return "FT_UINT32";
   } elsif ($len > 32 && $len <= 64) {
      return "FT_UINT64";
   } else {
      return "FT_STRING";
   }
}


# receives a pointer to a leaf field (not a subnode), and generates code for its display in Wireshark
sub generateForField {
   my $field = shift;
   my $tree = shift || $def_tree;              # which tree node to use as root in the generated dissection tree
   my $tree_prefix = shift || $proto_abbrev;   # subtree prefix so far
   my $indent = shift || "";                   # indent value used for pretty-printing during generation
   my $pre_name = $proto_abbrev . (($uniq eq "") ? "" : "_") . 
                  $uniq;                       # prefix used for creating unique names

   my $name_oc = $field->{fname};   # shorthand for field name in original case
   my $name = lc($name_oc);         # shorthand for field name in lowercase

   print $indent, "- Parsing field: $name_oc\n" if $verbosity;

   if ($field->{reserved}) {
      push(@local_code, " "x$tb  . "local_offset += " . ($field->{fsize} / 8) .
                                   ";  /* skip reserved field */");
      return;
   }

   my $type = decideType($field);
   my $base = ($type eq "FT_STRING") ? "BASE_NONE" : "BASE_HEX"; 

   push(@field_vars, "hf_"."$pre_name"."_"."$name");   # add a global variable for the field

   if (($field->{fsize} % 8) == 0 && not $bit_offset) {   # for none-bitfields
      push(@local_code, " "x$tb  . "proto_tree_add_item($tree, " . 
                                   "hf_"."$pre_name"."_"."$name, " .
                                   "$tvb, local_offset, ".($field->{fsize} / 8).", FALSE); " .
                                   "local_offset += ".($field->{fsize} / 8).";");   # display this field in the Wireshark window
   } else {    # for bit-fields only
      push(@local_code, " "x$tb  . "proto_tree_add_bits_item($tree, " . 
                                   "hf_"."$pre_name"."_"."$name, " .
                                   "$tvb, local_offset*8" . ($bit_offset ? " + $bit_offset, " : ", ") .
                                   "$field->{fsize}, FALSE);");   # display this field in the Wireshark window
      $bit_offset = $bit_offset + $field->{fsize};
      if ($bit_offset >= 8) {
         my $prev_code = pop(@local_code);   # fix generated code to advance local_offset
         push(@local_code,  $prev_code . " local_offset += " . int($bit_offset/8) . ";");
         $bit_offset = $bit_offset % 8;
      }
   }

   push(@reg_code, "  "x$tb  . "{ &hf_"."$pre_name"."_"."$name,\n" .
                   "   "x$tb . "{ \"$name_oc\", \"$tree_prefix.$name\",\n" .
                   "   "x$tb . "$type, $base, NULL, 0x0,\n" .
                   "   "x$tb . "\"$field->{descr}\", HFILL }\n" .
                   "  "x$tb  . "}");

}

# receives a field that points to a subnode, and generates dissector code for the subtree rooted at this node
sub generateForNode {
   my $field = shift;
   my $tree = shift || $def_tree;              # which tree node to use as root in the generated dissection tree
   my $tree_prefix = shift || $proto_abbrev;   # subtree prefix so far
   my $indent = shift || "";                   # indent value used for pretty-printing during generation
   my $pre_name = $proto_abbrev . (($uniq eq "") ? "" : "_") . 
                  $uniq;                       # prefix used for creating unique names

   my $name_oc = $field->{fname};   # shorthand for field name in original case
   $name_oc =~ s/_block_element//i;  # filter out extraneous parts of the name
   my $name = lc($name_oc);         # shorthand for field name in lowercase

   print $indent, "+ Parsing node: $name_oc\n" if $verbosity;

   push(@field_vars, "hf_"."$pre_name"."_$name");   # add a global variable for the subtree field
   push(@subtree_vars, "ett_"."$pre_name"."_$name");    # add a global variable for the subtree identifier

   push(@{$local_vars{"proto_item*"}}, "$name"."_item");    # add a local variable for the item we will create to add the subtree to
   push(@{$local_vars{"proto_tree*"}}, "$name"."_subtree"); # add a local variable for the subtree we will create

   push(@local_code, " "x$tb  . "$name"."_item = proto_tree_add_item($tree,\n" . 
                     "  "x$tb . "hf_"."$pre_name"."_"."$name, " .
                                "$tvb, local_offset, ".($field->{fsize} / 8).", FALSE);");   # item registration for the subtree node
   push(@local_code, " "x$tb  . "$name"."_subtree = proto_item_add_subtree($name"."_item, " .
                                "ett_"."$pre_name"."$name);");

   push(@reg_code, "  "x$tb  . "{ &hf_"."$pre_name"."_"."$name,\n" .
                   "   "x$tb . "{ \"$name_oc\", \"$tree_prefix.$name\",\n" .
                   "   "x$tb . "FT_NONE, BASE_NONE, NULL, 0x0,\n" .
                   "   "x$tb . "\"$field->{subnode}->{descr}\", HFILL }\n" .
                   "  "x$tb  . "}");

   # recursively generate code for subtrees, generate actual display code for fields using generateForField
   foreach my $subfield (@{$field->{subnode}->{fields}}) {
      if (isSubtree($subfield)) { 
         push(@local_code, "") if ($prev_field eq "leaf");
         $prev_field = "node";
         generateForNode($subfield, "$name"."_subtree", "$tree_prefix.$name", "$indent   ");
      } else {
         push(@local_code, "") if ($prev_field eq "node");
         $prev_field = "leaf";
         generateForField($subfield, "$name"."_subtree", "$tree_prefix.$name", "$indent   ");
      }
   }
   
}

# receives a packet field and generates a dissector .c file for it
sub generateForPacket {
   my $root = shift;
   my $packet = $root->{fname};
   my $filenm = "dissect_" . lc($packet) . ".c";

   # reset all global variables to their initial states, so we don't accidentally use
   # state left over from the last packet
   undef(@field_vars); undef(@subtree_vars); undef(@local_code);
   undef(@reg_code);   undef(%local_vars);
   $bit_offset = 0;     
   $prev_field = "node";

   if (-e $filenm && not $ow_all) {
      while (1) {    # we'll break out of this later
         print "File $filenm already exists. Overwrite? (yes/no/all) ";
         chomp(my $answer = <STDIN>);
         if ($answer =~ /^y(e|es){0,1}$/i) {
            last;
         } elsif ($answer =~ /^no{0,1}$/i) {
            return;
         } elsif ($answer =~ /^a(l|ll){0,1}$/i) {
            $ow_all = 1;
            last;
         }
      }
      print "\n" if $verbosity;
   }

   open(PACKET_FILE, "> $filenm") || perish "Could not open $filenm: $!";
   print "Writing to file: $filenm\n";
   print "-----------------" . "-" x length($filenm) . "\n" if $verbosity;

   generateForNode($root);

   my @time = localtime;
   my $sec   = $time[0];
   my $min   = $time[1];
   my $hr    = $time[2];
   my $day   = $time[3];
   my $month = $time[4];
   my $year  = $time[5] + 1900;

   print PACKET_FILE <<END;
/* $filenm
 * Routines for $proto_abbrev dissection of $packet packet
 * Copyright 200x, YOUR_NAME <YOUR_EMAIL_ADDRESS>
 *
 * \$Id\$
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald\@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This file has been auto-generated by adb2shark $version on $day/$month/$year, $hr:$min:$sec.
 * adb2shark is the creation of Slava Koyfman, (c) Mellanox Technologies Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

#include <epan/packet.h>
#include <epan/prefs.h>


END

   print PACKET_FILE "/* Initialize the registered fields */\n";
   foreach my $var (@field_vars) {
      print PACKET_FILE "static int $var = -1;\n";
   }

   print PACKET_FILE "\n";

   print PACKET_FILE "/* Initialize the subtree pointers */\n";
   foreach my $var (@subtree_vars) {
      print PACKET_FILE "static int $var = -1;\n";
   }

   print PACKET_FILE <<END;


/* Code to parse and display the $packet packet */
static int parse_$packet(tvbuff_t *$tvb, packet_info *$pinfo, proto_tree *$def_tree, int *$offset)
{
END

   # output local variables
   foreach my $type (keys %local_vars) {
      my @vars = @{$local_vars{$type}};

      if ($type =~ /[^\*]*([*]+)[^\*]*/) {   # tidy up so pointer-types are declared correctly and neatly
         my $pointer = $1;                         # save number of indirections
         $type =~ s/([^\*]*)[*]*([^\*]*)/$1$2/;    # get rid of them
   
         for (my $i = 0; $i < scalar(@vars); $i += 1) {
            $vars[$i] = "$pointer" . $vars[$i];
         }
      }

      print PACKET_FILE " "x$tb . "$type " . join(", ", @vars) . ";\n";
   }

   print PACKET_FILE " "x$tb . "int local_offset = *$offset;\n";  # output this manually since if we add it to $local_vars
                                                                  # we can't control the order in which it is declared in the .c file

   # I'd love to keep printing this out directly to file as before, but we want to stick to the
   # indent requested by $tb, and not hardcode it into the script
   my $indent = " "x$tb;
   my $packet_size = int($root->{fsize} / 8);  # size of packet we're parsing in bytes, for use inside the here-doc below
   (my $out = <<END) =~ s/   /$indent/g;

   /* make sure there isn't less data in the tvb than the size of the packet */
   if (tvb_length($tvb) - local_offset < $packet_size) {
      return 0;
   }

   col_append_str($pinfo->cinfo, COL_INFO, " ($packet)");

END

   print PACKET_FILE $out;
   print PACKET_FILE join("\n", @local_code) . "\n";

   ($out = <<END) =~ s/   /$indent/g;

   *$offset = local_offset;
   return $packet_size;
}


void proto_register_$proto_abbrev(void)
{

   /* Setup list of header fields */
   static hf_register_info hf[] = {
END

   print PACKET_FILE $out;
   print PACKET_FILE join(",\n", @reg_code);
   print PACKET_FILE "\n";

   ($out = <<END) =~ s/   /$indent/g;
   };

   /* Setup subtree array */
   static gint *ett[] = {
END

   print PACKET_FILE $out;

   for (my $i = 0; $i < scalar(@subtree_vars); $i = $i + 1) {
      $subtree_vars[$i] = "  "x$tb . "&$subtree_vars[$i]";
   }
   print PACKET_FILE join(",\n", @subtree_vars);
   print PACKET_FILE "\n";

   ($out = <<END) =~ s/   /$indent/g;
   };

   /* If we were creating a dissector for a protocol, this is where the protocol
      and field/subtree registration would go */
}
END

   print PACKET_FILE $out;

   close(PACKET_FILE);
}



# ------------------ UTILITY FUNCTIONS -----------------------------



# fields in the csp file are arranged in little-endian order. this function receives
# a node pointer, and modifies all fields under it to be in big-endian order
sub toBigEndian {
   my $node = shift;
   my $offset = 0;
   my $fields = \ @{$node->{fields}};
   my @bigEndian;
   my @dword;

   if (exists($node->{b_endian})) { # already in big-endian order...
      return;
   }

   $node->{b_endian} = 1;

   foreach my $field (@$fields) {
      unshift(@dword, $field);
      $offset += $field->{fsize};
      unless ($offset % 32) {
         push(@bigEndian, @dword);
         undef(@dword); # empty out the dword
         $offset = 0;
      }
      toBigEndian($field->{subnode}) if $field->{subnode};
   }

   push(@bigEndian, reverse(@dword));  # for anything remaining
   @$fields = @bigEndian;   # put the big-endian ordered fields in place of the old ones
}


# searches for a packet by name in the csp structure and returns pointer to the appropriate field
sub findPacket {
   my $name = shift;
   my $root = "";

   foreach my $field (@{$csp->{main_node}->{fields}}) {
      if ($field->{fname} =~ /^$name/i) {
         $root = $field;
         last;
      }
   }

   return $root;
}


sub displayHelp {
   print <<END;
adb2shark $version
adb2shark generates skeleton-code for Wireshark dissectors based on packet information from an
ADABE database.

Usage: adb2shark.pl [options] [packet,[packet,...]]

Options:
   -f <file>      Read database from given CSP file. If not given, adb2shark will try reading
                  from the file packets_st.csp in the current directory.
   -i <ident>     Will insert the identifier <ident> into global field and subtree registration
                  variable names in the generated source file. This is useful, for example, to
                  make it easier to identify families of related packets in the code.
   -p <abbrev>    Use <abbrev> as the protocol abbreviation in the generated source file. If not
                  specified, default is "infiniband".
   -r <name>      Use <name> as the name for the proto_tree* argument passed to the parsing
                  function. Default is "tree".
   -t <name>      Use <name> as the name for the tvbuff_t* argument passed to the parsing
                  function. Default is "tvb".
   -o <name>      Use <name> as the name for the offset argument passed to the parsing
                  function. Default is "offset".
   -n <name>      Use <name> as the name for the packet_info* argument passed to the parsing
                  function. Default is "pinfo".
   -tab <n>       Use <n> spaces for tabbing in the generated code file. Default is 3.
   -v             Run in verbose mode. Prints extra progress information to the screen.
   -h             Display this help screen.

Packet:
   Specify a comma-delimited list of packets to generate source file for. If not provided,
   source files will be generated for all packets in the database. (Caution: This can create
   a lot of new .c files in the current directory.)
END
}


# parses command line for the options
sub getOptions {
   my %options = ("pkts_file" => "packets_st.csp");   # holds various execution options

   for (my $i = 0; $i <= $#ARGV; $i = $i + 1) {
      if ($ARGV[$i] =~ /^-([a-zA-Z]+)$/) {   # an option
         switch ($1) {
            case "h" {       # help
               displayHelp;
               exit 0;
            }
            case "f" {   # csp file
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify csp file after -f option."; }
               else { $options{"pkts_file"} = $ARGV[$i]; }
            }
            case "i" {   # identifier
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify identifier after -i option."; }
               elsif ($ARGV[$i] !~ /^\w+$/) { perish "Identifier may contain only alphanumeric characters and underscores.";}
               else { $uniq = $ARGV[$i]; }
            }
            case "p" {   # protocol abbreviation
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify protocol abbreviation after -p option."; }
               elsif ($ARGV[$i] !~ /^[_a-z0-9]+$/) { perish "Protocol abbreviation may contain only lowercase alphanumeric characters and underscores.";}
               else { $proto_abbrev = lc($ARGV[$i]); }
            }
            case "r" {   # tree arg name
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify name for tree argument after -r option."; }
               elsif ($ARGV[$i] !~ /^\w+$/) { perish "Tree argument name may contain only alphanumeric characters and underscores.";}
               else { $def_tree = $ARGV[$i]; }
            }
            case "t" {   # tvb arg name
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify name for tvb argument after -t option."; }
               elsif ($ARGV[$i] !~ /^\w+$/) { perish "tvb argument name may contain only alphanumeric characters and underscores.";}
               else { $tvb = $ARGV[$i]; }
            }
            case "o" {   # offset arg name
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify name for offset argument after -t option."; }
               elsif ($ARGV[$i] !~ /^\w+$/) { perish "Offset argument name may contain only alphanumeric characters and underscores.";}
               else { $offset = $ARGV[$i]; }
            }
            case "n" {   # pinfo arg name
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify name for packet info argument after -t option."; }
               elsif ($ARGV[$i] !~ /^\w+$/) { perish "Packet info argument name may contain only alphanumeric characters and underscores.";}
               else { $pinfo = $ARGV[$i]; }
            }
            case "tab" {   # tab size
               $i += 1;
               if ($i > $#ARGV) { perish "Must specify tab size after -tab option."; }
               elsif ($ARGV[$i] !~ /^\d+$/ || $ARGV[$i] <= 0) { perish "Tab size must be a positive integer.";}
               else { $tb = $ARGV[$i]; }
            }
            case "v" {   # tab size
               $verbosity = 1;
            }
            else {
               perish "Unrecognized option: $ARGV[$i]. Use adb2shark.pl -h to display the help screen.";
            }
         }
      } elsif ($i == $#ARGV) {               # last argument - packet list?
         @{$options{"packets"}} = split(/,/, $ARGV[$i]);
      } else {
         perish "Unrecognized argument: $ARGV[$i]. Use adb2shark.pl -h to display the help screen.";
      }
   }

   return %options;
}



# ------------------ MAIN -----------------------------



my %options = getOptions;

# initialize data structure from csp file
$csp = CSP->new($options{"pkts_file"}) if (-e $options{"pkts_file"})
   || perish "The file \"$options{pkts_file}\" does not exist.";

if (exists($options{"packets"})) {
   foreach my $packet_name (@{$options{"packets"}}) {
      $packet_name =~ s/^\s*//;  # remove leading whitespaces
      $packet_name =~ s/\s*$//;  # remove trailing whitespaces
      my $packet = findPacket($packet_name) || perish "$packet_name: No such packet.";
      toBigEndian($packet->{subnode});
      generateForPacket($packet);
      print "\n" if $verbosity;
   }
} else { # generate for all packets
   foreach my $packet (@{$csp->{main_node}->{fields}}) {
      next unless $packet->{subnode};  # skip fields that don't represent packets
      toBigEndian($packet->{subnode});
      generateForPacket($packet);
      print "\n" if $verbosity;
   }
}
