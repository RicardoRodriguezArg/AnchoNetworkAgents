load("@rules_python//python:defs.bzl", "py_test")
load("@3rdparty//:requirements.bzl", "requirement")

py_test(
    name = "agents-webapi-app-tests",
    srcs = ["agents-webapi-app-tests.py"],
    deps = [
        "//agents-webapi-py/src:agents-webapi-app",
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
        requirement("pytest"),
    ],
)
