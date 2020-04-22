# Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.   
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
# --                                                                        


#######################################################
# 
# AdbParser.py
# Python implementation of the Class AdbParser
# Created on:      23-Mar-2020 8:00:00 AM
# Original author: talve
# 
#######################################################
import xml.etree.ElementTree as ET


class AdbParser:
    """This class is responsible for loading and parsing the adb file.
    """
    def __init__(self, adb_path):
        try:
            # build a dictionary with all the adb nodes.
            self.adb_dict = ET.parse(adb_path)
            # build a dictionary with only the adb nodes that contain segment id field.
            self.segment_id_nodes_dict = {}
            self._build_nodes_with_seg_id()
            # fix the offset since subnode should contain the offset with the addition of his parent.
            self._fix_nodes_offset(self.segment_id_nodes_dict)
        except Exception as _:
            raise Exception("Fail to parse the ADB file")

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
                adb_layout_item = self._node_to_AdbLayoutItem(node)
                self.segment_id_nodes_dict[node.attrib["segment_id"]] = adb_layout_item

    def _retrieve_node_by_name(self, node_name):
        """This method go over all the nodes in the adb dictionary and return the node with the
        wanted name, if not found return None.
        """
        for node in self.adb_dict.iter('node'):
            if node.attrib["name"] == node_name:
                return node
        return None

    def _build_subitems(self, node):
        """This method build the subitems of the specific node
        """
        sub_items = []
        counter = 0
        for item in node:
            if "low_bound" in item.attrib and "high_bound" in item.attrib:
                self._extract_array_to_list(counter, item, sub_items)
            else:
                sub_items.insert(counter, self._node_to_AdbLayoutItem(item))
                counter += 1
        return sub_items

    def _extract_array_to_list(self, index, item, subitems_list):
        """This method build insert array items to a list form a specific index.
        """
        name = item.attrib["name"]
        start_index = int(item.attrib["low_bound"], 10)
        if item.attrib["high_bound"] == "VARIABLE":
            end_index = 1
        else:
            end_index = int(item.attrib["high_bound"], 10) + 1

        offset = self._parse_node_size(item.attrib["offset"])
        size = self._parse_node_size(item.attrib["size"])

        calculated_size = int(size / (end_index - start_index))
        current_offset = offset

        for i in range(start_index, end_index):
            adb_layout_item = AdbLayoutItem()
            adb_layout_item.nodeDesc = self._node_to_node_desc(item)
            adb_layout_item.name = name + "[" + str(i) + "]"
            adb_layout_item.size = calculated_size
            adb_layout_item.offset = current_offset
            subitems_list.insert(index, adb_layout_item)
            current_offset += calculated_size
            index += 1

    def _node_to_AdbLayoutItem(self, node):
        """This method build adb layout field from a given node.
        """
        adb_layout_item = AdbLayoutItem()
        #adb_layout_item.fieldDesc = None  # Reference to "AdbFieldDesc" object, always != None
        #adb_layout_item.parent = None  # Reference to parent "AdbLayoutItem" object, always != None (expect of the root)
        adb_layout_item.name = node.attrib["name"]
        adb_layout_item.nodeDesc = self._node_to_node_desc(node)  # For leafs must be None
        if "subnode" in node.attrib:
            sub_node = self._retrieve_node_by_name(node.attrib["subnode"])
            if "attr_is_union" in sub_node.attrib:
                adb_layout_item.nodeDesc.isUnion = self._parse_union(sub_node.attrib["attr_is_union"])
            adb_layout_item.subItems = self._build_subitems(sub_node)  # List of the child items (for nodes only)
        else:
            adb_layout_item.subItems = self._build_subitems(node)

        if "offset" in node.attrib:
            adb_layout_item.offset = self._parse_node_size(node.attrib["offset"])

        adb_layout_item.size = self._parse_node_size(node.attrib["size"])
        adb_layout_item.attrs = {}  # Attributes after evaluations and array expanding
        adb_layout_item.arrayIdx = -1  # in case of being part of an array this will hold the array index, -1 means not part of array
        #adb_layout_item.vars = {}  # all variable relevant to this item after evaluation
        return adb_layout_item

    def _node_to_node_desc(self, node):
        """This method build adb desc field from a given node.
        """
        node_description = AdbNodeDesc()
        #node_description.name = ""
        #node_description.size = 0  # Size in bits
        if "attr_is_union" in node.attrib:
            node_description.isUnion = self._parse_union(node.attrib["attr_is_union"])
        #node_description.desc = ""
        #node_description.fields = []  # List of "AdbFieldDesc" objects
        #node_description.attrs = {}  # Dictionary of attributes: key, value
        # defined in
        #node_description.fileName = ""
        #node_description.lineNumber = -1
        return node_description

    def _parse_union(self, union_str):
        """This method parse the 'is union' attribute.
        """
        if union_str == "1":
            return True
        return False

    def _parse_node_size(self, size_str):
        """This method return the size of the 'size' attribute in bits.
        """
        hex_size = 0
        bit_size = 0

        if "." in size_str:
            # hex size is in bytes, multiply by 8 to convert to bits
            hex_size = size_str[:size_str.index(".")]
            bit_size = size_str[size_str.index(".")+1:]

            hex_size = 0 if len(hex_size) == 0 else int(hex_size, 16) * 8
            bit_size = 0 if len(size_str[size_str.index("."):]) == 0 else int(bit_size, 10)
        else:
            bit_size = int(size_str, 10)

        return hex_size+bit_size

####################################################################


class AdbLayoutItem(object):
    """ Represents a Layout node/leaf instance """

    ##########################
    def __init__(self):
        self.fieldDesc   = None        # Reference to "AdbFieldDesc" object, always != None
        self.nodeDesc    = None        # For leafs must be None
        self.parent      = None        # Reference to parent "AdbLayoutItem" object, always != None (expect of the root)
        self.name        = ""          # The instance name
        self.subItems    = []          # List of the child items (for nodes only)
        self.offset      = 0           # Global offset (relative to the 0 address)
        self.size        = 0           # Element size in bits
        self.attrs       = {}          # Attributes after evaluations and array expanding
        self.arrayIdx    = -1          # in case of being part of an array this will hold the array index, -1 means not part of array
        self.vars        = {}          # all variable relevant to this item after evaluation


####################################################################
class AdbFieldDesc(object):
    """ Represents an ADABE field descriptor, objects of this type are immutable """

    ##########################
    def __init__(self):
        self.name       = ""
        self.size       = 0                    # Size in bits (the whole array size)
        self.offset     = None                 # Offset in bits (relative to the node start addr)
        self.desc       = ""
        self.lowBound   = 0
        self.highBound  = 0
        self.unlimitedArr = False
        self.definedAsArr = False
        self.subNode    = None                # Subnode name as string
        self.attrs      = {}                  # Dictionary of attributes: key, value
        self.reserved   = False
        self.condition  = ""


####################################################################
class AdbNodeDesc(object):
    """ Represents an ADABE node descriptor, objects of this type are immutable """

    ##########################
    def __init__(self):
        self.name       = ""
        self.size       = 0                 # Size in bits
        self.isUnion    = False
        self.desc       = ""
        self.fields     = []                # List of "AdbFieldDesc" objects
        self.attrs      = {}                # Dictionary of attributes: key, value

        # defined in
        self.fileName = ""
        self.lineNumber = -1
