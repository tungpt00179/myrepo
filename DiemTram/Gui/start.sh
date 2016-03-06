#!/bin/sh
a=0
/usr/bin/navit&
while [ $a -lt 10 ]
do
	sleep 3
	echo "start taxi app" > ~/cheap.log
	cd /home/pi/bin/CheapTaxi
	./GuiDriver >> ~/cheap.log 2>&1
done
