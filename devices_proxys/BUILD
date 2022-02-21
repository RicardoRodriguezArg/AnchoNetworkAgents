load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "devices_proxys",
    hdrs = glob(["*.h"]),
    visibility = ["//agent_server:__pkg__",
                  "//utils/tests:__pkg__",
                  "//utils:__pkg__",
                  "//message_handlers:__pkg__",
                  "//agents_middleware:__pkg__",
                  "//commons:__pkg__",
                  "//builder:__pkg__",
                 ],
    deps = [
             "//data_processors:data_processors",
             "//commons:commons",
             "//commands:commands",
             "//interface:nano_interface",
           ]
            )
