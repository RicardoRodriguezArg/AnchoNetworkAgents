load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "interface_cc_proto",
    deps = [":interface_proto"],
)

proto_library(
    name = "interface_proto",
    srcs = [":message_interface_idl.proto"],
 )
