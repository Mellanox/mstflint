
# NAME

mstcongestion

# SYNPOSIS

> mstcongestion \[OPTIONS\]
> 
> \<-d|-\-device \<PCI DEVICE\>\> \[-\-mode \<MODE\>\] \[-\-action
> \<ACTION\>\] \[-q|-\-query\] \[-h|-\-help\] \[-v|-\-version\]

# DESCRIPTION

> mstcongestion is a utility for configuring Mellanox device's receive
> congestion handling.

OPTIONS

> mstcongestion \[OPTIONS\]

  - **-d**|-\-device \<PCI DEVICE\>  
    : Mellanox PCI device address

  - **-\-mode** \<MODE\>  
    : Set Mode, options are: \[aggressive | dynamic\]

  - **-\-action** \<ACTION\>  
    : Set Action, options are: \[disabled | drop | mark\]

  - **-q**|-\-query  
    : Query congestion

  - **-h**|-\-help  
    : Show help message and exit

  - **-v**|-\-version  
    : Show version and exit

# SEE ALSO

The full documentation for **mstcongestion,** is maintained as a Texinfo
manual. If the **info** and **mstcongestion,** programs are properly
installed at your site, the command

> **info mstcongestion,**

should give you access to the complete manual.
