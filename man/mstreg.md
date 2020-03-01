
# NAME

mstreg

# SYNOPSIS

> mstreg \[OPTIONS\]

# DESCRIPTION

> Exposes supported access registers, and allows users to obtain
> information regarding the registers fields and attributes, and to set
> and get data with specific register.
> 
> OPTIONS:

  - **-h** |-\-help  
    : Display help message.

  - **-v** |-\-version  
    : Display version info.

  - **-d** |-\-device  
    \<device\> : Perform operation for a specified mst device.

  - **-a** |-\-adb\_file  
    \<adb\_file\> : An external ADB file

  - **-\-reg\_name**  
    \<reg\_name\> : Known access register name

  - **-\-reg\_id**  
    \<reg\_ID\> : Access register ID

  - **-\-reg\_len**  
    \<reg\_length\> : Access register layout length (bytes)

  - **-i** |-\-indexes  
    \<idxs\_vals\> : Register indexes

  - **-g** |-\-get  
    : Register access GET

  - **-s** |-\-set  
    \<reg\_dataStr\> : Register access SET

  - **-\-show\_reg**  
    \<reg\_name\> : Print the fields of a given reg access (must have
    reg\_name)

  - **-\-show\_regs**  
    : Print all available reg access'

  - **-\-yes**  
    : Non-interactive mode, answer yes to all questions
    
# EXAMPLES

  - Show all available access register  
    : mstreg **-d** \<device\> **-\-show\_regs**

  - Show all fields of register PAOS  
    : mstreg **-d** \<device\> **-\-show\_reg** PAOS
    
    GET PAOS with indexes: local port 0x1 and swid 0x5:
    
    mstreg **-d** \<device\> **-\-get** **-\-reg\_name** PAOS
    **-\-indexes** "local\_port=0x1,swid=0x5"
    
    SET PAOS with indexes: local port 0x1 and swid 0x5, and data: e 0x0:
    
    mstreg **-d** \<device\> **-\-set** "e=0x0" **-\-reg\_name** PAOS
    **-\-indexes** "local\_port=0x1,swid=0x5"

# SEE ALSO

The full documentation for **mstreg,** is maintained as a Texinfo
manual. If the **info** and **mstreg,** programs are properly installed
at your site, the command

> **info mstreg**

should give you access to the complete manual.
