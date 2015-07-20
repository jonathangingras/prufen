SweetGreen
================

C Unit Test framework. Simple, easy, header-only.

Example:
=====
sample.c
-----
<code>#include "sweetgreen/sweetgreen.h"</code>
<code></code>
<code>sweetgreen_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {</code>
<code>	int _1 = 1;</code>
<code>	int _3 = 3;</code>
<code></code>
<code>	sweetgreen_expect_equal(4, _1 + _3);</code>
<code>	sweetgreen_expect_true(4 == _1 + _3);</code>
<code>}</code>

Compile
-----
<code>$ cc -o sample sample.c # assuming sweetgreen is in your include path</code>
output:
-----
<code>*--------------------*</code>
<code>| Launching 1 test: |</code>
<code>*--------------------*</code>
<code>-------------------</code>
<code>DummyTestCase - mathematics_should_work_on_my_cpu:</code>
<code>launching 2 assertions:</code>
<code>😃  equality: ok</code>
<code>😃  non-zero expression: ok</code>
<code>=> ️test result: PASSED</code>
<code>-------------------</code>
<code>tearing down...</code>
<code>testcase result: PASSED</code>