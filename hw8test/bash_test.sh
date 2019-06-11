#!/bin/bash
make
# ~ test cases 1 - 9
counter=1
while [ $counter -le 9 ]
do
    g++ -O3 test.cc test_case_0$counter.cc hw8.a -o test
    echo -n $counter ": "
    ./test
    ((counter++))
done
# test cases 10 - 38
while [ $counter -le 50 ]
do
    g++ -O3 test.cc test_case_$counter.cc hw8.a -o test
    echo -n $counter": "
    ./test
    ((counter++))
done
