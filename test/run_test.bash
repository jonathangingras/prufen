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

function select_return_assertion {
    if [[ $1 == *"shouldpass_"* ]]; then
        echo returns_zero
        return 0
    fi

    if [[ $1 == *"shouldfail_"* ]]; then
        echo returns_non_zero
        return 0
    fi

    return 1
}

run_test $(select_return_assertion $1) $1
