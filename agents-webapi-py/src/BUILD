load("@rules_python//python:defs.bzl", "py_test")
load("@3rdparty//:requirements.bzl", "requirement")

py_binary(
    name = "agents-webapi_app",
    srcs = ["agents-webapi_app.py"],
    deps = [
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
    ],
)
