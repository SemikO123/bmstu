#!/bin/bash
ls | grep '^in' | while read name 
do
	.././main <$name >'out'$name
	diff -q 'out'$name answers/'out'$name 1>/dev/null
	if [[ $? == "0" ]]
	then
		echo 'Test with file' $name 'passed'
	else
		echo 'Test with file' $name 'failed' 
		diff 'out'$name answers/'out'$name 
	fi

done