import binascii
import socket
import struct
import sys
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Event
from interface.message_interface_idl_pb2 import Telemetry
from interface.message_interface_idl_pb2 import Header

def PackBinaryData(string_to_encode):
    #CMD_PROTO -->
    values = (int(len(string_to_encode)), 5,string_to_encode)
    """
    General Protocol for encoding binary data on enconded serialize protocol buffer object
    """
    packer = struct.Struct('I I s')
    return  packer.pack(*values)

def UnpackBinaryData(packet_data):
    unpacker = struct.Struct('I I s')
    return unpacker.unpack(packet_data)


def ProcessProtoMessage(unpack_data):
    message_size = unpack_data(0)
    message_type = unpack_data(1)
    result = None
    serialize_proto_message = unpack_data(2)
    if message_type == Header.MessageType.CMD_PROTO:
        serialize_message = unpack_data(2)
        result = CommandWithArguments.ParseFromString(serialize_message)
    elif message_type == Header.MessageType.EVENT_PROTO:
        serialize_message = unpack_data(2)
        result = Event.ParseFromString(serialize_message)
    elif message_type == Header.MessageType.EVENT_PROTO:
        serialize_message = unpack_data(2)
        result = Event.ParseFromString(serialize_message)
    return result
