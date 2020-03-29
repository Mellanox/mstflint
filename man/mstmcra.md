
# NAME

mstmcra - manual page for mstmcra Mellanox Configuration Registers
Access tool

# SYNOPSIS
> Mellanox Configuration Registers Access tool Usage:
> mstmcra \[-s \<i2c-slave\>\] \[-a \<adb dump\>\] \[-v\] \[-h\] \[-c\] \<device\>
> \<addr\[.\<bit offset\>:\<bit size\>\]|\[,\<bytes number\>\]\> \[data\]
> If data is given, operation is write. Otherwise it is read.
> 
> If a bit range is given in the address (E.G.: 0xf0014.16:8):
> - For read  
 >   \- Only the requested bits are printed.
   > 
>  - For write
 >  \- Read-Modify-Write. Only the requested bits are changed.
    >
 >   If 'bytes number' is given in the address (E.G.: 0xf0014,16):
>
 > - For read  
  >  \- Will read a block (its size is the given bytes number).
    >
  >  - For write
  >  \- User need to give list of dwrods to write, number of dwords should be (bytes number/4).

# DESCRIPTION

> Reads/writes a single word from/to a device configuration register
> space

- **-s** \<i2c-slave\> : I2C slave address.

- **-a** \<dump file\> : adb dump file, used for access by path.

 - **-c** clear the device's PCI semaphore.

 - **-h** Print this help message.

 - **-v** Display version info

## Environment Variables:

  - ADB\_DUMP - Holds the path to adb dump, used for access by path (can be overridden by "-a").

# SEE ALSO

The full documentation for **mstmcra** is maintained as a Texinfo
manual. If the **info** and **mstmcra** programs are properly installed
at your site, the command

> **info mstmcra**

should give you access to the complete manual.
