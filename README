Mellanox Technologies - www.mellanox.com
****************************************

MSTFLINT Package - Firmware Burning and Diagnostics Tools

1) Overview
    This package contains a burning tool and diagnostic tools for Mellanox
    manufactured HCA/NIC cards. It also provides access to the relevant source
    code. Please see the file LICENSE for licensing details.

    ----------------------------------------------------------------------------
    NOTE:
    This burning tool should be used only with Mellanox-manufactured
    HCA/NIC cards. Using it with cards manufactured by other vendors 
    may be harmful  to  the cards (due to different configurations).
    Using the diagnostic tools is normally safe for all HCAs/NICs.
    ----------------------------------------------------------------------------
    
2) Package Contents
    a) mstflint source code
    b) mflash lib
       This lib provides Flash access through Mellanox HCAs.
    c) mtcr lib (implemented in mtcr.h file)
       This lib enables access to HCA hardware registers.
    d) mstregdump utility
       This utility dumps hardware registers from Mellanox hardware
       for later analysis by Mellanox.
    e) mstvpd
       This utility dumps the on-card VPD.

3) Installation
    a) Build the mstflint utility. This package is built using a standard
       autotools method.
	   
       Example: 
       > ./configure
       > make
       > make install

       - Run "configure --help" for custom configuration options.
       - Typically, root privileges are required to run "make install"

4) Hardware Access Device Names
   The tools in this package require a device name in the command
   line. The device name is the identifier of the target CA.
   This section describes the device name formats and the HW access flow.

   a) The devices can be accessed by their PCI ID as displayed by lspci
      (bus:dev.fn).
      Example:
      # List all Mellanox devices
      > /sbin/lspci -d 15b3:
        02:00.0 Ethernet controller: Mellanox Technologies Unknown device 6368 (rev a0)
 	   
      # Use mstflint tool to query the firmware on this device
      > mstflint -d 02:00.0 q

    b) When the IB driver (mlx4 or mthca) is loaded, the devices can be accessed
       by their IB device name.
       Example:
       # List the IB devices 
       > ibv_devinfo | grep hca_id
         hca_id: mlx4_0

       # Use mstvpd tool to dump the VPD of this device
       > mstvpd mlx4_0

    c) PCI configuration access
       In examples a and b above, the device is accessed via PCI Memory Mapping.
       The device can also be accessed by PCI configuration cycles.
       PCI configuration access is slower and less safe than memory access --
       use it only if methods a and b above do not work.

       To force configuration access, use device names in the following format:
       /proc/bus/pci/<bus>/<dev.fn>

       Example:
       # List all Mellanox devices
       > /sbin/lspci -d 15b3:
         02:00.0 Ethernet controller: Mellanox Technologies Unknown device 6368 (rev a0)
	   
       # Use mstregdump to dump HW registers, using PCI config cycles
       > mstregdump /proc/bus/pci/02/00.0 > crdump.log

       Note: Typically, you will need root privileges for hardware access
	   
5) Usage (mstflint):
       Read mstflint usage. Enter "./mstflint -h" for a short help message, or
       "./mstflint -hh" for a detailed help message.

       Obtaining firmware files:
       If you purchased your card from Mellanox Technologies, please use the
       Mellanox website (www.mellanox.com, under 'Firmware' downloads) to
       download the firmware for your card.
       If you purchased your card from a vendor other than Mellanox, get a
       specific firmware configuration (INI) file from your HCA card vendor and
       generate the binary image.
	
       Use mstflint to burn a device according to the burning instructions in 
       "mstflint -hh" and in Mellanox web site firmware page.

6) Usage (mstregdump):
       An internal register dump is displayed to the standard output.
       Please store it in a file for analysis by Mellanox.

       Example:
       > mstregdump mthca0 > dumpfile

7) Usage (mstvpd):
    A VPD dump is displayed to the standard output.
	A list of keywords to dump can be supplied after the -- flag
	to apply an output filter.

	Examples:
	> mstvpd mthca0
	ID: Lion cub DDR
	PN: MHGA28-1T
	EC: A3
	SN: MT0551X00740
	V0: PCIe x8
	V1: N/A
	YA: R               R
	RW:

	> mstvpd mthca0 -- PN ID
	PN: MHGA28-1T
	ID: Lion cub DDR

8) Problem Reporting:
	Please collect the following information when reporting issues:

	uname -a
	cat /etc/issue
	cat /proc/bus/pci/devices
	mstflint -vv
	lspci
        mstflint -d 02:00.0 v
        mstflint -d 02:00.0 q
        mstvpd 02:00.0


