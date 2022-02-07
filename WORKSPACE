load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/32ad3c8c36382165274385a28a23addbea581f5d.zip"],
  strip_prefix = "googletest-32ad3c8c36382165274385a28a23addbea581f5d",
)
new_local_repository(
    name = "libnanopb",
    path = "ext_lib/nano_pb/",
    build_file = "third_party/nano_pb/nano_pb.BUILD",
    )
