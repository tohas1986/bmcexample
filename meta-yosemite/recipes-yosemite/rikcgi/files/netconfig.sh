#!/bin/bash

echo "start" > /www/pages/lognet.log

if [ "$REQUEST_METHOD" = "POST" ]; then
    if [ "$CONTENT_LENGTH" -gt 0 ]; then
        while read -n $CONTENT_LENGTH POST_DATA <&0
        do
            echo "$POST_DATA" >> /www/pages/lognet.log
         done
    fi
fi
