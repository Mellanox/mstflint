MELLANOX TECHNOLOGIES LTD.


*******************************
MSTFLINT DRIVER FOR SECURE BOOT
*******************************

This kernel was developed to add support for mstflint to work under secure boot systems.

To work with this driver need to compile and then to insmod.

1. Run make
2. insmod ./mstflint_driver.ko
3. Run your tools with the DBDF device name format:
    > mstflint -d 05:00.0 q
    > mstmcra 05:00.0 0xf0014

    