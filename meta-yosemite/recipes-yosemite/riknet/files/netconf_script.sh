#!/bin/bash

#LINE=`sed -n 1p netconf`
#LINE2=`cat netconf`
#LINE='cat /sys/devices/platform/ast-i2c.3/i2c-3/3-0050'
#LINE='cat /sys/devices/platform/ast-i2c.3/i2c-3/3-0052'

#DEBUG only - TODO - Remove it
LINE="tohas n 192.168.10.10 255.255.255.0 192.168.10.1"

IFS=' ' read -r -a Q <<< $LINE

#echo $LINE
#echo "${Q[0]}"
#echo "${Q[1]}"
#echo "${Q[2]}"
#echo "${Q[3]}"
#echo "${Q[4]}"
#echo $LINE2

DHCPVDEF=n
HNAME=${Q[0]}
DHCPV=${Q[1]}
IP=${Q[2]}
NETMASK=${Q[3]}

if [[ $DHCPV == $DHCPVDEF ]]; then
	ifconfig eth0:1 $IP netmask $NETMASK
fi


