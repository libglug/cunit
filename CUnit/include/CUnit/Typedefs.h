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
 *  CUnit typedefs.
 *
 *   1/Dec/2018   Split typedef macros from main header (DC)
 */

/** @file
 * CUnit type definitions
 */
/** @addtogroup Framework
 * @{
 */

#ifndef CUNIT_TYPEDEFS_H_SEEN
#define CUNIT_TYPEDEFS_H_SEEN

/*  Max string lengths for names (includes terminating NULL. */
/** Maximum length of a test name string. */
#define CU_MAX_TEST_NAME_LENGTH 256
/** Maximim length of a suite name string. */
#define CU_MAX_SUITE_NAME_LENGTH 256

/* Global type Definitions to be used for boolean operators. */
#ifndef CU_BOOL
  /** Boolean type for CUnit use. */
  #define CU_BOOL int
#endif

#ifndef CU_TRUE
  /** Boolean TRUE for CUnit use. */
  #define CU_TRUE 1
#endif

#ifndef CU_FALSE
  /** Boolean FALSE for CUnit use. */
  #define CU_FALSE 0
#endif

#ifndef CU_UNREFERENCED_PARAMETER
  /** Consistent approach to referencing unused parameters. */
  #define CU_UNREFERENCED_PARAMETER(x) (void)x
#endif

#endif  /*  CUNIT_TYPEDEFS_H_SEEN  */

/** @} */
