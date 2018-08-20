#!/bin/bash
while true; do
    ./data > data.in
    ./std <data.in >std.out
    ./sol <data.in > sol.out
    if diff std.out sol.out; then
        printf "AC\n"
    else
        printf "Wa\n"
        cat sol.out std.out
        exit 0
    fi
done
