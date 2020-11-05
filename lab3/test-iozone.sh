#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 1KB, 10KB, 1000KB, 1MB
#     - num_procs: 1 2 4

# right now the bash script calls the program with only one configuration
curpwd=$(pwd)
subpwd="/iozone3_490/src/current"
export PATH=$PATH:"$curpwd$subpwd"

for i in 4 64 1m 16m
do
	for j in 1 2 4 8
	do
		if [ $i = 4 ]
		then
			if [ $j = 1 ]
			then iozone -O -i0 -i1 -i2 -I -t$j -s4m -r$i
			elif [ $j = 2 ]
			then iozone -O -i0 -i1 -i2 -I -t$j -s2m -r$i
			elif [ $j = 4 ]
			then iozone -O -i0 -i1 -i2 -I -t$j -s1m -r$i
			else
			iozone -O -i0 -i1 -i2 -I -t$j -s512 -r$i
			fi
		else
			if [ $j = 1 ]
			then iozone -i0 -i1 -i2 -I -t$j -s1g -r$i
			elif [ $j = 2 ]
			then iozone -i0 -i1 -i2 -I -t$j -s512m -r$i
			elif [ $j = 4 ]
			then iozone -i0 -i1 -i2 -I -t$j -s256m -r$i
			else
			iozone -i0 -i1 -i2 -I -t$j -s128m -r$i
			fi
		fi
	done
done
