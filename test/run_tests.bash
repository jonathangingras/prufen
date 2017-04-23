#!/bin/bash


function run_test {
    TESTER=$1
    CMD=${@:2}

    $TESTER $CMD
    if [ $? -eq 0 ]; then
        echo
        echo ' ========> PASSED:' $CMD
        echo
        return 0
    else
        echo
        echo ' ========> FAILED:' $CMD
        echo
        exit 1
    fi
}

function returns_zero {
    echo -n testing zero for \`$@\'' : '

    "$@"
    if [ $? -eq 0 ]; then
        return 0
    else
        return 1
    fi
}

function returns_non_zero {
    echo -n testing non-zero for \`$@\'' : '

    "$@"
    if [ $? -eq 0 ]; then
        return 1
    else
        return 0
    fi
}


ALL_EXEC=$(find . -type f -executable -print)

ZERO_TESTS=""
for i in $ALL_EXEC; do
    if [[ $i == *"shouldpass_"* ]]; then
        ZERO_TESTS="$ZERO_TESTS $i"
    fi
done

NON_ZERO_TESTS=""
for i in $ALL_EXEC; do
    if [[ $i == *"shouldfail_"* ]]; then
        NON_ZERO_TESTS="$NON_ZERO_TESTS $i"
    fi
done


###### TESTS THAT SHOULD FAIL ######
for t in $NON_ZERO_TESTS; do
    run_test returns_non_zero $t
done

###### TESTS THAT SHOULD PASS ######
for t in $ZERO_TESTS; do
    run_test returns_zero $t
done
