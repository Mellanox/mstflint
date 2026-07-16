/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 *  Version: $Id$
 *
 */

#ifndef DEVICE_PROPERTIES_CONSTANTS_H
#define DEVICE_PROPERTIES_CONSTANTS_H

/* Property key constants -- JSON field names used by device_properties_api */

#define PROP_DEVICE_NAME "device_name"
#define PROP_DEVICE_SHORT_NAME "device_short_name"
#define PROP_FW_NAME "fw_name"
#define PROP_DEVICE_TYPE "device_type"
#define PROP_SERIES "series"
#define PROP_SERIES_INDEX "series_index"
#define PROP_IS_SECURED "is_secured"
#define PROP_VENDOR "vendor"
#define PROP_DEVICE_FAMILY "device_family"
#define PROP_PORTS_NUM "ports_num"
#define PROP_MODULE_NUM "module_num"
#define PROP_GENERATION "generation"
#define PROP_PCI_DEVICE_ID_LIST "pci_device_id_list"
#define PROP_IMAGE_LAYOUT_FORMAT "image_layout_format"
#define PROP_FW_MAJOR "fw_major"
#define PROP_SUPPORTS_ETH "supports_eth"
#define PROP_SUPPORTS_IB "supports_ib"
#define PROP_NUMBER_OF_CLUSTERS "number_of_clusters"
#define PROP_PCIE_UC_SUPPORTED "pcie_uc_supported"
#define PROP_PHY_UC_SUPPORTED "phy_uc_supported"
#define PROP_SX_DUMP_SUPPORTED "sx_dump_supported"
#define PROP_RX_DUMP_SUPPORTED "rx_dump_supported"
#define PROP_SUPPORTS_DYNAMIC_DB "supports_dynamic_db"
#define PROP_VALID_CLUSTER_INDEXES "valid_cluster_indexes"

/* WQ/CQ/EQ/SRQ context node names */
#define PROP_CMAS_CONTEXT_NODE_NAME "cmas_context_node_name"
#define PROP_COMMON_QPC_NODE "common_qpc_node"
#define PROP_SEND_QPC_NODE "send_qpc_node"
#define PROP_RECEIVE_QPC_NODE "receive_qpc_node"
#define PROP_QPC_VALID_FIELD "qpc_valid_field"
#define PROP_QPC_DUAL_WRITE_FIELD "qpc_dual_write_field"
#define PROP_SRQ_NODE "srq_node"
#define PROP_SRQ_VALID_FIELD "srq_valid_field"
#define PROP_CQ_NODE "cq_node"
#define PROP_CQ_VALID_FIELD "cq_valid_field"
#define PROP_EQ_NODE "eq_node"
#define PROP_EQ_VALID_FIELD "eq_valid_field"
#define PROP_HW_SXDC_VALID_FIELD_NAME "hw_sxdc_valid_field_name"
#define PROP_IGNORE_STEERING_LAST_QP_FIELD "ignore_steering_last_qp_field"
#define PROP_ICQ_STATE_NODE "icq_state_node"
#define PROP_MKEY_CONTEXT_NODE "mkey_context_node"
#define PROP_MKEY_CONTEXT_VALID "mkey_context_valid"

/* Tracer properties */
#define PROP_PTR_CHUNK_SIZE "ptr_chunk_size"
#define PROP_FIFO_EVENTS_IN_ROW "fifo_events_in_row"
#define PROP_FIFO_SIZE "fifo_size"
#define PROP_TS_ID "ts_id"
#define PROP_G_EVENT_TS_OFFS "g_event_ts_offs"
#define PROP_G_EVENT_TS_SIZE "g_event_ts_size"
#define PROP_G_EVENT_LOST_BIT_OFFS "g_event_lost_bit_offs"
#define PROP_G_EVENT_DATA_OFFS "g_event_data_offs"
#define PROP_G_EVENT_DATA_SIZE "g_event_data_size"
#define PROP_G_EVENT_ID_OFFS "g_event_id_offs"
#define PROP_G_EVENT_ID_SIZE "g_event_id_size"
#define PROP_G_EVENT_UNREL_BIT_OFFS "g_event_unrel_bit_offs"
#define PROP_MKEY_PATH "mkey_path"

/* FW trace properties */
#define PROP_FW_STR_DB_SIGNATURE_EXISTS "fw_str_db_signature_exists"
#define PROP_MAX_MAIN_IRISC "maxMainIrisc"
#define PROP_MAX_APU "maxAPU"
#define PROP_MAX_NUM_OF_TILES "maxNumOfTiles"
#define PROP_MAX_IRISC_PER_TILE "maxIriscPerTile"
#define PROP_IRISC_START_ADDR "IriscStartAddr"
#define PROP_IRISC_STEP "IriscStep"
#define PROP_TILE_START "TileStart"
#define PROP_TILE_STEP "TileStep"
#define PROP_APU_START_ADDR "ApuStartAddr"
#define PROP_APU_STEP "ApuStep"
#define PROP_APU_MAX_NUM_OF_STEPS "ApuMaxNumOfSteps"
#define PROP_SUPPORT_PHY_UC "supportPhyUc"
#define PROP_IS_DYNAMIC_DEVICE_WITHOUT_IRISC_ID "is_dynamic_device_without_irisc_id"
#define PROP_SUPPORT_NVRISC "support_nvrisc"

/* Devmon properties */
#define PROP_MARKET_NAME "market_name"
#define PROP_PROJECT_NAME "project_name"
#define PROP_HW_REV_ID "hw_rev_id"

/* ICMD properties */
#define PROP_CMD_PTR_ADDRESS "cmd_ptr_address"
#define PROP_CMD_PTR_BITLEN "cmd_ptr_bitlen"
#define PROP_SEMAPHORE_ADDRESS "semaphore_address"
#define PROP_SEMAPHORE_BIT_OFFSET "semaphore_bit_offset"
#define PROP_STATIC_CFG_NOT_DONE_ADDRESS "static_cfg_not_done_address"
#define PROP_STATIC_CFG_NOT_DONE_OFFSET "static_cfg_not_done_offset"
#define PROP_VERSION_BIT_OFFSET "version_bit_offset"
#define PROP_VERSION_BITLEN "version_bitlen"
#define PROP_VERSION_ADDRESS "version_address"

/* Property value constants -- device_type field values */
#define DEVICE_TYPE_NIC "NIC"
#define DEVICE_TYPE_SWITCH "Switch"
#define DEVICE_TYPE_CABLE "Cable"
#define DEVICE_TYPE_LINKX "LinkX"
#define DEVICE_TYPE_RETIMER "Retimer"

/* Property value constants -- image_layout_format field values */
#define IMAGE_LAYOUT_NA "N/A"
#define IMAGE_LAYOUT_FS2 "fs2"
#define IMAGE_LAYOUT_FS3 "fs3"
#define IMAGE_LAYOUT_FS4 "fs4"
#define IMAGE_LAYOUT_FS5 "fs5"
#define IMAGE_LAYOUT_FS6 "fs6"

/* Property value constants -- vendor field values */
#define VENDOR_MELLANOX "Mellanox"
#define VENDOR_NVIDIA "Nvidia"

#endif /* DEVICE_PROPERTIES_CONSTANTS_H */
