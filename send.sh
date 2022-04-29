#!/bin/bash

fifo_name="Tmp/inFifo";

outStr="0 $1 $2"



if [[ "$1" == "kill" ]]; then
	echo -1 >$fifo_name;
else
	echo $outStr >$fifo_name;
fi

echo "Communication complete !\n"


echo (cat Tmp/outFifo);



#Code written by:
#      - Nemo Chentre
#
# Last modified: 29/04/2022
