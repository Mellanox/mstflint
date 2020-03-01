
# NAME

mstflint

# SYNOPSIS

> MstFlint \[OPTIONS\] \<command\> \[Parameters\]
> 
> \[-d|-\-device \<device\>\] \[-i|-\-image \<image\>\] \[-\-ir\]
> \[-\-image\_reactivation\] \[-h|-\-help\] \[-\-hh\] \[-y|-\-yes\] \[-\-no\]
> \[-\-guid \<GUID\>\] \[-\-guids \<GUIDS...\>\] \[-\-mac \<MAC\>\]
> \[-\-macs \<MACs...\>\] \[-\-uid \<UID\>\] \[-\-blank\_guids\]
> \[-\-clear\_semaphore\] \[-\-qq\] \[-\-low\_cpu\] \[-\-flashed\_version\]
> \[-\-nofs\] \[-\-allow\_rom\_change\] \[-\-override\_cache\_replacement\]
> \[-\-no\_flash\_verify\] \[-\-use\_fw\] \[-s|-\-silent\] \[-\-vsd
> \<string\>\] \[-\-use\_image\_ps\] \[-\-use\_image\_guids\]
> \[-\-use\_image\_rom\] \[-\-use\_dev\_rom\] \[-\-ignore\_dev\_data\]
> \[-\-no\_fw\_ctrl\] \[-\-dual\_image\] \[-\-striped\_image\] \[-\-banks
> \<bank\>\] \[-\-log \<log\_file\>\] \[-\-flash\_params \<type, log2size,
> num\_of\_flashes\>\] \[-v|-\-version\] \[-\-private\_key \<key\_file\>\]
> \[-\-key\_uuid \<uuid\_file\>\] \[-\-private\_key2 \<key\_file\>\]
> \[-\-hmac\_key \<hmac\_key\>\] \[-\-key\_uuid2 \<uuid\_file\>\]

# DESCRIPTION

> flint is a FW (firmware) burning and flash memory operations tool for
> Mellanox Infiniband HCAs,Ethernet NIC cards, and switch devices.

OPTIONS

> MstFlint \[OPTIONS\] \<command\> \[Parameters\]

  - **-d**|-\-device \<device\>  
    : Device flash is connected to. Commands affected: all

  - **-i**|-\-image \<image\>  
    : Binary image file. Commands affected: burn, verify

  - **-\-ir**  
    : Commands affected: burn

  - **-\-image\_reactivation**  
    : Commands affected: burn

  - **-h**|-\-help  
    : Prints this message and exits

  - **-\-hh**  
    : Prints extended command help

  - **-y**|-\-yes  
    : Non interactive mode - assume answer "yes" to all questions.
    Commands affected: all

  - **-\-no**  
    : Non interactive mode - assume answer "no" to all questions.
    Commands affected: all

  - **-\-guid** \<GUID\>  
    : GUID base value. 4 GUIDs are automatically assigned to the
    following values:

  - guid  
    \-\> node GUID
    
    guid+1 -\> port1 guid+2 -\> port2 guid+3 -\> system image GUID.
    
    Note: port2 guid will be assigned even for a single port HCA - The
    HCA ignores this value.
    
    Commands affected: burn, sg

  - **-\-guids** \<GUIDS...\>  
    : 4 GUIDs must be specified here. The specified GUIDs are assigned
    to the following fields, respectively: node, port1, port2 and system
    image GUID.
    
    Note: port2 guid must be specified even for a single port HCA - The
    HCA ignores this value. It can be set to 0x0.
    
    Commands affected: burn, sg

  - **-\-mac** \<MAC\>  
    : MAC address base value. 2 MACs are automatically assigned to the
    following values:

  - mac  
    \-\> port1

  - mac+1  
    \-\> port2
    
    Commands affected: burn, sg

  - **-\-macs** \<MACs...\>  
    : 2 MACs must be specified here. The specified MACs are assigned to port1, port2, respectively. Commands affected: burn, sg

