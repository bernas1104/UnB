#!/bin/bash

dir_set=('obj' 'bin')

for dir in ${dir_set[@]}; do
	if [ ! -d $dir ]; then
		echo -e "(I) Creating required build directory $dir"
		mkdir $dir
	fi
done

exit 0