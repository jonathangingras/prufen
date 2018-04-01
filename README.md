# Prüfen [![Build Status](https://travis-ci.org/jonathangingras/prufen.svg?branch=master)](https://travis-ci.org/jonathangingras/prufen)

C Unit Test framework for Unix-like systems. Simple, easy, header-only.

## Example:

### sample.c

    #include "prufen/prufen.h"

    pruf_setup(DummyTestCase) { /* optional */
        printf("from setup: ran before each test\n");
    }

    pruf_teardown(DummyTestCase) { /* optional too */
       printf("from teardown: ran after each test\n");
    }
    
    pruf_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {
    	int _1 = 1;
    	int _3 = 3;
    
    	pruf_expect_equal(4, _1 + _3);
    	pruf_expect_true(4 == _1 + _3);
    }

### Compile & run

#### compile:
assuming Prüfen is in your include path:

    $ cc -o sample sample.c

#### run test:

    $ ./sample

#### output:
    *-------------------------------*
      Prüfen - launching 1 testcase 
    *-------------------------------*
    
    Testcase: DummyTestCase
     -> launching 1 test:
    -------------------
    from setup: ran before each test
    DummyTestCase - mathematics_should_work_on_my_cpu:
    execution:
     <---- end
    launching 2 assertions:
    😃  equality: ok
    😃  true expression: ok
    => ️test result: PASSED
    from teardown: ran after each test
    -------------------
    tearing down 1 test...
    testcase result: PASSED

### Run tests
    $ mkdir build && cd build
    $ cmake -DBUILD_TESTING=ON ..
    $ make
    $ make test