> Note: **-mac**/-macs flags are applicable only for Mellanox
> 
> Technologies ethernet products.

  - **-\-uid** \<UID\>  
    : ConnectIB/SwitchIB only. Derive and set the device UIDs (GUIDs,
    MACs, WWNs). UIDs are derived from the given base UID according to
    Mellanox Methodology Commands affected: burn, sg

  - **-\-blank\_guids**  
    : Burn the image with blank GUIDs and MACs (where applicable). These
    values can be set later using the "sg" command (see details below).
    
    Commands affected: burn

  - **-\-clear\_semaphore**  
    : Force clear the flash semaphore on the device. No command is
    allowed when this flag is used. NOTE: May result in system
    instability or flash corruption if the device or another application
    is currently using the flash. Exercise caution.

  - **-\-qq**  
    : Run a quick query. When specified, flint will not perform full
    image integrity checks during the query operation. This may shorten
    execution time when running over slow interfaces (e.g., I2C,
    MTUSB-1). Commands affected: query

  - **-\-low\_cpu**  
    : When specified, cpu usage will be reduced. Run time might be
    increased Commands affected: query

  - **-\-flashed\_version**  
    : When specified, only flashed fw version is fetched Commands
    affected: query

  - **-\-nofs**  
    : Burn image in a non failsafe manner.

  - **-\-allow\_rom\_change**  
    : Allow burning/removing a ROM to/from FW image when product version
    is present. Use only if you know what you are doing

  - **-\-override\_cache\_replacement**  
    : On SwitchX/ConnectIB devices: Allow accessing the flash even if
    the cache replacement mode is enabled. NOTE: This flag is intended
    for advanced users only. Running in this mode may cause the firmware
    to hang.

  - **-\-no\_flash\_verify**  
    : Do not verify each write on the flash.

  - **-\-use\_fw**  
    : Flash access will be done using FW (ConnectX-3/ConnectX-3Pro
    only).

  - **-s**|-\-silent  
    : Do not print burn progress flyer. Commands affected: burn

  - **-\-vsd** \<string\>  
    : Write this string, of up to 208 characters, to VSD when burn.

  - **-\-use\_image\_ps**  
    : Burn vsd as appears in the given image - do not keep existing VSD
    on flash. Commands affected: burn

  - **-\-use\_image\_guids**  
    : Burn (guids/macs) as appears in the given image. Commands
    affected: burn

  - **-\-use\_image\_rom**  
    : Do not save the ROM which exists in the device. Commands affected:
    burn

  - **-\-use\_dev\_rom**  
    : Save the ROM which exists in the device. Commands affected: burn

  - **-\-ignore\_dev\_data**  
    : Do not attempt to take device data sections from device(sections
    will be taken from the image. FS3 Only). Commands affected: burn

  - **-\-no\_fw\_ctrl**  
    : Do not attempt to work with the FW Ctrl update commands

  - **-\-dual\_image**  
    : Make the burn process burn two images on flash (previously default
    algorithm). Current default failsafe burn process burns a single
    image (in alternating locations). Commands affected: burn

  - **-\-striped\_image**  
    : Use this flag to indicate that the given image file is in a
    "striped image" format. Commands affected: query verify

  - **-\-banks** \<bank\>  
    : Set the number of attached flash devices (banks)

  - **-\-log** \<log\_file\>  
    : Print the burning status to the specified log file

**-\-flash\_params** \<type, log2size,

  - num\_of\_flashes\>  
    : Use the given parameters to access the flash
    
    instead of reading them from the flash. Supported parameters: Type:
    The type of the flash, such as:M25PXxx, M25Pxx, N25Q0XX, SST25VFxx,
    W25QxxBV, W25Xxx, W25Qxxx, W25Qxxx, AT25DFxxx, S25FLXXXP, S25FL11xx,
    MX25L16xxx, MX25Lxxx, S25FLxxx, IS25LPxxx. log2size: The log2 of the
    flash size.num\_of\_flashes: the number of the flashes connected to
    the device.

  - **-v**|-\-version  
    : Version info.

  - **-\-private\_key** \<key\_file\>  
    : path to PEM formatted private key to be used by the sign command

  - **-\-key\_uuid** \<uuid\_file\>  
    : UUID matching the given private key to be used by the sign command

  - **-\-private\_key2** \<key\_file\>  
    : path to PEM formatted private key to be used by the sign command

  - **-\-hmac\_key** \<hmac\_key\>  
    : path to file containing key (For FS4 image only).

  - **-\-key\_uuid2** \<uuid\_file\>  
    : UUID matching the given private key to be used by the sign command

