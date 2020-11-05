#!/bin/bash

# iterate over the program parameters using nested for loops
# program usage: ./fileio <workload> <block_size> <num_procs>
#     - workload: WS (write-sequential), WR (write-random), RS (read sequential), RR (read random)
#     - block_size: 4K, 64K, 1M, 16M
#     - num_procs: 1 2 4 8
make
mkdir files

fallocate -l 1G files/1G1.txt
for i in $(seq 1 2)
do fallocate -l 512M files/512M$i.txt
done
for i in $(seq 1 4)
do fallocate -l 256M files/256M$i.txt
done
for i in $(seq 1 8)
do fallocate -l 128M files/128M$i.txt
done
fallocate -l 4M files/4M1.txt
for i in $(seq 1 2)
do fallocate -l 2M files/2M$i.txt
done
for i in $(seq 1 4)
do fallocate -l 1M files/1M$i.txt
done
for i in $(seq 1 8)
do fallocate -l 512K files/512K$i.txt
done

for workload in WS RS WR RR
do
	for num_procs in 1 2 4 8
	do
		if [ $num_procs = 1 ]
		then total_bytes="1073741824"
		fi
		if [ $num_procs = 2 ]
		then total_bytes="536870912"
		fi
		if [ $num_procs = 4 ]
		then total_bytes="268435456"
		fi
		if [ $num_procs = 8 ]
		then total_bytes="134217728"
		fi
		for block_size in 64K 1M 16M
		do
		./fileio $workload $block_size $num_procs $total_bytes
		done
	done
done

block_size="4K"
for workload in WR RR
do
	for num_procs in 1 2 4 8
	do
		if [ $num_procs = 1 ]
		then total_bytes="4194304"
		fi
		if [ $num_procs = 2 ]
		then total_bytes="2097152"
		fi
		if [ $num_procs = 4 ]
		then total_bytes="1048576"
		fi
		if [ $num_procs = 8 ]
		then total_bytes="524288"
		fi
	./fileio $workload $block_size $num_procs $total_bytes
	done
done

#Feel free to comment out this next line if you want to see what the file directory looks like
rm -rf files/



