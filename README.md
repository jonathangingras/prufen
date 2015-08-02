#SweetGreen

C Unit Test framework. Simple, easy, header-only.

##Example:

###sample.c

    #include "sweetgreen/sweetgreen.h"

    sweetgreen_setup { // optional
        printf("from setup: ran before each test\n");
    }

    sweetgreen_teardown {
       printf("from teardown: ran after each test\n");
    }
    
    sweetgreen_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {
    	int _1 = 1;
    	int _3 = 3;
    
    	sweetgreen_expect_equal(4, _1 + _3);
    	sweetgreen_expect_true(4 == _1 + _3);
    }

###Compile
assuming sweetgreen is in your include path:

    $ cc -o sample sample.c

###output:

    *--------------------*
      Launching 1 test:
    *--------------------*
    -------------------
    from setup: ran before each test
    DummyTestCase - mathematics_should_work_on_my_cpu:
    execution:
    <---- end
    launching 2 assertions:
    😃  equality: ok
    😃  non-zero expression: ok
    => ️test result: PASSED
    from teardown: ran after each test
    -------------------
    tearing down 1 test...
    testcase result: PASSED