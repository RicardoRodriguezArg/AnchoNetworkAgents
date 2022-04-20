load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "builder",
    hdrs = ["builder.h", "commands_buider.h"],
    srcs = ["builder.cpp"],
    visibility = ["//agents_middleware:__pkg__",
                 ],
    deps = [
             "@com_github_google_glog//:glog",
             "//utils:ancho_net_middleware_utils",
             "//commons:commons",
             "//message_handlers:message_handlers",
             "//commands:commands",
             "//devices_proxys:devices_proxys",
             "//data_processors:data_processors",
             "//eth_layer:eth_layer",
             "//communication:server",
           ],

            )
