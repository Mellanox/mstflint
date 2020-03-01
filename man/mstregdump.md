
# NAME

mstregdump

# SYNOPSIS

> Usage: mstregdump \[-full\] \<device\> \[i2c-slave\] \[-v\[ersion\] \[-h\[elp\]\]\]

# DESCRIPTION

> Mellanox mstregdump utility, dumps device internal configuration data

  - **-full**  
    : Dump more expanded list of addresses Note : be careful when using
    this flag, None safe addresses might be read.

  - **-v** | **-\-version**  
    : Display version info

  - **-h** | **-\-help**  
    : Print this help message
    
# EXAMPLES

    mstregdump 0b:00.0

# SEE ALSO

The full documentation for **mstregdump,** is maintained as a Texinfo
manual. If the **info** and **mstregdump,** programs are properly
installed at your site, the command

> **info mstregdump**

should give you access to the complete manual.
