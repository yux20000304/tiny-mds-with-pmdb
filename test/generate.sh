#!/bin/sh

set -x

rm ./data.txt


for k in $( seq 1 10)
do
    echo "mkdir /aaa${k}" >> ./data.txt
    for l in $(seq 1 10)
    do
        echo "mkdir /aaa${k}/bbb${l}" >> ./data.txt
        for j in $(seq 1 10)
        do
           echo "touch /aaa${k}/bbb${l}/file${j}.txt" >> ./data.txt
        done
    done
done