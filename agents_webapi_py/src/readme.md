##WebApi server - running the server

bazel run //agents_webapi_py/src:agents_webapi_app

##WebApi server - running the server tests
bazel test //agents_webapi_py/src:agents_webapi_app_tests_one

##Py Agents 
bazel run //agents_webapi_py/src:agents_cli_app
