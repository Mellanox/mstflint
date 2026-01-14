# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#######################################################
#
# AdbParser.py
# Python implementation of the Class AdbParser
# Created on:      23-Mar-2020 8:00:00 AM
# Original author: talve
#
#######################################################
import xml.etree.ElementTree as ET
import resourceparse_lib.utils.constants as CONST
from resourceparse_lib.utils.common_functions import calculate_aligned_offset
from resourceparse_lib.utils.Exceptions import ResourceParseException
import ast
import re
from collections import deque


class AdbParser:
    """This class is responsible for loading and parsing the adb file.
    """
    def __init__(self, adb_path):
        try:
            # build a dictionary with all the adb nodes.
            self.adb_dict = ET.parse(adb_path)
            self._build_xml_elements_dict()
            self._parse_config()
            self._dependant_layout_items = set()
            # build a dictionary with only the adb nodes that contain segment id field.
            self.segment_id_nodes_dict = {}
            self._build_nodes_with_seg_id()
            # fix the offset since subnode should contain the offset with the addition of his parent.
            self._fix_nodes_offset(self.segment_id_nodes_dict)
            # update all items that has dependency on other items, like conditions and union-selectors.
            self._update_dependant_layout_items()
        except ResourceParseException as rpe:
            raise ResourceParseException("{0}\nFailed to parse the ADB file.".format(rpe))

    def _update_dependant_layout_items(self):
        """This method go over all the segments and update fields with conditions."""

        for layout_item in self._dependant_layout_items:
            if layout_item.condition:
                layout_item.condition.update_variables(layout_item)
            if layout_item.uSelector:
                layout_item.uSelector.update_references(layout_item)

    def _create_enum_dict(self, enum_lst: list):
        """This function gets a list of enums and export them to a dictionary.
        if the enums_lst is empty, return None.
        """
        enums_dict = {}
        if len(enum_lst) == 0:
            return None

        for enum in enum_lst:
            enum = enum.split('=')
            if len(enum) != 2 or enum[1] == '':
                raise ResourceParseException("Error - Failed to parse enum attribute '{0}'".format(str(enum)))
            enums_dict[int(enum[1], 0)] = enum[0]
        return enums_dict

    def _build_xml_elements_dict(self):
        self._node_xml_elements = {}
        for xml_element in self.adb_dict.iter('node'):
            self._node_xml_elements[xml_element.attrib["name"]] = xml_element

    def _parse_config(self):
        self.ifdef_list = []
        self.if_dict = {}
        self._configs = {
            'big_endian_arr': False
        }
        for xml_element in self.adb_dict.iter('config'):
            attr = xml_element.attrib.get('define')
            if attr:
                if "=" not in attr:
                    # Create a list for 'inst_ifdef' (C like 'define' feature)
                    self.ifdef_list.append(attr)
                else:
                    # Create a dict for 'inst_if' (C like 'define' feature)
                    define_name, define_value = attr.split("=")
                    self.if_dict[define_name] = define_value

            attr = xml_element.attrib.get('big_endian_arr')
            if attr:
                try:
                    self._configs['big_endian_arr'] = int(attr) != 0
                except ValueError:
                    raise ResourceParseException("invalid value - {} of config - 'big_endian_array', should be numeric".format(attr))

    def _check_condition(self, left_operand, right_operand, condition):
        """
        This method do the right logic according the given condition
        """
        if condition == ' EQ ':
            return left_operand == right_operand
        elif condition == ' NOTEQ ':
            return left_operand != right_operand
        elif condition == ' LESS ':
            return left_operand < right_operand
        elif condition == ' LESS_EQ ':
            return left_operand <= right_operand
        elif condition == ' GREAT_EQ ':
            return left_operand >= right_operand
        elif condition == ' GREAT ':
            return left_operand > right_operand

        raise ResourceParseException("unsupported condition '{0}'".format(condition))

    def _get_condition_str(self, expression):
        """
        This method return the right condition exist in the expression
        """
        if ' EQ ' in expression:
            return ' EQ '
        elif ' NOTEQ ' in expression:
            return ' NOTEQ '
        elif ' LESS ' in expression:
            return ' LESS '
        elif ' LESS_EQ ' in expression:
            return ' LESS_EQ '
        elif ' GREAT_EQ ' in expression:
            return ' GREAT_EQ '
        elif ' GREAT ' in expression:
            return ' GREAT '

        raise ResourceParseException("No condition found in expression '{0}'".format(expression))

    def _check_single_expression(self, expression):
        """
        The method check the condition type and perform the
        logic accordingly.
        """
        condition = self._get_condition_str(expression)
        define_name, define_value = expression.split(condition)
        define_name = define_name.strip()
        define_value = define_value.strip()

        # if operand not exist in the if dictionary its a value that we need to convert from str to int
        left_operand = int(self.if_dict[define_name]) if define_name in self.if_dict else int(define_name)
        right_operand = int(self.if_dict[define_value]) if define_value in self.if_dict else int(define_value)
        return self._check_condition(left_operand, right_operand, condition)

    def _check_expressions(self, inst_if_attrib):
        """
        The method checks an expression and return True/False.
        Note that the method support only OR(s) or AND(s) but not together.
        """
        # assumption using 'OR' or 'AND' but not together
        expressions = []
        if ' OR ' in inst_if_attrib:
            expressions = inst_if_attrib.split(' OR ')
            # check if one of the expressions is True return True
            return any([self._check_single_expression(expression) for expression in expressions])
        elif ' AND ' in inst_if_attrib:
            expressions = inst_if_attrib.split(' AND ')
            # check if all of the expressions is True return True
            return all([self._check_single_expression(expression) for expression in expressions])

        # if only one expression
        return self._check_single_expression(inst_if_attrib)

    def _fix_nodes_offset(self, nodes_dict):
        """This method go over all the nodes in the dictionary and
        send them to offset fixing.
        """
        for node in nodes_dict.values():
            self._fix_node(node, node.offset)

    def _fix_node(self, node, offset):
        """This method go over all the subnodes and perform offset addition
        to all nodes recursively.
        """
        for sub_node in node.subItems:
            sub_node.offset += offset
            self._fix_node(sub_node, sub_node.offset)

    def _build_nodes_with_seg_id(self):
        """This method go over all the nodes in the adb dictionary and build a dictionary with the nodes
        that contain the "segment_id' field.
        """
        for node in self.adb_dict.iter('node'):
            if "segment_id" in node.attrib:
                segment_id = int(node.attrib["segment_id"], 0)
                adb_layout_item = self._node_to_AdbLayoutItem(node, None, 0, self._parse_node_size(node.attrib["size"]), True)
                self.segment_id_nodes_dict[segment_id] = adb_layout_item
                if ("is_conditional" in node.attrib):
                    if (node.attrib["is_conditional"] == '1'):
                        self.segment_id_nodes_dict[segment_id].is_conditional = True

    def _retrieve_node_by_name(self, node_name: str):
        """This method return the node with the
        wanted name, if not found return None.
        """
        if node_name in self._node_xml_elements:
            return self._node_xml_elements[node_name]
        else:  # Missing-nodes feature
            return None

    def _retrieve_layout_item_by_name(self, name):
        """This method return the layout item with the wanted name,
        if it wasn't found returns None
        """
        for seg in self.segment_id_nodes_dict.values():
            if seg.name == name:
                return seg
            for subItem in seg.subItems:
                if subItem.name == name:
                    return subItem
        return None

    @staticmethod
    def get_layout_item_by_path(path: str, layout_item):
        seperator_index = path.find(".")
        root_item = None
        # If There's a parent or segment prefix search path according to the prefix
        if seperator_index != -1:
            prefix = path[:seperator_index]
            if prefix in CONST.PARENT_PREFIX_LIST:
                root_item = layout_item.parent
                return root_item.get_child_by_path(path[seperator_index + 1:]) if root_item else None
            elif prefix == CONST.SEGMENT_PREFIX:
                root_item = layout_item.get_root()
                return root_item.get_child_by_path(path[seperator_index + 1:]) if root_item else None
        # If no relevant prefix
        else:
            root_item = layout_item.parent
            if not root_item:
                return None

            # Try searching from parent
            found_item = root_item.get_child_by_path(path)
            if found_item:
                return found_item

            # Try searching from segment root
            root_item = layout_item.get_root()
            found_item = root_item.get_child_by_path(path)
            if found_item:
                return found_item

            # Finally, try searching by DFS from segment root
            return AdbParser._find_layout_item_dfs(path, root_item)

    @staticmethod
    def _find_layout_item_dfs(path, root_item):
        dfs_queue = deque(reversed(root_item.subItems))
        while len(dfs_queue) > 0:
            current_item = dfs_queue.pop()
            found_item = current_item.get_child_by_path(path)
            if found_item:
                return found_item
            dfs_queue.extend(reversed(current_item.subItems))
        return None

    def _build_subitems(self, node: ET.Element, parent, last_sub_tree_flag):
        """This method build the subitems of the specific node.
        :param node: always field element except from the root which is node.
        """
        sub_items = []
        last_sub_item = max(node, key=lambda e: self._parse_node_size(e.attrib["offset"]))

        for item in node:
            is_unlimited_array = False
            # Skip on elements that are excluded in the configuration ('inst_ifdef')
            if 'inst_ifdef' in item.attrib:
                if item.attrib['inst_ifdef'] not in self.ifdef_list:
                    continue
            # Skip on elements that are excluded in the configuration ('inst_if')
            if 'inst_if' in item.attrib:
                if not self._check_expressions(item.attrib['inst_if']):
                    continue
            last_sub_item_flag = last_sub_tree_flag and last_sub_item is item

            low_bound = item.attrib.get("low_bound")
            high_bound = item.attrib.get("high_bound")

            # An array
            if low_bound and high_bound:
                start_index = int(low_bound, 10)
                # Definite array
                if high_bound != "VARIABLE":
                    end_index = int(high_bound, 10) + 1
                # Variable array
                else:
                    # Unlimited array
                    if last_sub_item_flag:
                        is_unlimited_array = True
                        end_index = int(low_bound, 10)
                    # Pointer / Wrong unlimited array
                    else:
                        end_index = int(low_bound, 10) + 1

                if not is_unlimited_array:
                    sub_items.extend(self._extract_array_to_list(item, parent, start_index, end_index))

            # On regular field or unlimited array, process recursively
            if not low_bound or is_unlimited_array:
                last_sub_item_flag = last_sub_item_flag and not is_unlimited_array
                adb_layout_item = self._node_to_AdbLayoutItem(item, parent, self._parse_node_size(item.attrib['offset']), self._parse_node_size(item.attrib['size']), last_sub_item_flag)
                if adb_layout_item:
                    if is_unlimited_array:
                        adb_layout_item.is_unlimited_array = True
                    sub_items.append(adb_layout_item)
        return sub_items

    @staticmethod
    def _calculate_array_item_offset(offset, element_size, idx, align=32, be_array=True):
        if be_array and element_size < align:
            array_dword_offset = offset // align * align
            element_dword_offset = (align - offset % align + (idx - 1) * element_size) // align * align  # calculating the offset as if elements were reversed inside the dword
            element_bit_offset = (offset + (align - idx * element_size) % align) % align

            return array_dword_offset + element_dword_offset + element_bit_offset
        else:
            return offset + element_size * idx

    def _extract_array_to_list(self, item, parent, start_index, end_index):
        """This method build insert array items to a list form a specific index.
        :param node: always field element except from the root which is node.
        :param parent: layout item representing the parent of the array.
        """
        extracted_array_layout_items = []

        array_offset = self._parse_node_size(item.attrib["offset"])
        array_size = self._parse_node_size(item.attrib["size"])

        element_size = int(array_size / (end_index - start_index))

        enum_dict = None
        if 'index_enum' in item.attrib and item.attrib['index_enum'] != '':
            enums_lst = item.attrib['index_enum'].split(',')
            enum_dict = self._create_enum_dict(enums_lst)
            if enum_dict is None:
                raise ResourceParseException("Error - could not parse the 'index_enum' attribute for node '{0}'.".format(item.attrib["name"]))

        for i in range(start_index, end_index):
            current_element_offset = AdbParser._calculate_array_item_offset(array_offset, element_size, i, be_array=self._configs['big_endian_arr'])
            adb_layout_item = self._node_to_AdbLayoutItem(item, parent, current_element_offset, element_size, False)

            if enum_dict is None or i not in enum_dict:
                adb_layout_item.name += "[" + str(i) + "]"
            else:
                adb_layout_item.name += "[" + enum_dict[i] + "]"

            extracted_array_layout_items.append(adb_layout_item)
        return extracted_array_layout_items

    def _node_to_AdbLayoutItem(self, field_element: ET.Element, parent, offset, size, last_sub_tree_flag):
        """This method build adb layout field from a given node.
        :param field_element: always field element except from the root which is node.
        """
        adb_layout_item = AdbLayoutItem()
        # adb_layout_item.fieldDesc = None  # Reference to "AdbFieldDesc" object, always != None
        adb_layout_item.parent = parent  # Reference to parent "AdbLayoutItem" object, always != None (expect of the root)
        adb_layout_item.name = field_element.attrib["name"]
        adb_layout_item.offset = offset
        adb_layout_item.size = size
        adb_layout_item.attrs = field_element.attrib
        if not parent:
            adb_layout_item.parse_method = field_element.attrib.get("parse_method", "adb")

        node_element = None
        if not parent:
            node_element = field_element
        else:
            subnode_name = field_element.attrib.get("subnode")
            if subnode_name:
                node_element = self._retrieve_node_by_name(subnode_name)

        if node_element:
            adb_layout_item.nodeDesc = self._node_to_node_desc(node_element)  # For leafs must be None

        condition_attr = field_element.attrib.get("condition")
        if (parent and parent.nodeDesc.is_conditional and condition_attr and condition_attr.strip() != ""):
            adb_layout_item.condition = ConditionParser(condition_attr, self.if_dict)
            self._dependant_layout_items.add(adb_layout_item)

        us_attr = field_element.attrib.get("union_selector")
        if adb_layout_item.nodeDesc and adb_layout_item.nodeDesc.isUnion and us_attr and us_attr.strip():
            adb_layout_item.uSelector = AdbUnionSelector(us_attr)
            self._dependant_layout_items.add(adb_layout_item)

        enum_attr = field_element.attrib.get("enum")
        try:
            if enum_attr:
                adb_layout_item.adb_enum = AdbEnum(enum_attr.strip())
        except ResourceParseException as rpe:
            raise ResourceParseException("Error - could not create the enums dictionary for node '{0}'.\n{1}".format(adb_layout_item.name, rpe))

        try:
            if node_element:
                adb_layout_item.subItems = self._build_subitems(node_element, adb_layout_item, last_sub_tree_flag)  # List of the child items (for nodes only)
        except ResourceParseException as rpe:
            raise ResourceParseException("{0}\nFailed to create a valid layout from node '{1}'.".format(rpe, field_element.attrib['name']))

        # adb_layout_item.attrs = {}  # Attributes after evaluations and array expanding
        # adb_layout_item.vars = {}  # all variable relevant to this item after evaluation
        return adb_layout_item

    def _node_to_node_desc(self, node: ET.Element):
        """This method build adb desc field from a given node.
        """
        node_descriptor = AdbNodeDesc()
        # node_description.name = ""
        # node_description.size = 0  # Size in bits
        node_descriptor.isUnion = int(node.attrib.get("attr_is_union", 0)) > 0
        node_descriptor.is_conditional = int(node.attrib.get("is_conditional", 0)) > 0
        # node_description.desc = ""
        # node_description.fields = []  # List of "AdbFieldDesc" objects
        # node_description.attrs = {}  # Dictionary of attributes: key, value
        # defined in
        # node_description.fileName = ""
        # node_description.lineNumber = -1
        return node_descriptor

    def _parse_node_size(self, size_str):
        """This method return the size of the 'size' attribute in bits.
        """
        hex_size = 0
        bit_size = 0
        size_parts = size_str.split(".")

        if len(size_parts) == 1:
            size_parts = size_parts[0], "0"
        if size_parts[0] == "":
            size_parts[0] = "0"

        hex_size = int(size_parts[0], 16) * 8
        bit_size = int(size_parts[1], 10)

        return hex_size + bit_size

