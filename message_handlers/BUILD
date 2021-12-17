load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "agents_server",
    srcs = [""],
    hdrs = ["agent_server.h"],
    linkopts = ["-lpthread"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//utils:ancho_net_middleware_utils",
    ],
)

cc_binary(
    name = "openwrt_agents_server",
    srcs = ["main.cpp"],
)
