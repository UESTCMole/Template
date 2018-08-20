#!/bin/bash
while true; do
    ./data > data.in
    ./jstd <data.in >jstd.out
    ./j <data.in > j.out
    if diff jstd.out j.out; then
        printf "AC\n"
    else
        printf "Wa\n"
        exit 0
    fi
done
