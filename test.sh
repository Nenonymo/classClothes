#!/bin/bash

testBatch=$1
batchFolders="Tests/test"

echo $testBatch


while IFS="," read -r pId pPath pLabel
do
	echo "Id: $pId, path:$pPath, label:$pLabel"
	echo 0 $pPath $pLabel > "Tmp/inFifo"
	echo `cat Tmp/outFifo`
	wait

done < <(tail -n +2 "$batchFolders$testBatch.csv")

echo done
