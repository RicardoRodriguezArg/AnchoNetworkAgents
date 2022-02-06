load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "agents_middleware_server",
    srcs = ["main.cpp"],
    linkopts = ["-lpthread"],
    deps = [
            "@com_google_googletest//:gtest_main",
             "//utils:ancho_net_middleware_utils",
             "//commons:commons",
             "//message_handlers:message_handlers",
             "//builder:builder",
             "//commands:commands",
             "//devices_proxys:devices_proxys",
             "//data_processors:data_processors",
           ],
)
