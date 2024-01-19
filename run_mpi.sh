#!/bin/bash

EXECUTABLE="./Franklin-for-testing"

OUTPUT_FILE="timp_executie.txt"

# We execute the program for 25, 50, ... 400 processes
for (( num_procs=25 ; num_procs<=400 ; num_procs+=25 ))
do
    echo "Rulare cu $num_procs procese..."
    echo -n "$num_procs " >> $OUTPUT_FILE
    mpirun -np $num_procs --oversubscribe $EXECUTABLE >> $OUTPUT_FILE
done

echo "Done! Rezultate: $OUTPUT_FILE."
