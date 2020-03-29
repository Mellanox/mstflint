
# NAME

mstfwmanager

# SYNOPSIS

> mstfwmanager
> 
> \[-d|-\-dev DeviceName\] \[-h|-\-help\] \[-v|-\-version\] \[-\-query\]
> \[-\-query-format Format\] \[-u|-\-update\] \[-i|-\-image-file FileName\]
> \[-D|-\-image-dir DirectoryName\] \[-f|-\-force\] \[-\-no\_fw\_ctrl\]
> \[-y|-\-yes\] \[-\-no\] \[-\-clear-semaphore\] \[-\-exe-rel-path\]
> \[-l|-\-list-content\] \[-\-archive-names\] \[-\-nofs\] \[-\-log\]
> \[-L|-\-log-file LogFileName\] \[-\-no-progress\] \[-o|-\-outfile
> OutputFileName\] \[-\-online\] \[-\-online-query-psid PSIDs\] \[-\-key
> key\] \[-\-download DirectoryName\] \[-\-download-default\]
> \[-\-get-download-opt OPT\] \[-\-download-device Device\]
> \[-\-download-os OS\] \[-\-download-type Type\] \[-\-ssl-certificate
> Certificate\]
> 
# DESCRIPTION

> Mellanox Firmware Manager

OPTIONS

> mstfwmanager

  - **-d**|-\-dev DeviceName  
    : Perform operation for specified mst device(s). Run 'mst status'
    command to list the available devices. Multiple devices can be
    specified delimited by semicolons. A device list containing
    semicolons must be quoted.

  - **-h**|-\-help  
    : Show this message and exit

  - **-v**|-\-version  
    : Show the executable version and exit

  - **-\-query**  
    : Query device(s) info

  - **-\-query-format** Format  
    : (Query | Online query) output format, XML | Text - default Text

  - **-u**|-\-update  
    : Update firmware image(s) on the device(s)

  - **-i**|-\-image-file FileName  
    : Specified image file to use

  - **-D**|-\-image-dir DirectoryName  
    : Specified directory instead of default to locate image files

  - **-f**|-\-force  
    : Force image update

  - **-\-no\_fw\_ctrl**  
    : Don't use FW Ctrl update

  - **-y**|-\-yes  
    : Answer is yes in prompts

  - **-\-no**  
    : Answer is no in prompts

  - **-\-clear-semaphore**  
    : Force clear the flash semaphore on the device, No command is
    allowed when this flag is used. NOTE: May result in system
    instability or flash corruption if the device or another application
    is currently using the flash. Exercise caution.

  - **-\-exe-rel-path**  
    : Use paths relative to the location of the executable

  - **-l**|-\-list-content  
    : List file/Directory content, used with **-\-image-dir** and
    **-\-image-file** flags

  - **-\-archive-names**  
    : Display archive names in listing

  - **-\-nofs**  
    : Burn image in a non failsafe manner

  - **-\-log**  
    : Create log file

  - **-L**|-\-log-file LogFileName  
    : Use specified log file

  - **-\-no-progress**  
    : Do not show progress

  - **-o**|-\-outfile OutputFileName  
    : Write to specified output file

  - **-\-online**  
    : Fetch required FW images online from Mellanox server

  - **-\-online-query-psid** PSIDs  
    : Query FW info, PSID(s) are comma separated

  - **-\-key** key  
    : Key for custom download/update

  - **-\-download** DirectoryName  
    : Download files from server to a specified directory

  - **-\-download-default**  
    : Use Default values for download

  - **-\-get-download-opt** OPT  
    : Get download options for OS or Device Options are: OS, Device

  - **-\-download-device** Device  
    : Use '-\-get-download-opt Device' option to view available devices
    for device specific downloads

  - **-\-download-os** OS  
    : Only for self\_extractor download: Use '-\-get-download-opt OS'
    option to view available OS for sfx download

  - **-\-download-type** Type  
    : MFA | self\_extractor - default All

  - **-\-ssl-certificate** Certificate  
    : SSL certificate For secure connection

# EXAMPLES

> 1\. Query specific device or all devices (if no device were supplied)
> \>\> mstfwmanager \[-d \<device\>\] \[-\-query\]
> 2. Burn device with specific image / MFA / images directory
> \>\> mstfwmanager -d \<device\> \[-i \<image file/MFA file\> | -D \<images dir\>\]
> 3.Update the card's firmware
> \>\> mstfwmanager -u
> 4. Update the card's firmware from latest version on the web
> \>\> mstfwmanager -\-online -u
> 5. Download latest FW package from the web
> \>\> mstfwmanager -\-download-default -\-download-os Linux\_x64 -\-download-type self\_extractor

# SEE ALSO

The full documentation for **mstfwmanager** is maintained as a Texinfo
manual. If the **info** and **mstfwmanager** programs are properly
installed at your site, the command

> **info mstfwmanager**

should give you access to the complete manual.
