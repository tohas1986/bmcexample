#!/bin/bash

echo 1 > /sys/class/gpio/gpio195/value
sleep 1s
echo out > /sys/class/gpio/gpio195/direction
echo 0 > /sys/class/gpio/gpio195/value
echo 1 > /sys/class/gpio/gpio195/value 

