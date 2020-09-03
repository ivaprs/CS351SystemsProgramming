#!/bin/bash

shuf -i 0-2147483647 -n $2 >> num.txt
base64 -w 100 /dev/urandom | tr -d '/+' | head -n $2 >> words.txt

paste num.txt num.txt words.txt >> $1

rm num.txt
rm words.txt
