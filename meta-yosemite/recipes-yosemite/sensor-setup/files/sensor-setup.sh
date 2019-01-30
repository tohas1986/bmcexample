#!/bin/sh
#
# Copyright 2014-present Facebook. All Rights Reserved.
#
# This program file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program in a file named COPYING; if not, write to the
# Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA
#

### BEGIN INIT INFO
# Provides:          sensor-setup
# Required-Start:    power-on
# Required-Stop:
# Default-Start:     S
# Default-Stop:
# Short-Description: Power on micro-server
### END INIT INFO

# Eventually, this will be used to configure the various (mostly
# i2c-based) sensors, once we have a kernel version that supports
# doing this more dynamically.
#
# For now, we're using it to install the lm75 and pmbus module so that it
# can detect the fourth temperature sensor, which is located
# on the uServer, which doesn't get power until power-on executes.
#
# Similarly, the pmbus sensor seems to have an easier time of
# detecting the NCP4200 buck converters after poweron.  This has not
# been carefully explored.

modprobe lm75
modprobe tmp421
modprobe pmbus
modprobe at24


echo 24c02 0x50 > /sys/devices/platform/ast-i2c.3/i2c-3/new_device
echo 24c02 0x52 > /sys/devices/platform/ast-i2c.3/i2c-3/new_device

echo tmp75 0x49 > /sys/devices/platform/ast-i2c.6/i2c-6/new_device
echo tmp75 0x4b > /sys/devices/platform/ast-i2c.6/i2c-6/new_device
echo tmp75 0x4c > /sys/devices/platform/ast-i2c.6/i2c-6/new_device
echo tmp75 0x4e > /sys/devices/platform/ast-i2c.6/i2c-6/new_device
echo tmp421 0x4f > /sys/devices/platform/ast-i2c.6/i2c-6/new_device

# setup ADC channels

ADC_PATH="/sys/devices/platform/ast_adc.0"

# Enable the ADC inputs;  adc0 - adc7 are connected to various voltage sensors
#
#  adc0 P5V_STBY_SCALED           r1: 5.11k,   r2: 3.48k,  v2: 0mv
#  adc1 P12V_STBY_SCALED          r1: 5.11k,   r2: 1.02k,  v2: 0mv
#  adc2 P3V3_STBY_SCALED          r1: 5.11k,   r2: 8.25k,  v2: 0mv
#  adc3 P12V_STBY_SLOT2_SCALED    r1: 5.11k,   r2: 1.02k,  v2: 0mv
#  adc4 P12V_STBY_SLOT1_SCALED    r1: 5.11k,   r2: 1.02k,  v2: 0mv
#  adc5 P12V_STBY_SLOT4_SCALED    r1: 5.11k,   r2: 1.02k,  v2: 0mv
#  adc6 P12V_STBY_SLOT3_SCALED    r1: 5.11k,   r2: 1.02k,  v2: 0mv
#  adc7 P3V3_SCALED               r1: 5.11k,   r2: 8.25k,  v2: 0mv

config_adc() {
    channel=$1
    r1=$2
    r2=$3
    v2=$4
    echo $r1 > ${ADC_PATH}/adc${channel}_r1
    echo $r2 > ${ADC_PATH}/adc${channel}_r2
    echo $v2 > ${ADC_PATH}/adc${channel}_v2
    echo 1 > ${ADC_PATH}/adc${channel}_en
}

config_adc 0  5100  8200 0
config_adc 1  5110  1000 0
config_adc 2  5100  8200 0
config_adc 3  5100  3400 0
config_adc 4     0     1 0
config_adc 5     0     1 0
config_adc 6     0     1 0
config_adc 7     0     1 0
config_adc 8  5110  20500 0
config_adc 9     0     1 0
config_adc 10    0     1 0
config_adc 11    0     1 0
config_adc 12    0     1 0
config_adc 13    0     1 0
config_adc 14    0     1 0
config_adc 15    0     1 0



echo 1 > /sys/devices/platform/ast_adc.0/adc0_en
echo 1 > /sys/devices/platform/ast_adc.0/adc1_en
echo 1 > /sys/devices/platform/ast_adc.0/adc2_en
echo 1 > /sys/devices/platform/ast_adc.0/adc3_en
echo 1 > /sys/devices/platform/ast_adc.0/adc4_en
echo 1 > /sys/devices/platform/ast_adc.0/adc5_en
echo 1 > /sys/devices/platform/ast_adc.0/adc6_en
echo 1 > /sys/devices/platform/ast_adc.0/adc7_en
echo 1 > /sys/devices/platform/ast_adc.0/adc8_en
echo 1 > /sys/devices/platform/ast_adc.0/adc9_en
echo 1 > /sys/devices/platform/ast_adc.0/adc10_en
echo 1 > /sys/devices/platform/ast_adc.0/adc11_en
echo 1 > /sys/devices/platform/ast_adc.0/adc12_en
echo 1 > /sys/devices/platform/ast_adc.0/adc13_en
echo 1 > /sys/devices/platform/ast_adc.0/adc14_en
echo 1 > /sys/devices/platform/ast_adc.0/adc15_en

# i2cset -y -f 10 0x40 0xd4 0x3f1c w
#rmmod adm1275
#modprobe adm1275
