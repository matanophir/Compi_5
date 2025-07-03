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
inter_folder="inter"

# Create inter folder if it doesn't exist
mkdir -p "$inter_folder"

for test_in in $t_folder/t*.in; do
    test_name=$(basename "$test_in" .in)
    test_out="$t_folder/${test_name}.out"
    test_res="$t_folder/${test_name}.res"
    inter_file="$inter_folder/${test_name}.ll"

    echo -n "Running $test_name... "

    # Generate LLVM IR
    ./hw5 < "$test_in" > "$inter_file" 2>&1
    
    # Check if compilation was successful
    if [ $? -ne 0 ]; then
        echo "FAILED (compilation error, see $inter_file)"
        cp "$inter_file" "$test_res"
        ((failed++))
        continue
    fi

    # Run the LLVM IR through lli
    lli "$inter_file" > "$test_res" 2>&1

    if diff "$test_res" "$test_out" > /dev/null; then
        echo "PASSED"
        rm "$test_res"
        ((passed++))
    else
        echo "FAILED (see $test_res and $inter_file)"
        ((failed++))
    fi
done

echo
echo "Summary:"
echo "Passed: $passed"
echo "Failed: $failed"
