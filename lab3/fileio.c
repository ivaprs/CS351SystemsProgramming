#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG "* running fileio %s workload with %s blocks and %s process(es)\n"

#define USAGE "usage: ./fileio <workload> <block_size> <num_procs> \n" \
"     - workload: WS, WR, RS, RR \n" \
"     - block_size: 4KB, 64KB, 1MB, 16MB \n" \
"     - num_procs: 1, 2, 4, 8 \n" \
"     - WS = write-sequential \n" \
"     - WR = write-random \n" \
"     - RS = read-sequential \n" \
"     - RR = read-random \n"

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf(USAGE);
        exit(1);
    } else {
        printf(MSG, argv[1], argv[2], argv[3]);
    }

    return 0;
}
