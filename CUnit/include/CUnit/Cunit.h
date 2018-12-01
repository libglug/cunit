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
 *  ASSERT Macro definitions and general CUnit configuration definitions.
 *
 *  09/Aug/2001   ASSERT definitions. (AK)
 *
 *  12/Mar/2003   New Assert definitions. (AK)
 *
 *  27/Jul/2003   Modified ASSERT_XXX Macro definitions. (AK)
 *
 *  15-Jul-2004   New interface, changed action on assert failure to not
 *                return, provided _FATAL versions of assertions to return
 *                from test function on failure. (JDS)
 *
 *  01-Sep-2004   Modified assertions for setjmp/longjmp mechanism of
 *                aborting test runs, added CU_FAIL and CU_PASS macros. (JDS)
 *
 *  07-May-2005   Added CU_ prefix to remaining CUnit defines (BOOL, TRUE,
 *                FALSE, MAX_...).  Added CU_UNREFERENCED_PARAMETER() define. (JDS)
 *
 *  14/Nov/2018   Removed deprecated interface. Update version vars. (DC)
 *
 *   1/Dec/2018   Split ASSERT macros, typedefs, CU_EXPORT, version info, and turned
 *                the main CUnit.h into a single include to get up and running (DC)
 */

/** @file
 * Basic CUnit include file for user and system code.
 * Basic system macro definitions also appear here.
 */
/** @addtogroup Framework
 * @{
 */

#ifndef CUNIT_CUNIT_H_SEEN
#define CUNIT_CUNIT_H_SEEN

#include <CUnit/Assert.h>
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <CUnit/Typedefs.h>
#include <CUnit/Version.h>

#endif  /*  CUNIT_CUNIT_H_SEEN  */

/** @} */
