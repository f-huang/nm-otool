#!/bin/sh

#############

bin_mine=./ft_nm
bin_theirs=nm

##############

IFS=';'
command_args=(\
"ft_nm;"\
"-r ft_nm;"\
"-nr ft_nm;"\
"-U ft_nm;"\
)

#############
output_mine="mine"
output_theirs="theirs"
##############

for command_arg in $command_args; do
	args=($command_arg)
	IFS=" "
	$bin_mine ${args[@]} > $output_mine
	$bin_theirs ${args[@]} > $output_theirs
	diff $output_mine $output_theirs

	if [ $? -eq 0 ]; then
		echo "\033[0;32m""√ \t$command_arg""\033[0;0m"
	else
		echo "\033[0;31m""✗ \t$command_arg""\033[0;0m"
	fi
done
