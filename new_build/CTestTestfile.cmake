# CMake generated Testfile for 
# Source directory: /Users/aromanov/LongNumbers
# Build directory: /Users/aromanov/LongNumbers/new_build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(long_number_tests "/Users/aromanov/LongNumbers/new_build/long_number_tests")
set_tests_properties(long_number_tests PROPERTIES  _BACKTRACE_TRIPLES "/Users/aromanov/LongNumbers/CMakeLists.txt;30;add_test;/Users/aromanov/LongNumbers/CMakeLists.txt;0;")
subdirs("lib/googletest")