####################################################################


class ConditionVariable:
    def __init__(self, name: str, consts):
        self._name = name
        self.found = name in consts
        self.evaluated = self.found
        self.value = int(consts[name], 0) if self.found else 0
        self.layout_item = None

    def update_references(self, dependant_layout_item):
        if self.found:
            return
        self.layout_item = AdbParser.get_layout_item_by_path(self._name, dependant_layout_item)
        if self.layout_item:
            self.found = True

    def evaluate(self, bit_array):
        if not self.evaluated:
            if self.found and self.layout_item:
                offset = calculate_aligned_offset(self.layout_item.offset, self.layout_item.size)
                self.evaluated = True
                self.value = int(bit_array[offset:offset + self.layout_item.size], 2)
            else:
                raise ResourceParseException('Condition variable - "{}", was not found in the adb'.format(self._name))
        return self.value


class ConditionParser:
    adb_to_py_ops = {'~': ' not ', ' AND ': ' and ', '|': ' or '}

    word_operators = ('AND',)
    symbol_operators = ('~', '|', '==', '!=', '(', ')')
    operators = word_operators + symbol_operators

    def __init__(self, condition_str: str, consts):
        variable_names = [word for word in re.findall(r"\$\([a-zA-Z_][\w]*\)(?:\.[a-zA-Z_][\w]*)*|[a-zA-Z_][\w]*(?:\.[a-zA-Z_][\w]*)*", condition_str) if word not in ConditionParser.word_operators]
        self._variables = {re.sub(r"\$\(([a-zA-Z_][\w]*)\)", r"___dollar___\1", variable_name.replace(".", "___")): ConditionVariable(variable_name, consts) for variable_name in variable_names}
        self._condition_str = condition_str
        for adb_op, py_op in ConditionParser.adb_to_py_ops.items():
            self._condition_str = self._condition_str.replace(adb_op, py_op)
        for fixed_variable_name, variable in self._variables.items():
            self._condition_str = self._condition_str.replace(variable._name, fixed_variable_name)
        self._condition_str = self._condition_str.strip()

    def update_variables(self, layout_item):
        for variable in self._variables.values():
            variable.update_references(layout_item)

    def evaluate(self, bit_array):
        try:
            tree = ast.parse(self._condition_str, mode='eval')
        except SyntaxError:
            raise ResourceParseException("Invalid condition syntax")
        if not all(isinstance(node, (ast.Expression, ast.Name, ast.Load,
                                     ast.UnaryOp, ast.unaryop,
                                     ast.BinOp, ast.operator,
                                     ast.BoolOp, ast.Num, ast.And, ast.Or,
                                     ast.Compare, ast.Eq, ast.NotEq, ast.Lt, ast.LtE, ast.Gt, ast.GtE)) for node in ast.walk(tree)):
            raise ResourceParseException("Condition contains unsupported operation")
        locals = {variable_name: variable.evaluate(bit_array) for variable_name, variable in self._variables.items()}
        return eval(compile(tree, filename='', mode='eval'), None, locals)


