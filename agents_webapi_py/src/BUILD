load("@3rdparty//:requirements.bzl", "requirement")
package(default_visibility = ["//visibility:public"])

py_binary(
    name = "agents_webapi_app",
    srcs = ["agents_webapi_app.py"],
    deps = [
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
    ],
)

py_test(
    name = "agents_webapi_app_tests_one",
    srcs = ["test/agents_webapi_app_tests_one.py"],
    deps = [
        "agents_webapi_app",
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
        requirement("pytest"),
    ],
)

test_suite(
    name = "agents_webapi_app_tests_suite",
    tests = [
        "agents_webapi_app_tests_one",
    ],
)

py_library(
    name = "test_lib",
    srcs = glob(["test/*.py"]),
    deps = ["agents_webapi_app",
           ],
)
