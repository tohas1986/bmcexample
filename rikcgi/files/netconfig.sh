#!/bin/bash

echo "" > /www/pages/lognet.json

if [ "$REQUEST_METHOD" = "POST" ]; then
    if [ "$CONTENT_LENGTH" -gt 0 ]; then
        while read -n $CONTENT_LENGTH POST_DATA <&0
        do
            echo "$POST_DATA" >> /www/pages/lognet.json
         done
    fi
fi

read -a Q <<< `cat lognet.json|sed -E 's/[{}\"]//g;s/,/ /g'`

HOSTNAME=`echo "${Q[0]}"|cut -d : -f 2`
DHCP=`echo "${Q[1]}"|cut -d : -f 2`
DHCPDEF=no

if [ "$DHCP" = "$DHCPDEF" ]
then
    ADDR=`echo "${Q[2]}"|cut -d : -f 2`
    MASK=`echo "${Q[3]}"|cut -d : -f 2`
    GATE=`echo "${Q[4]}"|cut -d : -f 2`
else
    ADDR=192.168.0.100
    MASK=255.255.255.0
    GATE=192.168.0.1
fi

#DEBUG only - TODO - replace with eeprom write utility
#echo "$HOSTNAME $DHCP $ADDR $MASK $GATE" > /www/pages/netconfig.log
echo "$HOSTNAME $DHCP $ADDR $MASK $GATE" > /sys/devices/platform/ast-i2c.3/i2c-3/3-0050/eeprom
#or
#echo "$HOSTNAME $DHCP $ADDR $MASK $GATE" > /sys/devices/platform/ast-i2c.3/i2c-3/3-0052/eeprom
