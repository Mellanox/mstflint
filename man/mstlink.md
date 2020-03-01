
# NAME

mstlink, - manual page for mstlink, mstflint 4.13.1, built on Sep 11
2019, 21:09:35. Git SHA Hash: N/A

# SYNOPSIS

> mstlink \[OPTIONS\]
> 
# DESCRIPTION

> The mstlink tool is used to check and debug link status and issues
> related to them. The tool can be used on different links and cables
> (passive, active, transceiver and backplane).
> 
> OPTIONS:

  - **-h** |-\-help  
    : Display help message.

  - **-v** |-\-version  
    : Display version info.

  - **-d** |-\-device  
    \<device\> : Perform operation for a specified mst device

  - **-p** |-\-port  
    \<port\_number\> : Port Number

  - **-\-port\_type**  
    \<port\_type\> : Port Type \[NETWORK(Default)/PCIE\]

  - **-\-depth**  
    \<depth\> : depth level of the DUT of some hierarchy (PCIE only)

  - **-\-pcie\_index**  
    \<pcie\_index\> : PCIe index number (Internal domain index) (PCIE
    only)

  - **-\-node**  
    \<node\> : the node within each depth (PCIE only)
    
    QUERIES:

  - **-\-show\_links**  
    : Show valid PCIe links (PCIE only)

  - **-m** |-\-show\_module  
    : Show Module Info

  - **-c** |-\-show\_counters  
    : Show Physical Counters and BER Info

  - **-e** |-\-show\_eye  
    : Show Eye Opening Info

  - **-\-show\_fec**  
    : Show FEC Capabilities

  - **-\-show\_serdes\_tx**  
    : Show Transmitter Info

  - **-\-show\_device**  
    : General Device Info

  - **-\-show\_ber\_monitor**  
    : Show BER Monitor Info (not supported for HCA)

  - **-\-show\_external\_phy**  
    : Show External PHY Info
    
    COMMANDS:

  - **-a** |-\-port\_state \<port\_state\>  
    : Configure Port State \[UP(up)/DN(down)/TG(toggle)\]

  - **-s** |-\-speeds  
    \<speeds\> : Configure Speeds \[speed1,speed2,...\]

  - **-\-link\_mode\_force**  
    : Configure Link Mode Force (Disable AN)

  - **-l** |-\-loopback  
    \<loopback\> : Configure Loopback Mode \[NO(no loopback)/PH(phy
    loopback)/EX(external loopback)\]

  - **-k** |-\-fec  
    \<fec\_override\> : Configure FEC \[AU(Auto)/NF(No-FEC)/FC(FireCode
    FEC)/RS(RS-FEC)\]

  - **-\-fec\_speed**  
    \<fec\_speed\> : Speed to Configure FEC \[100G/50G/25G/...\]
    (Default is Active Speed)

  - **-\-serdes\_tx**  
    \<params\> : Configure Transmitter Parameters
    \[polarity,ob\_tap0,...\]

  - **-\-serdes\_tx\_lane** \<transmitter\_lane\>  
    : Transmitter Lane to Set (Optional - Default All Lanes)

  - **-\-database**  
    : Save Transmitter Configuration for Current Speed Permanently
    (Optional)

  - **-\-test\_mode**  
    \<prbs\_mode\> : Physical Test Mode Configuration
    \[EN(enable)/DS(disable)/TU(perform tuning)\]

  - **-\-rx\_prbs**  
    \<rx\_prbs\_mode\> : RX PRBS Mode \[PRBS31(Default)/PRBS7/...\]
    (Optional - Default PRBS31)

  - **-\-tx\_prbs**  
    \<tx\_prbs\_mode\> : TX PRBS Mode \[PRBS31(Default)/PRBS7/...\] (Optional - Default PRBS31)

  - **-\-rx\_rate**  
    \<rx\_lane\_rate\> : RX Lane Rate \[EDR(Default)/25G/10G/...\]
    (Optional - Default 25G)

  - **-\-tx\_rate**  
    \<tx\_lane\_rate\> : TX Lane Rate \[EDR(Default)/25G/10G/...\]
    (Optional - Default 25G)

  - **-b** |-\-ber\_collect \<csv\_file\>  
    : Port Extended Information Collection \[CSV File\]

  - **-\-ber\_limit**  
    \<limit\_criteria\> : BER Limit Criteria
    \[Nominal(Default)/Corner/Drift\] (Optional - Default Nominal)

  - **-\-iteration**  
    \<iteration\> : Iteration Number of BER Collection

  - **-\-pc**  
    : Clear Counters

  - **-\-set\_external\_phy**  
    : Set External PHY (not supported for HCA)

  - **-\-twisted\_pair\_force\_mode** \<twisted\_pair\_force\_mode\>  
    : Twisted Pair Force Mode \[MA(Master)/SL(Slave)\]
    
    # EXAMPLES
  - get info of \<device\>, \<port\_number\>:
    
    mstlink **-d** \<device\> **-p** \<port\_number\>
    
    get info of \<device\>, \<port\_number\> and BER Counters:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-c**
    
    get info of \<device\>, \<port\_number\> and Transmitter Parameters:
    
    mstlink **-d** \<device\> **-p** \<port\_number\>
    **-\-show\_serdes\_tx**

  - Configure Port State:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-port\_state** UP

  - Configure Port Speeds:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-speeds** 25G,50G,100G

  - Configure FEC:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-fec** RS

  - Configure Port for Physical Test Mode:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-test\_mode**
    EN (**-\-rx\_prbs** PRBS31 **-\-rx\_rate** 25G **-\-tx\_prbs** PRBS7
    **-\-tx\_rate** 10G)

  - Perform PRBS Tuning:
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-test\_mode** TU
    
    Configure Transmitter Parameters (on lane, to database):
    
    mstlink **-d** \<device\> **-p** \<port\_number\> **-\-serdes\_tx**
    \<polarity\>,\<ob\_tap0\>,\<ob\_tap1\>,\<ob\_tap2\>,\<ob\_bias\>,\<ob\_preemp\_mode\>
    (**-\-serdes\_tx\_lane** \<lane number\>) (**-\-database**)

# SEE ALSO

The full documentation for **mstlink,** is maintained as a Texinfo
manual. If the **info** and **mstlink,** programs are properly installed
at your site, the command

> **info mstlink,**

should give you access to the complete manual.
