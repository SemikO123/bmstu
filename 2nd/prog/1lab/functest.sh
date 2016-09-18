#!/bin/bash
ls | grep '^tst' | while read filename
do
	./1lab.exe $filename 'out'$filename > outputtests.txt
	diff -q 'out'$filename testanswers/'out'$filename 
	if [[ $? == "0" ]]
	then
			echo 'TEST WITH FILE' $filename 'PASSED'
	else
			echo 'TEST WITH FILE' $filename 'FAILED'
			diff 'out'$filename testanswers/'out'$filename
	fi

done


