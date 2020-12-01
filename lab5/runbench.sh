#!/bin/bash

./cpubench flops single 10 1
./cpubench flops single 10 2
./cpubench flops single 10 4

./cpubench flops single 100 1
./cpubench flops single 100 2
./cpubench flops single 100 4

./cpubench flops single 1000 1
./cpubench flops single 1000 2
./cpubench flops single 1000 4

./cpubench flops double 10 1
./cpubench flops double 10 2
./cpubench flops double 10 4

./cpubench flops double 100 1
./cpubench flops double 100 2
./cpubench flops double 100 4

./cpubench flops double 1000 1
./cpubench flops double 1000 2
./cpubench flops double 1000 4

./cpubench matrix single 1024 1
./cpubench matrix single 1024 2
./cpubench matrix single 1024 4

./cpubench matrix single 4096 1
./cpubench matrix single 4096 2
./cpubench matrix single 4096 4

./cpubench matrix single 6144 1 #tried multiples of 1024 on fourier and this was the lowest one that worked
./cpubench matrix single 6144 2 # 7*1024 = 7168 works for single but not double so for consistency sake I used 6144 for both
./cpubench matrix single 6144 4

./cpubench matrix double 1024 1
./cpubench matrix double 1024 2
./cpubench matrix double 1024 4

./cpubench matrix double 4096 1
./cpubench matrix double 4096 2
./cpubench matrix double 4096 4

./cpubench matrix double 6144 1
./cpubench matrix double 6144 2
./cpubench matrix double 6144 4

