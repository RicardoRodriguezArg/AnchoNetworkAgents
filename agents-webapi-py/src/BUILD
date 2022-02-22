load("@3rdparty//:requirements.bzl", "requirement")

package(default_visibility = ["//visibility:public"])

py_library(
    name = "webapi-deps",
    srcs = glob(["*.py"]),
    deps = [
        # Flask
        "//third_party:flask",
         "//third_party:pandas"
    ],
)

py_binary(
  name = "agents-webapi",
  srcs = ["agents-webapi.py"],
  deps = [
    ":webapi-deps"
  ]
)
