#!/bin/bash

while [ 1 ]				
do
sensors > /www/pages/sensors.log
sleep 1s
#TODO: Раскоментировать при тестировании на плате с полным набором термодатчиков
#/usr/local/fbpackages/rikfans/rikfans
#sleep 5s
done