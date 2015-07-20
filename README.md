SweetGreen
================

C Unit Test framework. Simple, easy, header-only.

Example:
=====
sample.c
-----
<code>#include "sweetgreen/sweetgreen.h"</code><br>
<code></code><br>
<code>sweetgreen_test_define(DummyTestCase, mathematics_should_work_on_my_cpu) {</code><br>
<code>	int _1 = 1;</code><br>
<code>	int _3 = 3;</code><br>
<code></code><br>
<code>	sweetgreen_expect_equal(4, _1 + _3);</code><br>
<code>	sweetgreen_expect_true(4 == _1 + _3);</code><br>
<code>}</code><br>

Compile
-----
<code>$ cc -o sample sample.c # assuming sweetgreen is in your include path</code><br>
output:
-----
<code>*--------------------*</code><br>
<code>| Launching 1 test: |</code><br>
<code>*--------------------*</code><br>
<code>-------------------</code><br>
<code>DummyTestCase - mathematics_should_work_on_my_cpu:</code><br>
<code>launching 2 assertions:</code><br>
<code>😃  equality: ok</code><br>
<code>😃  non-zero expression: ok</code><br>
<code>=> ️test result: PASSED</code><br>
<code>-------------------</code><br>
<code>tearing down...</code><br>
<code>testcase result: PASSED</code><br>