COMMANDS SUMMARY

  - burn|b **-ir**  
    : Burn flash. Use "-ir burn" flag to perform
    
    image reactivation prior burning.

  - query|q \[full\]  
    : Query misc. flash/firmware characteristics,
    
    use "full" to get more information.

  - verify|v \[showitoc\]  
    : Verify entire flash, use "showitoc" to see
    
    ITOC headers in FS3/FS4 image only.

  - swreset  
    : SW reset the target switch device.This
    
    command is supported only in the In-Band access method.

  - brom  
    \<ROM-file\> : Burn the specified ROM file on the flash.

  - drom  
    : Remove the ROM section from the flash.

  - rrom  
    \<out-file\> : Read the ROM section from the flash.

  - bb  
    : Burn Block - Burns the given image as is. No
    
    checks are done.

  - sg  
    \[guids\_num=\<num|num\_port1,num\_port2\>
    
    step\_size=\<size|size\_port1,size\_port2\>\] | \[nocrc\] : Set
    GUIDs. sv : Set the VSD. ri \<out-file\> : Read the fw image on the
    flash. dc \[out-file\] : Dump Configuration: print fw configuration
    
    file for the given image.

  - dh  
    \[out-file\] : Dump Hash: dump the hash if it is integrated
    
    in the FW image

  - set\_key  
    \[key\] : Set/Update the HW access key which is used to
    
    enable/disable access to HW. The key can be provided in the command
    line or interactively typed after the command is given NOTE: The new
    key is activated only after the device is reset.

  - hw\_access  
    \<enable|disable\> \[key\] : Enable/disable the access to the HW.
    
    The key can be provided in the command line or interactively typed after the command
is given

  - hw  
    query : Query HW info and flash attributes.

  - erase|e \<addr\>  
    : Erases sector.

  - rw  
    \<addr\> : Read one dword from flash

  - ww  
    \<addr\> \<data\> : Write one dword to flash

  - wwne  
    \<addr\> \<data\> : Write one dword to flash without sector
    
    erase

  - wbne  
    \<addr\> \<size\> \<data ...\> : Write a data block to flash without
    sector
    
    erase.

  - wb  
    \<data-file\> \<addr\> : Write a data block to flash.

  - rb  
    \<addr\> \<size\> \[out-file\] : Read a data block from flash

  - clear\_semaphore  
    : Clear flash semaphore.

  - qrom  
    : query ROM image.

  - checksum|cs  
    : perform MD5 checksum on FW.
    
    timestamp|ts \<set|query|reset\> \[timestamp\] \[FW version\] : FW
    time stamping. cache\_image|ci : cache FW image(Windows only). sign
    : Sign firmware image file sign\_with\_hmac : Sign image with HMAC
    set\_public\_keys \[public keys binary file\] : Set Public Keys (For
    FS3/FS4 image only). set\_forbidden\_versions \[forbidden versions
    binary file\] : Set Forbidden Versions (For FS3/FS4 image only).

  - image\_reactivate|ir  
    : Reactivate previous flash image. For FW
    
    controlled devices only.

RETURN VALUES

  - 0  
    : Successful completion.

  - 1  
    : An error has occurred.

  - 7  
    : For burn command - FW already updated - burn
    
    was aborted.

# SEE ALSO

The full documentation for **mstflint,** is maintained as a Texinfo
manual. If the **info** and **mstflint,** programs are properly
installed at your site, the command

> **info mstflint,**

should give you access to the complete manual.
