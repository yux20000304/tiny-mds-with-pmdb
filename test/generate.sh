#!/bin/sh
i=0

rm ./data.txt

while [ $i -ne 100 ]
do
        i=$(($i+1))
        echo "mkdir haha$i" >> ./data.txt
done