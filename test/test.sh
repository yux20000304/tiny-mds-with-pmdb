#!/bin/bash

rm ./*.poolset



#gnome-terminal -t "master" -- bash -c "../build/server -s8081 -n3;exec bash;"
#
#gnome-terminal -t "slave1" -- bash -c "../build/server -s8082 -i127.0.0.1 -p8081;exec bash;"
#
#gnome-terminal -t "slave2" -- bash -c "../build/server -s8083 -i127.0.0.1 -p8081;exec bash;"
#
#gnome-terminal -t "slave3" -- bash -c "../build/server -s8084 -i127.0.0.1 -p8081;exec bash;"

#gnome-terminal -t "client" -- bash -c "../build/client -i127.0.0.1 -p8081 ;exec bash;"