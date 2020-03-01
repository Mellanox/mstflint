
# NAME

mstconfig

# SYNOPSIS

> mstconfig \[Options\] \<Commands\> \[Parameters\]

# DESCRIPTION
> 
> Allows the user to change some of the device configurations without
> having to create and burn a new firmware.
> 
> OPTIONS:

  - **-d**|-\-dev \<device\>  
    : Perform operation for a specified MST device.

  - **-b**|-\-db \<filename\>  
    : Use a specific database file.

  - **-f**|-\-file \<conf\_file\>  
    : raw configuration file.

  - **-h**|-\-help  
    : Display help message.

  - **-v**|-\-version  
    : Display version info.

  - **-e**|-\-enable\_verbosity  
    : Show default and current configurations.

  - **-y**|-\-yes  
    : Answer yes in prompt.

  - **-a**|-\-all\_attrs  
    : Show all attributes in the XML template

  - **-p**|-\-private\_key  
    : pem file for private key

  - **-u**|-\-key\_uuid  
    : keypair uuid
    
    COMMANDS:

  - clear\_semaphore  
    : clear the tool semaphore.

  - i\[show\_confs\]  
    : display information about all configurations.

  - q\[uery\]  
    : query supported configurations.

  - r\[eset\]  
    : reset all configurations to their default value.

  - s\[et\]  
    : set configurations to a specific device.

  - set\_raw  
    : set raw configuration file.(only Connect-IB/Connect-X4/LX.)

  - backup  
    : backup configurations to a file (only Connect-IB/Connect-X4/LX.).
    Use set\_raw command to restore file.

  - gen\_tlvs\_file  
    : Generate List of all TLVs. TLVs output file name must be
    specified. (\*)

  - g\[en\_xml\_template\]  
    : Generate XML template. TLVs input file name and XML output file
    name must be specified. (\*)

  - xml2raw  
    : Generate Raw file from XML file. XML input file name and raw
    output file name must be specified. (\*)

  - raw2xml  
    : Generate XML file from Raw file. raw input file name and XML
    output file name must be specified. (\*)

  - xml2bin  
    : Generate Bin file from XML file. XML input file name and bin
    output file name must be specified. (\*)

  - create\_conf  
    : Generate Configuration file from XML file. XML input file name and
    bin output file name must be specified. (\*)

  - apply  
    : Apply a Configuration file. bin input file name must be specified.
    (\*)
    
    (\*) These commands do not require MST device
    
    To show supported configurations by device type, run show\_confs
    command
    
# EXAMPLES

  - To query configurations  
    : mstconfig **-d** 04:00.0 query

  - To set configuration  
    : mstconfig **-d** 04:00.0 set SRIOV\_EN=1 NUM\_OF\_VFS=16
    WOL\_MAGIC\_EN\_P1=1

  - To set raw configuration  
    : mstconfig **-d** 05:00.0 **-f** conf\_file set\_raw

  - To reset configuration  
    : mstconfig **-d** 04:00.0 reset
    
    Supported devices:
    
    4th Generation devices: ConnectX3, ConnectX3-Pro (FW 2.31.5000 and
    above). 5th Generation devices: ConnectIB, ConnectX4, ConnectX4-LX, ConnectX5.

> Note: query device to view supported configurations by Firmware.

# SEE ALSO

The full documentation for **mstconfig,** is maintained as a Texinfo
manual. If the **info** and **mstconfig,** programs are properly
installed at your site, the command

> **info mstconfig,**

should give you access to the complete manual.
