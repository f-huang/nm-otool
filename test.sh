#!/bin/sh

#############

bin_nm_mine=./ft_nm
bin_nm=nm
bin_otool_mine=./ft_otool
bin_otool=otool

##############

IFS=';'

dirs=(\
"/bin;"\
"/usr/bin;"\
)

#############
output_mine="mine"
output_theirs="theirs"
##############

function print_result() {
	diff $output_mine $output_theirs
	if [ $? -eq 0 ]; then
		echo "\033[0;32m""√ \t $1""\033[0;0m"
	else
		echo "\033[0;31m""✗ \t $1""\033[0;0m"
	fi
	rm -r $output_mine $output_theirs
}

function check_nm() {
	$bin_nm_mine $1 > $output_mine
	$bin_nm $1 > $output_theirs
	print_result $1
}

function check_otool() {
	$bin_otool_mine $1 > $output_mine
	$bin_otool -t $1 > $output_theirs
	print_result $1
}

for dir in $dirs; do
	for file in $dir/*; do
		check_nm $file
		check_otool $file
	done
done
