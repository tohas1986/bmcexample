#!/bin/bash

echo "Content-type: text/html"
echo ""

#USERNAME=`echo "$QUERY_STRING" | sed -n 's/^.*name=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"
#AGE=`echo "$QUERY_STRING" | sed -n 's/^.*age=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"
USERNAME=$(echo "$QUERY_STRING" | sed -n 's/^.*name=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
AGE=$(echo "$QUERY_STRING" | sed -n 's/^.*age=\([^&]*\).*$/\1/p' | sed "s/%20/ /g")
echo "<html><head><title>Welcome</title></head>"
echo "<body>"
echo "Welcome to Rikor light httpd server"
echo "Your name is $USERNAME and $AGE years old"
echo "</body></html>"
