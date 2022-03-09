##WebApi server - running the server

bazel run //agents_webapi_py/src:agents-webapi-app

##WebApi server - running the server tests
bazel test //agents_webapi_py/test:agents-webapi-app-tests

##Py Agents 
bazel run //agents_webapi_py/src:agents_cli_app
