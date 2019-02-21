#!/bin/bash

sensors tmp75-i2c-6-49 > /www/pages/sensors.log
LINE1=`sed -n 3p /www/pages/sensors.log`
sensors tmp75-i2c-6-4b > /www/pages/sensors.log
LINE2=`sed -n 3p /www/pages/sensors.log`
sensors tmp75-i2c-6-4c > /www/pages/sensors.log
LINE3=`sed -n 3p /www/pages/sensors.log`
sensors tmp75-i2c-6-4e > /www/pages/sensors.log
LINE4=`sed -n 3p /www/pages/sensors.log`
sensors tmp421-i2c-6-4f > /www/pages/sensors.log
LINE5=`sed -n 3p /www/pages/sensors.log`

VAL= echo ${LINE1:15:1}${LINE1:16:1}${LINE1:17:1}${LINE1:18:1}${LINE1:19:1} > /www/pages/sentmp.log
VAL1=`sed -n 1p /www/pages/sentmp.log`
VAL= echo ${LINE2:15:1}${LINE2:16:1}${LINE2:17:1}${LINE2:18:1}${LINE2:19:1} > /www/pages/sentmp.log
VAL2=`sed -n 1p /www/pages/sentmp.log`
VAL= echo ${LINE3:15:1}${LINE3:16:1}${LINE3:17:1}${LINE3:18:1}${LINE3:19:1} > /www/pages/sentmp.log
VAL3=`sed -n 1p /www/pages/sentmp.log`
VAL= echo ${LINE4:15:1}${LINE4:16:1}${LINE4:17:1}${LINE4:18:1}${LINE4:19:1} > /www/pages/sentmp.log
VAL4=`sed -n 1p /www/pages/sentmp.log`
VAL= echo ${LINE1:18:1}${LINE1:19:1}${LINE1:20:1}${LINE1:21:1}${LINE1:22:1} > /www/pages/sentmp.log 
VAL5=`sed -n 1p /www/pages/sentmp.log`

STR="[[\"Sensor1\",\"$VAL1\"],[\"Sensor2\",\"$VAL2\"],[\"Sensor3\",\"$VAL3\"],[\"Sensor4\",\"$VAL4\"],[\"Sensor5\",\"$VAL5\"]]"

echo $STR
