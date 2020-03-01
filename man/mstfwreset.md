
# NAME

mstfwreset

# SYNOPSIS

usage: mstfwreset **-\-device** DEVICE \[-\-level {0,3,4,5}\] \[-\-type
{0,1}\] \[-\-yes\]

> \[-\-skip\_driver\] \[-\-mst\_flags MST\_FLAGS\] \[-\-version\]
> \[-\-help\] \[-\-skip\_fsm\_sync\]
> {q,query,r,reset,reset\_fsm\_register}

# DESCRIPTION

## mstfwreset : The tool provides the following functionality in order to load new firmware:

> 1\. Query the device for the supported reset-level and reset-type 2.
> Perform reset operation on the device

# OPTIONS

  - **-\-device** DEVICE, **-d** DEVICE  
    Device to work with

  - **-\-level** {0,3,4,5}, **-l** {0,3,4,5}  
    Run reset with the specified reset-level

  - **-\-type** {0,1}, **-t** {0,1}  
    Run reset with the specified reset-type

  - **-\-yes**, **-y**  
    answer "yes" on prompt

  - **-\-skip\_driver**, **-s**  
    Skip driver start/stop stage (driver must be stopped manually)

  - **-\-mst\_flags** MST\_FLAGS, **-m** MST\_FLAGS  
    Provide mst flags to be used when invoking mst restart step. For
    example: **-\-mst\_flags=**"-\-with\_fpga"

  - **-\-version**, **-v**  
    Print tool version

  - **-\-help**, **-h**  
    show this help message and exit

  - **-\-skip\_fsm\_sync**  
    Skip fsm syncing

## Commands:

> {q,query,r,reset,reset\_fsm\_register}
> 
> query: Query reset Level. reset: Execute reset. reset\_fsm\_register:
> Reset the fsm register.

## Reset levels:

> 0: Driver, PCI link, network link will remain up ("live-Patch") 3:
> Driver restart and PCI reset 4: Warm Reboot 5: Cold Reboot

## Reset types:

> 0: Full chip reset 1: Phy-less reset ("port-alive" - network link will
> remain up)

# SEE ALSO

The full documentation for **mstfwreset** is maintained as a Texinfo
manual. If the **info** and **mstfwreset** programs are properly
installed at your site, the command

> **info mstfwreset**

should give you access to the complete manual.
