load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "ancho_net_middleware_utils",
    srcs = ["utils.cpp"],
    hdrs = ["utils.h"],
    visibility = ["//agent_server:__pkg__",
                  "//utils/tests:__pkg__",
                  "//message_handlers:__pkg__",
                  "//builder:__pkg__",
                  "//eth_layer:__pkg__",
                  "//agents_middleware:__pkg__",
                  "//communication:__pkg__",
                  ],
    deps = ["//commons:commons",]
)
