Mellanox Technologies - www.mellanox.com
****************************************

MSTFLINT Package - Firmware Burning and Diagnostics Tools

1) Overview
    This package contains a burning tool and diagnostic tools for Mellanox
    manufactured HCA/NIC cards. It also provides access to the relevant source
    code. Please see the file LICENSE for licensing details.
	This package is based on a subset of the Mellanox Firmware Tools (MFT) package.
	For a full documentation of the MFT package, please refer to the downloads page
	in Mellanox web site.

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
       This lib provides low level Flash access through Mellanox HCAs.
    c) mtcr lib (implemented in mtcr.h file)
       This lib enables access to HCA hardware registers.
    d) mstregdump utility
       This utility dumps hardware registers from Mellanox hardware
       for later analysis by Mellanox.
    e) mstvpd
       This utility dumps the on-card VPD.
    f) mstmcra
       This debug utility reads/writes a to/from the device configuration register space.
    g) mstconfig
       This tool sets or queries non-volatile configurable options for Mellanox HCAs.

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
        02:00.0 Ethernet controller: Mellanox Technologies MT25448 [ConnectX EN 10GigE, PCIe 2.0 2.5GT/s] (rev a0) 

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
         02:00.0 Ethernet controller: Mellanox Technologies MT25448 [ConnectX EN 10GigE, PCIe 2.0 2.5GT/s] (rev a0) 
	   
       # Use mstregdump to dump HW registers, using PCI config cycles
       > mstregdump /proc/bus/pci/02/00.0 > crdump.log

       Note: Typically, you will need root privileges for hardware access

	d) Accessing a multi-function device:

	   In some configuration, the CA device identifies as a multi-function device on PCI. E.G.:
	   > /sbin/lspci -d 15b3:
	   07:00.0 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.1 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.2 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.3 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.4 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.5 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.6 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)
	   07:00.7 Ethernet controller: Mellanox Technologies MT26468 [ConnectX EN 10GigE, PCIe 2.0 5GT/s] (rev b0)

	   These multiple "logical" devices are actually a single physical device, so firmware update or "physical"
	   diagnostics should be run only on one of the functions.

	   When the device driver is loaded, only the primary physical function of the device can be accessed.
	   In Linux that would typically be function 0. This function can be accessed using memory mapping, as
	   described in sub section a) above. E.G.:
	   > mstflint -d 07:00.0 q

	   When the device driver is not loaded, all the functions can be accessed using configuration cycles, as
	   described in sub section c) above. It is recommended to use function 0 for FW update or diagnostics, E.G.:
	   > mstflint -d /proc/bus/pci/07/00.0 q

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
	> mstvpd mlx4_0
	ID: Hawk Dual Port
	PN: MNPH29C-XTR
	EC: X2
	SN: MT1001X00749
	V0: PCIe Gen2 x8
	V1: N/A
	YA: N/A
	RW:

    > mstvpd mlx4_0 -- PN ID
	PN: MNPH29C-XTR
	ID: Hawk Dual Port

8) Usage (mstconfig):
    Read mstconfig usage. Enter "mstconfig -h" for a help message.

9) Problem Reporting:
	Please collect the following information when reporting issues:

	uname -a
	cat /etc/issue
	cat /proc/bus/pci/devices
	mstflint -vv
	lspci
        mstflint -d 02:00.0 v
        mstflint -d 02:00.0 q
        mstvpd 02:00.0


