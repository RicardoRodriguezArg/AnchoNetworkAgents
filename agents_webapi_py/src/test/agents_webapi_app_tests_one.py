import pytest
import subprocess
import sys
from agents_webapi_py.src.agents_webapi_app import app
import logging
from agents_webapi_py.src.agents_stub import AgentStub
from interface.message_interface_idl_pb2 import Header
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageType
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageSize
from test_server_commons import *


class BashSystemCommandsManager:
    def __init__(self):
        pass

    def __execute_commands(self, command_to_execute):
        process = subprocess.Popen(
            [command_to_execute], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        return (len(stderr) == 0)

    def init_agents_server(self):
        result = self.__execute_commands('agents_middleware_server')
        return result

    def kill_agents_server(self):
        result = self.__execute_commands('killall agents_middleware_server')
        return result


@pytest.fixture
def client():
    return app.test_client()


def test_home(client):
    resp = client.get('/agents-webapi/')
    print("testing commands...")
    assert resp.status_code == 200


def test_service_fail(client):
    resp = client.post('/agents-webapi/cmd/',
                       json={'id': '1', 'argument_count': '2', 'source': 'main_web', 'target': 'generic_tp_link_router',
                             'request_ack': 'true',
                             'arguments': [
                                 {"name": "speed",  "value": "300"},
                                 {"name": "service_type", "value": "home"}
                             ]})
    assert resp.status_code == 200
    execution_status = resp.json.get('execution_status')
    assert "uninit" in execution_status


def test_server_agent_time_out(client):
    bash_command_executor = BashSystemCommandsManager()
    logging.info('Test Server C++ Agent')
    resp = client.post('/agents-webapi/cmd/',
                       json={'id': '1', 'argument_count': '2', 'source': 'main_web', 'target': 'generic_tp_link_router',
                             'request_ack': 'true',
                             'arguments': [
                                 {"name": "speed",  "value": "300"},
                                 {"name": "service_type", "value": "home"}
                             ]})
    assert resp.status_code == 200
    expected_valid_result = "Main C++ Server Not Responding, timeout" in resp.json.get(
        'execution_status')


def test_correct_message_handling_when_empty_json():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateEmptyJsonDict())
    assert server_stub.command_proto() == None

def test_correct_message_arrive_with_invalid_argument_count():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateJsonDictWithInvalidArgumentCount())
    assert server_stub.command_proto() == None


def test_correct_protoCommand_message_encoding_from_json():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateJsonForTestDict())
    converted_proto_command = server_stub.command_proto()
    assert converted_proto_command
    assert converted_proto_command.header.message_id == 0
    assert converted_proto_command.id == 1
    assert converted_proto_command.number_arg_count == 2
    assert converted_proto_command.header.source_agent_id == Header.MAIN_WEB_SITE
    assert converted_proto_command.header.target_agent_id == Header.GENERIC_TP_LINK_ROUTER_ID


def test_CorrectMessageEncodingDecodingProcess():
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(CreateJsonForTestDict())
    # protocol buffer serialization
    message = server_stub.command_proto().SerializeToString()
    # Custom Protocol AnchoNet
    expected_message_size = sys.getsizeof(message)
    packed_data = PackBinaryData(message)
    unpacked_data = UnpackBinaryData(packed_data)
    result_command = ProcessProtoMessage(unpacked_data)
    encoded_message_size = GetMessageSize(unpacked_data)
    message_type = GetMessageType(unpacked_data)
    assert expected_message_size == encoded_message_size
    assert message_type == Header.COMMAND_PROTO
    assert result_command.header.message_id == 0
    assert result_command.header.target_agent_id == Header.GENERIC_TP_LINK_ROUTER_ID
    assert result_command.header.source_agent_id == Header.MAIN_WEB_SITE
    assert result_command.id == 1
    assert result_command.number_arg_count == 2


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
