###UTILS
this folders contains utilites functions declared as free function.
It use C++20 Standard to compile
##Bazel Exectution with Debug simbols:
bazel run -c dbg -s --cxxopt='-std=c++2a' //utils/tests:communication_tests
bazel run --cxxopt='-std=c++2a' //utils/tests:communication_tests