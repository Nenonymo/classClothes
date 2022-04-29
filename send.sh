#!/bin/bash

fifo_name="Tmp/inFifo";

outStr="$1 $2"

echo $outStr >$fifo_name;
