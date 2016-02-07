#SweetGreen [![Build Status](https://travis-ci.org/jonathangingras/sweetgreen.svg?branch=master)](https://travis-ci.org/jonathangingras/sweetgreen)

C Unit Test framework for Unix-like systems. Simple, easy, header-only.

##Example:

###sample.c

    #include "sweetgreen/sweetgreen.h"

    sweetgreen_setup(DummyTestCase) { /* optional */
        printf("from setup: ran before each test\n");
    }

    sweetgreen_teardown(DummyTestCase) { /* optional too */
       printf("from teardown: ran after each test\n");
    }
    
    sweetgreen_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {
    	int _1 = 1;
    	int _3 = 3;
    
    	sweetgreen_expect_equal(4, _1 + _3);
    	sweetgreen_expect_true(4 == _1 + _3);
    }

###Compile & run

####compile:
assuming sweetgreen is in your include path:

    $ cc -o sample sample.c

####run test:

    $ ./sample

####output:
    *-----------------------------------*
      SweetGreen - launching 1 testcase 
    *-----------------------------------*
    
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

###Run tests
    $ mkdir build && cd build
    $ cmake -DWITH_TESTS=ON ..
    $ make
    $ bash bin/run_tests.bash