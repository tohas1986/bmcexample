#!/bin/bash

#Обработка DATA для входного запроса POST
echo "" > /www/pages/fanpost.json

if [ "$REQUEST_METHOD" = "POST" ]; then
    if [ "$CONTENT_LENGTH" -gt 0 ]; then
        while read -n $CONTENT_LENGTH POST_DATA <&0
        do
            echo "${POST_DATA}" >> /www/pages/fanpost.json
         done
    fi
fi

read -a Q <<< `cat fanpost.json|sed -E 's/[{}\"]//g;s/,/ /g'`

SIZE=${#Q[@]}
DEFSIZE=9
echo "$SIZE"
if [[ $SIZE == $DEFSIZE ]]; then
	FAN1=`echo "${Q[0]}"|cut -d : -f 2`
	FAN2=`echo "${Q[1]}"|cut -d : -f 2`
	FAN3=`echo "${Q[2]}"|cut -d : -f 2`
	FAN4=`echo "${Q[3]}"|cut -d : -f 2`
	FAN5=`echo "${Q[4]}"|cut -d : -f 2`
	FAN6=`echo "${Q[5]}"|cut -d : -f 2`
	FAN7=`echo "${Q[6]}"|cut -d : -f 2`
	FAN8=`echo "${Q[7]}"|cut -d : -f 2`

    	killall autofan.sh
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN1 1
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN2 2
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN3 3
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN4 4
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN5 5
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN6 6
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN7 7
	/usr/local/fbpackages/fan_ctrl/set_fan_speed.sh $FAN8 8

	#echo $FAN1 $FAN2 $FAN3 $FAN4 $FAN5 $FAN6 $FAN7 $FAN8

else
	killall autofan.sh
	./autofan.sh &
	#echo "AutoMODE"
fi

