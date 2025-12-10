## Mellanox Technologies - ibdump HCA Sniffing Utility
Project owner: Itay Avraham, itayavr@mellanox.com

# Table of Contents
1. Overview
2. How to get Wireshark
3. Known Issues
4. How to Compile




# 1. Overview
The ibdump tool dumps InfiniBand traffic that flows to and from Mellanox 
adapter cards and provides a similar functionality to the tcpdump tool 
on an Ethernet network.
The ibdump tool generates a packet dump file in .pcap format, the file can 
be loaded by the Wireshark tool for graphical traffic analysis.  
Using this tool enables the user to analyze network behavior and performance, 
and to debug applications that send or receive InfiniBand network traffic.
To display a help message which details the tools options run "ibdump -h". 




# 2. How to Get Wireshark
Download the current release from www.wireshark.org for a Linux or Windows
environment.

Note: 
Although ibdump is a Linux application, the generated .pcap file may be
analyzed on either operating system.

Note:
The InfiniBand plug-in released with the current Wireshark version has a basic
IB packets parser which includes Verbs level, IPoIB adn some SMP Mads parsing. 
To get the latest version of the IB plugin, which includes EoIB, 
SDP, and FCoIB parsing, download the latest Wireshark daily build:
- For Windows: Download the exe installer from
  http://www.wireshark.org/download/automated/win32/ and install it
- For Linux: Download the Wireshark dev source tarball from
  http://www.wireshark.org/download/automated/src/ and build it




# 3. Known Issues
* ibdump may encounter packet drops upon a burst of more than 4096 (or
  2^max-burst) packets.
* Packets loss is not reported by ibdump.
* Outbound retransmitted and multicast packets may not be collected correctly.
* ibdump may stop capturing packets when run on the same port of the Subnet
  Manager (E.G.: opensm). It is advised not to run the SM and ibdump on the same
  port.
* Ibdump does not support 5th gen IB devices (ConnectX-4 & newer) when compiled without FW tools (when using make WITHOUT_FW_TOOLS=yes).
  In order to use Ibdump on 5th generation ib devices please compile with one of the other options below.




# 4. How to Compile
| Setup desired                      | Compilation command                                    |
| ---------------------------------- | :-----------------------------------------------------:|
| MFT Library + RDMA_CORE            | make [install]                                         |
| MFT Library + LIBS_EXP     	       | make LIBS_EXP=yes [install]                            |
| MSTFLINT Library + RDMA_CORE       | make WITH_MSTFLINT=yes [install]                       |
| Without FW tools	                 | make WITHOUT_FW_TOOLS=yes [install]                    |
