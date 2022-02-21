load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "nano_interface",
    hdrs = glob(["*.h"]),
    srcs = glob(["*.c"]),
    visibility = ["//agent_server:__pkg__",
                  "//utils/tests:__pkg__",
                  "//utils:__pkg__",
                  "//message_handlers:__pkg__",
                  "//agents_middleware:__pkg__",
                  "//devices_proxys:__pkg__",
                  "//builder:__pkg__"
                 ],
            )
