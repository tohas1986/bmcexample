#!/bin/bash

FAN1=$(echo "$QUERY_STRING" | sed -n 's/^.*fan1=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN2=$(echo "$QUERY_STRING" | sed -n 's/^.*fan2=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN3=$(echo "$QUERY_STRING" | sed -n 's/^.*fan3=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN4=$(echo "$QUERY_STRING" | sed -n 's/^.*fan4=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN5=$(echo "$QUERY_STRING" | sed -n 's/^.*fan5=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN6=$(echo "$QUERY_STRING" | sed -n 's/^.*fan6=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN7=$(echo "$QUERY_STRING" | sed -n 's/^.*fan7=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
FAN8=$(echo "$QUERY_STRING" | sed -n 's/^.*fan8=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
MODE=$(echo "$QUERY_STRING" | sed -n 's/^.*fanauto=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
MODEDEF=off

if [ "$MODE" = "$MODEDEF" ]
then
    killall autofan.sh
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN1 1
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN2 2
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN3 3
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN4 4
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN5 5
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN6 6
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN7 7
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN8 8
else
	killall autofan.sh
	./autofan.sh &
fi

