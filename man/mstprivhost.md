
# NAME

mstprivhost

# SYNPOSIS

usage: mstprivhost \[-h\] \[-v\] **-\-device** DEVICE
\[-\-disable\_rshim\]

> \[-\-disable\_tracer\] \[-\-disable\_counter\_rd\]
> \[-\-disable\_port\_owner\] {r,restrict,p,privilege}

restrict or privilege host
Note: New configurations takes effect immediately.
Note: privileged host - host has all supported privileges.

> restricted host - host is not allowed to modify global per
> port/parameters or access other hosts parametersis.
> 
# DESCRIPTION

## optional arguments:

  - **-h**, **-\-help**  
    show this help message and exit

  - **-v**, **-\-version**  
    show program's version number and exit

# OPTIONS

  - **-\-device** DEVICE, **-d** DEVICE  
    Device to work with.

  - **-\-disable\_rshim**  
    When TRUE, the host does not have an RSHIM function to access the
    embedded CPU registers mlxconfig\_name: HOST\_DISABLE\_RSHIM

  - **-\-disable\_tracer**  
    When TRUE, the host will not be allowed to own the Tracer
    mlxconfig\_name: HOST\_DISABLE\_TRACER\_OWNER

  - **-\-disable\_counter\_rd**  
    When TRUE, the host will not be allowed to read Physical port
    counters mlxconfig\_name: HOST\_DISABLE\_PORT\_COUNTER

  - **-\-disable\_port\_owner**  
    When TRUE, the host will not be allowed to be Port Owner
    mlxconfig\_name: HOST\_DISABLE\_PORT\_OWNER

## Commands:

> {r,restrict,p,privilege}

  - restrict:  
    Set host 1 (ARM) privileged, host 0 (x86\_64) restricted.
    
    privilege: Set host 1 (ARM) privileged, host 0 (x86\_64) privileged
    
    (back to default).

# SEE ALSO

The full documentation for **mstprivhost** is maintained as a Texinfo
manual. If the **info** and **mstprivhost** programs are properly
installed at your site, the command

> **info mstprivhost**

should give you access to the complete manual.
