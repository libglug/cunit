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
 *   1/Dec/2018   Split CU_EXPORT macro defs from main header (DC)
 */

/** @file
 *  Export macro for windows dlls.
 */
/** @addtogroup Framework
 * @{
 */

#ifndef CUNIT_EXPORT_H_SEEN
#define CUNIT_EXPORT_H_SEEN

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
#  ifdef CU_DLL
#    ifdef CU_BUILD_DLL
#      define CU_EXPORT __declspec(dllexport)
#    else
#      define CU_EXPORT __declspec(dllimport)
#    endif
#  else
#    define CU_EXPORT
#  endif
#else
#  define CU_EXPORT
#endif  /* WIN32 */

#endif /* CUNIT_EXPORT_H_SEEN */
/** @} */
