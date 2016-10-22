#!/bin/bash
ls | grep '^T' | while read fn
do
	./qwe.exe < $fn > tests/'out'$fn
	echo -e '\e[45m  ===>' $fn '<===  \e[0m'
	head -2 $fn 
	diff -q  tests/'out'$fn tests/'rout'$fn
		if [[ $? == "0" ]]
		then
				tail -1 tests/'out'$fn
				echo -e '\e[32m----TEST PASSED----\e[0m'
		else
				tail -1 tests/'out'$fn
				tail -1 tests/'rout'$fn
				echo -e '\e[31m----TEST FAILED----\e[0m'
				#diff tests/'out'$fn tests/'rout'$fn
		fi
	echo ' '

done
