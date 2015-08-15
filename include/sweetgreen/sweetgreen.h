#ifndef _SWEETGREEN_H_
#define _SWEETGREEN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#include "operands.h"
#include "assertion.h"
#include "test.h"
#include "testcase.h"
#include "testcase_set.h"
#include "expect_macros.h"
#include "test_define.h"

#include "main.h"

sweetgreen_main;

#include "around.h"

#ifdef __cplusplus
}
#endif

#endif