SweetGreen
================

C Unit Test framework. Simple, easy, header-only.

Example:
=====
sample.c
-----
<code>
#include "sweetgreen/sweetgreen.h"

sweetgreen_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {
	int _1 = 1;
	int _3 = 3;

	sweetgreen_expect_equal(4, _1 + _3);
	sweetgreen_expect_true(4 == _1 + _3);
}
</code>

Compile
-----
$ cc -o sample sample.c # assuming sweetgreen is in your include path
output:
-----
<code>
*--------------------*
| Launching 1 test: |
*--------------------*
-------------------
DummyTestCase - mathematics_should_work_on_my_cpu:
launching 2 assertions:
😃  equality: ok
😃  non-zero expression: ok
=> ️test result: PASSED
-------------------
tearing down...
testcase result: PASSED
</code>