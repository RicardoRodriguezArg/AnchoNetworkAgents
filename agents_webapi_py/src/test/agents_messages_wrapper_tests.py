import pytest
from agents_webapi_py.src.agents_stub import AgentStub
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage

def CreateJsonForTest():
    json_to_send = {"id": "1",
                    "argument_count": "2",
                    "source": "main_web",
                    "target": "generic_tp_link_router",
                    "request_ack": "true",
                    "arguments": [
                        {"name": "speed",
                          "value": "300"
                         },
                        {"name": "service_type",
                         "value": "home"
                         }
                    ]
                    }
    return json_to_send


def TestCorrectProtoCommandMessageEncodingFromJson():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateJsonForTest())
    converted_proto_command = server_stub.command_proto
    assert converted_proto_command.header.message_id == 0
    assert converted_proto_command.header.target_agent_id == Header.SERVER_UDP_X86_TALCA_ID
    assert converted_proto_command.header.source_agent_id == Header.WEB_API_PYTHON_CLIENT_ID
    assert converted_proto_command.id == 1
    assert converted_proto_command.number_arg_count == 2

def TestCorrectMessageEncodingDecodingProcess():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateJsonForTest())
    message = self.__cmd_proto.SerializeToString()
    packed_data = PackBinaryData(message)
    unpacked_data = UnpackBinaryData(packed_data)
    result_command = ProcessProtoMessage(unpacked_response)
    assert result_command.header.message_id == 0
    assert result_command.header.target_agent_id == Header.SERVER_UDP_X86_TALCA_ID
    assert result_command.header.source_agent_id == Header.WEB_API_PYTHON_CLIENT_ID
    assert result_command.id == 1
    assert result_command.number_arg_count == 2
