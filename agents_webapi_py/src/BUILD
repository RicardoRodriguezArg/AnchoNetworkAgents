load("@3rdparty//:requirements.bzl", "requirement")
package(default_visibility = ["//visibility:public"])

py_binary(
    name = "agents_webapi_app",
    srcs = ["agents_webapi_app.py",
            "agents_proxy.py",
            "agents_stub.py",
            "agents_proxy_stub_utils.py",

           ],
    deps = [
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
        "//interface:message_interface_idl_pb2"
    ],
)



py_library(
    name = "agents_proxy",
    srcs = ["agents_proxy.py",
            "agents_stub.py",
            "agents_proxy_stub_utils.py",
            ],
    deps=[
        "//interface:message_interface_idl_pb2"],
)


py_library(
    name = "agents_cli_app",
    srcs = ["agents_cli_app.py.py"
            ],
    deps=[
        "//agents_webapi_py/src:agents_proxy"
        "//interface:message_interface_idl_pb2"],
)

py_test(
    name = "agents_webapi_app_tests_one",
    srcs = ["test/agents_webapi_app_tests_one.py"],
    deps = [
        "agents_webapi_app",
        "agents_proxy",
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
