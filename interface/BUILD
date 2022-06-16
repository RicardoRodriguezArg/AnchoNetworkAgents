load("@rules_cc//cc:defs.bzl", "cc_library")



cc_library(
    name = "nano_interface",
    hdrs = glob(["*.h"]),
    srcs = glob(["*.c"]),
    visibility = [                  
                  "//agent_server:__pkg__"      ,
                  "//utils/tests:__pkg__"       ,
                  "//utils:__pkg__"             ,
                  "//message_handlers:__pkg__"  ,
                  "//agents_middleware:__pkg__" ,
                  "//devices_proxys:__pkg__"    ,
                  "//builder:__pkg__"
                 ],
            )

cc_library(
    name = "proto_interface",
    hdrs = ["message_interface_idl.pb.h"],
    srcs = ["message_interface_idl.pb.cc"],
    visibility = [                  
                  "//builder:__pkg__"
                 ],
    deps=[
          "@com_google_protobuf//:protobuf",
          "@com_google_protobuf//:protobuf_headers"
          ]
           )



py_library(
  name = "message_interface_idl_pb2",
  srcs = ["message_interface_idl_pb2.py"],
  srcs_version = "PY3",
  visibility = ["//visibility:public"],
)
