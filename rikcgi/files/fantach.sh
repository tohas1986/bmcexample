#!/bin/bash

function get_speed
{
  PWM_DIR=/sys/devices/platform/ast_pwm_tacho.0
  set -e

  # refer to the comments in init_pwn.sh regarding
  # the fan unit and tacho mapping
  if [ "$#" -eq 0 ]; then
      TACHOS="0:0 1:1 2:2 3:3 4:7 5:6 6:5 7:4"
  elif [ "$#" -eq 1 ]; then
      case "$1" in
      "0")
          TACHOS="0:0"
          ;;
      "1")
          TACHOS="1:1"
          ;;
      "2")
          TACHOS="2:2"
          ;;
      "3")
          TACHOS="3:3"
          ;;
      "4")
          TACHOS="4:7"
          ;;
      "5")
          TACHOS="5:6"
          ;;
      "6")
          TACHOS="6:5"
          ;;
      "7")
          TACHOS="7:4"
          ;;
      *)
          usage
          exit 1
          ;;
      esac
  else
      usage
      exit 1
  fi

  for fan_tacho in $TACHOS; do
      fan=${fan_tacho%%:*}
      tacho=${fan_tacho##*:}
      echo "$(cat $PWM_DIR/tacho${tacho}_rpm)"
  done
}

TACH1=`get_speed 0` || exit 2
TACH2=`get_speed 1` || exit 2
TACH3=`get_speed 2` || exit 2
TACH4=`get_speed 3` || exit 2
TACH5=`get_speed 4` || exit 2
TACH6=`get_speed 5` || exit 2
TACH7=`get_speed 6` || exit 2
TACH8=`get_speed 7` || exit 2

STR="[[\"Fan1\",\"$TACH1\"],[\"Fan2\",\"$TACH2\"],[\"Fan3\",\"$TACH3\"],[\"Fan4\",\"$TACH4\"],[\"Fan5\",\"$TACH5\"],[\"Fan6\",\"$TACH6\"],[\"Fan7\",\"$TACH7\"],[\"Fan8\",\"$TACH8\"]]"

echo $STR



