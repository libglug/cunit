Summary: A unit testing framework for 'C'
Name: CUnit
Version : 1.0
Release: 4
Epoch: 1
Source: http://www.sourceforge.net/projects/cunit
Group: Development/Tools
Copyright: GPL
URL: http://cunit.sourceforge.net
Packager: Anil Kumar <aksaharan@yahoo.com>

%description
CUnit is unit testing framework for C.

%prep
echo "Preparing for Installation."

%build
echo "Preparing for Building."
cd $RPM_BUILD_ROOT && \
./configure --prefix=%{_prefix} && \
make

%install
echo "Preparing for Make install."
cd $RPM_BUILD_ROOT && \
make install

%clean

%files
%defattr(-,root,root)

########### Include Files
%{_prefix}/include/CUnit/Console.h
%{_prefix}/include/CUnit/Curses.h
%{_prefix}/include/CUnit/CUnit.h
%{_prefix}/include/CUnit/Errno.h
%{_prefix}/include/CUnit/TestDB.h

########## Library File
%{_prefix}/lib/libcunit.a

########## Manpage Files
%{_prefix}/man/man3/add_test_case.3
%{_prefix}/man/man3/add_test_group.3
%{_prefix}/man/man3/ASSERT.3
%{_prefix}/man/man3/cleanup_registry.3
%{_prefix}/man/man3/console_run_tests.3
%{_prefix}/man/man3/curses_run_tests.3
%{_prefix}/man/man3/get_error.3
%{_prefix}/man/man3/get_registry.3
%{_prefix}/man/man3/initialize_registry.3
%{_prefix}/man/man3/set_registry.3 
%{_prefix}/man/man8/CUnit.8

########## Share information and Example Files 
%{_prefix}/share/CUnit-1.0-4/Example/Console/README
%{_prefix}/share/CUnit-1.0-4/Example/Console/ConsoleTest
%{_prefix}/share/CUnit-1.0-4/Example/Curses/README
%{_prefix}/share/CUnit-1.0-4/Example/Curses/CursesTest

%changelog
* Sun Feb 03 2002 Anil Kumar <aksaharan@yahoo.com>
- Made modifications for moving RPM Creation in the root directory.
- Cleaned up configure.in for Checks not required and added some additonal
  header and library checks.
- Made separate options for gzip, tar, zip and rpm creation in root directory. 
- Fixed Workspace file for Windows Build.

* Sun Dec 23 2001 Anil Kumar <aksaharan@yahoo.com>
- Made modifications for change in Directory Structure and Linking Options.

* Sun Nov 25 2001 Anil Kumar <aksaharan@yahoo.com>
- Added Curses based interface to the Package.

* Sun Oct 28 2001 Anil Kumar <aksaharan@yahoo.com>
- Integrated RPM creation in the package configuration 

* Sun Oct 21 2001 Anil Kumar <aksaharan@yahoo.com>
- Added a few Error Codes and respective description.
- Added code for handling duplicate group/test name 
