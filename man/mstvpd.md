
# NAME

mstvpd

# SYNOPSIS

**mstvpd** \[*-m|-n|-r*\] \[*-t \#\#*\] *\<file\> *\[*-- keyword *...\]

# DESCRIPTION

**-h** Print this help.
**-v** Print tool version.
**-m** Dump raw VPD data to stdout.
**-n** Do not validate check sum.
**-r** Do not check and display the VPD\_W tag in the vpd data.
**-t** \#\# Time out after \#\# seconds. (Default is 30.)

file The PCI id number of the HCA (for example, "2:00.0"),

> the device name (such as "mlx4\_0") the absolute path to the device
> ("/sys/class/infiniband/mlx4\_0/device") or '-' to read VPD data from
> the standard input.

keyword(s): Only display the requested information. (ID, PN, EC, SN, etc...)

# SEE ALSO

The full documentation for **mstvpd** is maintained as a Texinfo manual.
If the **info** and **mstvpd** programs are properly installed at your
site, the command

> **info mstvpd**

should give you access to the complete manual.
