import struct
import sys
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Event
from interface.message_interface_idl_pb2 import Telemetry
from interface.message_interface_idl_pb2 import Header


def PackBinaryData(string_to_encode):
    # TODO: use Interface definition to assing this value
    # CMD_NANO VALUE = 1
    # CMD_PROTO VALUE = 2
    messageSize = sys.getsizeof(string_to_encode)
    print("message size: {}".format(messageSize))
    packet_message_bytes = struct.pack("!I ", messageSize)
    packet_message_bytes += struct.pack("!I", Header.COMMAND_PROTO)
    packet_message_bytes += string_to_encode
    print("packed message:  {}".format(packet_message_bytes))
    return packet_message_bytes


def UnpackBinaryData(packet_data):
    print("unpacking message- >>>>>>>:  {}".format(packet_data))
    packed_message_size_bytes = packet_data[:4]
    unpacked_message_size = struct.unpack("!I", packed_message_size_bytes)[0]
    print("message_size: {}".format(unpacked_message_size))
    unpacked_message_type_bytes = packet_data[4:8]
    unpacked_message_data_type = struct.unpack(
        "!I", unpacked_message_type_bytes)[0]
    print("message_type: {}".format(unpacked_message_data_type))
    unpacked_message_string_bytes = packet_data[8:unpacked_message_size]
    print("string: {}".format(unpacked_message_string_bytes))
    return (unpacked_message_size, unpacked_message_data_type, unpacked_message_string_bytes)


def GetMessageSize(unpack_data):
    message_type = unpack_data[0]
    return message_type


def GetMessageType(unpack_data):
    message_type = unpack_data[1]
    return message_type


def ProcessProtoMessage(unpack_data):
    message_size = unpack_data[0]
    message_type = unpack_data[1]
    result = None
    serialize_proto_message = unpack_data[2]
    if message_type == Header.COMMAND_PROTO:
        serialize_message = unpack_data[2]
        command = CommandWithArguments()
        command.ParseFromString(serialize_message)
        print(command)
        result = command
    elif message_type == Header.EVENT_PROTO:
        serialize_message = unpack_data[2]
        result = Event.ParseFromString(serialize_message)
    elif message_type == Header.DATA:
        serialize_message = unpack_data[2]
        result = Telemetry.ParseFromString(serialize_message)
    return result
