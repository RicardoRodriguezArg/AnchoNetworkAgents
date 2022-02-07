load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "message_handlers",
    hdrs = ["message_handlers.h"],
    linkopts = ["-lpthread"],
    deps = [
            "@com_google_googletest//:gtest_main",
            "//utils:ancho_net_middleware_utils",
            "//commons:commons",
           ],
    visibility = ["//agents_middleware:__pkg__",
                  "//utils:__pkg__",
                  "//message_handlers/tests:__pkg__",
                  "//builder:__pkg__",
                  "//communication:__pkg__"
                  ],
)