class AdbLayoutItem(object):
    """ Represents a Layout node/leaf instance """

    ##########################
    def __init__(self):
        self.fieldDesc = None        # Reference to "AdbFieldDesc" object, always != None
        self.nodeDesc = None         # For leafs must be None
        self.parent = None           # Reference to parent "AdbLayoutItem" object, always != None (expect of the root)
        self.name = ""               # The instance name
        self.subItems = []           # List of the child items (for nodes only)
        self.offset = 0              # Global offset (relative to the 0 address)
        self.size = 0                # Element size in bits
        self.attrs = {}              # Attributes after evaluations and array expanding
        self.vars = {}               # all variable relevant to this item after evaluation
        self.uSelector = None        # data structure that represent the union-selector properties
        self.adb_enum = None        # in case of being an enum element, holds the key-value of the enum
        self.condition = None
        self.is_unlimited_array = False

    def get_child_by_path(self, path):
        path_list = path.split('.')
        current_layout_item = self

        for path_part in path_list:
            sub_item = next((s for s in current_layout_item.subItems if s.name == path_part), None)
            if not sub_item:
                return None
            current_layout_item = sub_item
        return current_layout_item

    def get_root(self):
        layout_item = self
        while layout_item.parent:
            layout_item = layout_item.parent
        return layout_item


