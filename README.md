##Example C program of TCP server and client that handles both IPv6 and IPv4 on Linux

###Server###
The server program listens on just a IPv6 socket. Linux kernel will automatically allow
this socket to accept both IPv4 and IPv6 connections. Incoming IPv4 address is turned 
into a special form of IPv6 address. For example, 192.168.5.10 will be shown as 
"::ffff:192.168.5.10"


###Client###
The client will automatically detect the format of the client address to determine 
whether to use IPv4 or IPv6 socket to connect. This is done by the glibc function
"getaddrinfo()" internally.

###How to build and run it###
On Linux:

1. make
2. on one terminal, do ./64server
3. on another terminal, do ./64client 127.0.0.1 to connect use IPv4, Or do
   ./64client ::1 to connect using IPv6
