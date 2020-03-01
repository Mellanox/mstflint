
# NAME

mstfwtrace

# SYNOPSIS

usage: mstfwtrace **-d**|-\-device DEVICE \[options\]

# DESCRIPTION

## optional arguments:

  - **-h**, **-\-help**  
    show this help message and exit

  - **-v**, **-\-version**
    Print tool version.

# OPTIONS

  - **-d** DEVICE, **-\-device** DEVICE  
    PCI device name

  - **-\-tracer\_mode** TRACER\_MODE  
    Tracer mode \[MEM\]

  - **-\-real\_ts**  
    Print real timestamps in \[hh:mm:ss:nsec\]

  - **-\-ignore\_old\_events**  
    Ignore collecting old events

## Format:

  - **-i** IRISC, **-\-irisc** IRISC  
    Irisc name \[all\]

  - **-s**, **-\-stream**  
    Run in streaming mode

  - **-m** MASK, **-\-mask** MASK  
    Trace class mask, use "+" to enable multiple classes or use integer
    format, e.g: **-m** class1+class2+... or 0xff00ff00

  - **-l** LEVEL, **-\-level** LEVEL  
    Trace level

Device Specific Info: ====================

> ConnectIB: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> SwitchIB: Trace classes:
> 
> class1, class2
> 
> ConnectX4: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> ConnectX5: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> BlueField: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> ConnectX6: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> ConnectX6DX: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING
IFARM, ICMD, PCI, DC\_CLEANUP, PHY\_ETH VIRT

> Spectrum: Trace classes:
> 
> class1, class2
> 
> ConnectX4LX: Trace classes:
> 
> DEBUG\_INIT, INIT, ICM, ICM\_FREE\_LIST, HOST\_MNG CMD\_IF, PHY\_IB,
> PHY\_RX\_ADAP, PHY\_EYE\_OPN, PHY\_COMMON PHY\_MANAGER, PWR, FLR,
> ICM\_ACCESS, MAD RXT\_CHECKS, I2C, TRANSPORT, FW\_LL, RX\_ERRORS
> CMD\_DRIVER, PROFILING, MANAGEMENT, FLASH, STEERING IFARM, ICMD, PCI,
> DC\_CLEANUP, PHY\_ETH VIRT
> 
> SwitchIB2: Trace classes:
> 
> class1, class2
> 
> Quantum: Trace classes:
> 
> class1, class2
> 
> Spectrum2: Trace classes:
> 
> class1, class2

# SEE ALSO

The full documentation for **mstfwtrace,** is maintained as a Texinfo
manual. If the **info** and **mstfwtrace,** programs are properly
installed at your site, the command

> **info mstfwtrace,**

should give you access to the complete manual.