####################################################################
class AdbFieldDesc(object):
    """ Represents an ADABE field descriptor, objects of this type are immutable """

    ##########################
    def __init__(self):
        self.name = ""
        self.size = 0                    # Size in bits (the whole array size)
        self.offset = None                 # Offset in bits (relative to the node start addr)
        self.desc = ""
        self.lowBound = 0
        self.highBound = 0
        self.unlimitedArr = False
        self.definedAsArr = False
        self.subNode = None                # Subnode name as string
        self.attrs = {}                  # Dictionary of attributes: key, value
        self.reserved = False
        self.condition = ""


####################################################################
class AdbNodeDesc(object):
    """ Represents an ADABE node descriptor, objects of this type are immutable """

    ##########################
    def __init__(self):
        self.name = ""
        self.size = 0                 # Size in bits
        self.isUnion = False
        self.is_conditional = False
        self.desc = ""
        self.fields = []                # List of "AdbFieldDesc" objects
        self.attrs = {}                # Dictionary of attributes: key, value

        # defined in
        self.fileName = ""
        self.lineNumber = -1


####################################################################
class AdbEnum(object):
    """ Represents an ADABE enum  """

    ##########################
    def __init__(self, enum_string):

        self.num_to_string = {}
        self.string_to_num = {}

        enums_lst = enum_string.split(',')
        if len(enums_lst) == 0:
            raise ResourceParseException("Invalid enum format, or empty '{0}'".format(enum_string))

        for enum in enums_lst:
            enum = enum.split('=')
            if len(enum) != 2 or not enum[1].strip():
                raise ResourceParseException("Invalid enum pair '{0}', in enum {1}".format(str(enum), enum_string))
            numeric = int(enum[1], 0)
            string = enum[0].strip()
            self.num_to_string[numeric] = string
            self.string_to_num[string] = numeric


####################################################################
class AdbUnionSelector(object):
    """ Represents an ADABE union-selector descriptor, objects of this type are immutable """

    ##########################
    def __init__(self, selector_path=None):
        self.select_to_layout_item = {}   # mapping between the value and the enum, None if empty
        self.full_path = selector_path    # full path to the selector field, None if empty
        self.selector_layout_item = None

    def update_references(self, dependant_layout_item):
        self.selector_layout_item = AdbParser.get_layout_item_by_path(self.full_path, dependant_layout_item)

        if not self.selector_layout_item:
            raise ResourceParseException("Failed to find selector: '{0}' for node: '{1}'".format(self.full_path, dependant_layout_item.name))
        if not self.selector_layout_item.adb_enum:
            raise ResourceParseException("Selector field - '{0}' is not an enum".format(self.selector_layout_item.name))
        for sub_item in dependant_layout_item.subItems:
            selected_by = sub_item.attrs.get("selected_by")
            if selected_by:
                numeric_select = self.selector_layout_item.adb_enum.string_to_num.get(selected_by.strip())
                if numeric_select is not None:
                    self.select_to_layout_item[numeric_select] = sub_item
