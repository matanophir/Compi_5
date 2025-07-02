#!/bin/bash

make clean && make
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Compilation succeeded."
echo "Running tests..."

passed=0
failed=0
t_folder="hw5-tests"

for test_in in $t_folder/t*.in; do
    test_name=$(basename "$test_in" .in)
    test_out="$t_folder/${test_name}.out"
    test_res="$t_folder/${test_name}.res"

    echo -n "Running $test_name... "

    ./hw5 < "$test_in" 2>&1 > "$test_res"

    if diff "$test_res" "$test_out" > /dev/null; then
        echo "PASSED"
        rm "$test_res"
        ((passed++))
    else
        echo "FAILED (see $test_res)"
        ((failed++))
    fi
done

echo
echo "Summary:"
echo "Passed: $passed"
echo "Failed: $failed"
