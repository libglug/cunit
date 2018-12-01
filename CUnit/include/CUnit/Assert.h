/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001       Anil Kumar
 *  Copyright (C) 2004-2006  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  ASSERT Macro definitions.
 *
 *   1/Dec/2018   Split ASSERT macro defs from main header (DC)
 */

/** @file
 * CUnit assertion macros
 * Defines macros for assertions for use in user test cases.
 */
/** @addtogroup Framework
 * @{
 */

#ifndef CUNIT_ASSERT_H_SEEN
#define CUNIT_ASSERT_H_SEEN

#include <math.h>
#include <CUnit/TestRun.h>

/** Record a pass condition without performing a logical test. */
#define CU_PASS(msg) \
  { CU_assertImplementation(CU_TRUE, __LINE__, ("CU_PASS(" #msg ")"), __FILE__, "", CU_FALSE); }

/** Simple assertion.
 *  Reports failure with no other action.
 */
#define CU_ASSERT(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", CU_FALSE); }

/** Simple assertion.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", CU_TRUE); }

/** Simple assertion.
 *  Reports failure with no other action.
 */
#define CU_TEST(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", CU_FALSE); }

/** Simple assertion.
 *  Reports failure and causes test to abort.
 */
#define CU_TEST_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", CU_TRUE); }

/** Record a failure without performing a logical test. */
#define CU_FAIL(msg) \
  { CU_assertImplementation(CU_FALSE, __LINE__, ("CU_FAIL(" #msg ")"), __FILE__, "", CU_FALSE); }

/** Record a failure without performing a logical test, and abort test. */
#define CU_FAIL_FATAL(msg) \
  { CU_assertImplementation(CU_FALSE, __LINE__, ("CU_FAIL_FATAL(" #msg ")"), __FILE__, "", CU_TRUE); }

/** Asserts that value is CU_TRUE.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_TRUE(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE(" #value ")"), __FILE__, "", CU_FALSE); }

/** Asserts that value is CU_TRUE.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_TRUE_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE_FATAL(" #value ")"), __FILE__, "", CU_TRUE); }

/** Asserts that value is CU_FALSE.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_FALSE(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE(" #value ")"), __FILE__, "", CU_FALSE); }

/** Asserts that value is CU_FALSE.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_FALSE_FATAL(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE_FATAL(" #value ")"), __FILE__, "", CU_TRUE); }

/** Asserts that actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL(" #actual "," #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that actual == expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that pointers actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_EQUAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) == (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that pointers actual == expected.
 * Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) == (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that pointers actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) != (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that pointers actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((const void*)(actual) != (const void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that pointer value is NULL.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NULL(value) \
  { CU_assertImplementation((NULL == (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL(" #value")"), __FILE__, "", CU_FALSE); }

/** Asserts that pointer value is NULL.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NULL_FATAL(value) \
  { CU_assertImplementation((NULL == (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL_FATAL(" #value")"), __FILE__, "", CU_TRUE); }

/** Asserts that pointer value is not NULL.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_PTR_NOT_NULL(value) \
  { CU_assertImplementation((NULL != (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL(" #value")"), __FILE__, "", CU_FALSE); }

/** Asserts that pointer value is not NULL.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_PTR_NOT_NULL_FATAL(value) \
  { CU_assertImplementation((NULL != (const void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL_FATAL(" #value")"), __FILE__, "", CU_TRUE); }

/** Asserts that string actual == expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_STRING_EQUAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL(" #actual ","  #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that string actual == expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_STRING_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that string actual != expected.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_STRING_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL(" #actual ","  #expected ")"), __FILE__, "", CU_FALSE); }

/** Asserts that string actual != expected.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_STRING_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, "", CU_TRUE); }

/** Asserts that string actual == expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NSTRING_EQUAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", CU_FALSE); }

/** Asserts that string actual == expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NSTRING_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, "", CU_TRUE); }

/** Asserts that string actual != expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_NSTRING_NOT_EQUAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", CU_FALSE); }

/** Asserts that string actual != expected with length specified.
 *  The comparison is limited to count characters.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, "", CU_TRUE); }

/** Asserts that double actual == expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion passes.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_DOUBLE_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", CU_FALSE); }

/** Asserts that double actual == expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion passes.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_DOUBLE_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", CU_TRUE); }

/** Asserts that double actual != expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion fails.
 *  Reports failure with no other action.
 */
#define CU_ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", CU_FALSE); }

/** Asserts that double actual != expected within the specified tolerance.
 *  If actual is within granularity of expected, the assertion fails.
 *  Reports failure and causes test to abort.
 */
#define CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", CU_TRUE); }

#endif  /*  CUNIT_ASSERT_H_SEEN  */

/** @} */
