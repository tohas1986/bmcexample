#!/bin/bash

function get_voltage
{
  ADC_DIR=/sys/devices/platform/ast_adc.0
  set -e

  echo "$(cat $ADC_DIR/adc${1}_value)"
}

VNAME1="P3V3_BASE"
VNAME2="P12V_BASE"
VNAME3="P3V3_AUX"
VNAME4="P5V_BASE"
VNAME5="P1V05_STBY_PCH"
VNAME6="P1V05_PCH"
VNAME7="P1V5_STBY_PCH"
VNAME8="PVCCIO"
VNAME9="DRAM_PVPP"
VNAME10="DRAM_GH"
VNAME11="DRAM_EF"
VNAME12="DRAM_CD"
VNAME13="DRAM_AB"
VNAME14="CPU1_PVCCIN"
VNAME15="CPU0_PVCCIN"

VVAL1=`get_voltage 0` || exit 1
VVAL2=`get_voltage 1` || exit 1
VVAL3=`get_voltage 2` || exit 1
VVAL4=`get_voltage 3` || exit 1
VVAL5=`get_voltage 4` || exit 1
VVAL6=`get_voltage 5` || exit 1
VVAL7=`get_voltage 6` || exit 1
VVAL8=`get_voltage 7` || exit 1
VVAL9=`get_voltage 8` || exit 1
VVAL10=`get_voltage 9` || exit 1
VVAL11=`get_voltage 10` || exit 1
VVAL12=`get_voltage 11` || exit 1
VVAL13=`get_voltage 12` || exit 1
VVAL14=`get_voltage 13` || exit 1
VVAL15=`get_voltage 14` || exit 1

STR="[[\"$VNAME1\",\"$VVAL1\"],[\"$VNAME2\",\"$VVAL2\"],[\"$VNAME3\",\"$VVAL3\"],[\"$VNAME4\",\"$VVAL4\"],[\"$VNAME5\",\"$VVAL5\"],[\"$VNAME6\",\"$VVAL6\"],[\"$VNAME7\",\"$VVAL7\"],[\"$VNAME8\",\"$VVAL8\"],[\"$VNAME9\",\"$VVAL9\"],[\"$VNAME10\",\"$VVAL10\"],[\"$VNAME11\",\"$VVAL11\"],[\"$VNAME12\",\"$VVAL12\"],[\"$VNAME13\",\"$VVAL13\"],[\"$VNAME14\",\"$VVAL14\"],[\"$VNAME15\",\"$VVAL15\"]]"

echo $STR
