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
    srcs = ["agents_cli_app.py"
            ],
    deps=[
        "//agents_webapi_py/src:agents_proxy",
        "//interface:message_interface_idl_pb2"
        ],
)

##Python Server for protocol buffer messages
py_binary(
    name = "agents_proto_server",
    srcs = ["agents_proto_server.py"
            ],
    deps=[
        "//agents_webapi_py/src:agents_proxy",
        "//interface:message_interface_idl_pb2",
        requirement("protobuf"),
        ],
)

py_test(
    name = "agents_webapi_app_tests_one",
    srcs = ["test/agents_webapi_app_tests_one.py",
           ],
    deps = [
        "agents_webapi_app",
        "agents_proxy",
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
        requirement("pytest"),
        requirement("protobuf"),
    ],
)

py_test(
    name = "tests_server_clients_agent_messages",
    main = "test/tests_server_clients_agent_messages.py",
    srcs = ["test/tests_server_clients_agent_messages.py",
            "test/test_server_commons.py"
           ],
    deps = [
        "agents_webapi_app",
        "agents_proxy",
        requirement("flask"),
        requirement("jinja2"),
        requirement("werkzeug"),
        requirement("itsdangerous"),
        requirement("click"),
        requirement("pytest"),
        requirement("protobuf"),
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
