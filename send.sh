#!/bin/bash

inFifo="Tmp/inFifo";
outFifo="Tmp/outFifo";
needHelp=0;
serverStart=0;
serverKill=0;
serverPath=".";
serverCore=1;
filePath=${@: -2};
fileArg=${@: -1};


while getopts SKP:C:hi:o: flag
do
	case "${flag}" in
		S) serverStart=1;;
		K) serverKill=1;;
		P) serverPath=${OPTARG};;
		C) serverCore=${OPTARG};;
		h) needHelp=1;;
		i) inFifo=${OPTARG};;
		o) outFifo=${OPTARG};;
	esac
done

if [[ "$serverKill" == 1 ]]; then
	echo "Shutting down server...";
fi

#Server Start
if [[ "$serverStart" == 1 ]]; then
	echo "Starting server...";
	`gnome-terminal -e "$serverPath/labeller $inFifo $outFifo $serverCore"`;
	sleep 1;
	echo "Initializing...";
fi

#Send data to the server
echo "$serverKill $filePath $fileArg" > $inFifo;
echo `cat $outFifo`;

if [[ "$serverKill" == 1 ]]; then
	rm $inFifo;
	rm $outFifo;
	rm -rf 'Tmp/*';
fi

#Code written by:
#      - Nemo Chentre
#
# Last modified: 11/05/2022
