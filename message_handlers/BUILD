load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "message_handlers",
    srcs = [""],
    hdrs = ["message_handlers.h"],
    linkopts = ["-lpthread"],
    deps = [
            "@com_google_googletest//:gtest_main",
            "//utils:ancho_net_middleware_utils",
            "//common:commons",
           ],
    visibility = ["//agent_server:__pkg__",
                  "//utils:__pkg__",
                  "//message_handlers/tests:__pkg__"
                  ],
)


