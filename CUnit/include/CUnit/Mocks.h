#ifndef CU_MOCKS_H
#define CU_MOCKS_H

// To be used with the included CMake scripts for adding unit tests (add_unit_test.cmake)
#define CU_MOCK_INCLUDE(header, mocks) mocks

// To be used withe the included CMake scripts to mock out a specific function (add_unit_test.cmake)
#define CU_MOCK_FCN(ret_type, fcn) extern ret_type mock_##fcn

#endif // CU_MOCKS_H
