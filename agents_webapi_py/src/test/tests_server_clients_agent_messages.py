import pytest
from agents_webapi_py.src.agents_stub import AgentStub
from agents_webapi_py.src.test.test_server_commons import CreateJsonForTestDict
from agents_webapi_py.src.test.test_server_commons import CreateShutDownJsonForTestDict
from agents_webapi_py.src.test.test_server_commons import CreateJsonDictWithInvalidArgumentCount


def test_SendCommandToPythonServer_ExpectCorrectMessageEncodingDecoding():
    proto_message_stub = AgentStub(
        server_ip="127.0.0.1", target_server_port=5001, local_server_port=50100, buffer_size=4096)
    assert proto_message_stub.ShouldWaitForResponse() == False
    assert "uninit" in proto_message_stub.GetExecutionStatus()
    # prepare command
    proto_message_stub.ConvertToCmdProtoMessage(CreateJsonForTestDict())
    assert proto_message_stub.SendCmdToServer()
    assert "Command executed" in proto_message_stub.GetExecutionStatus(
    )
    result = proto_message_stub.GetResponseResult()
    assert result
    assert proto_message_stub.ShouldWaitForResponse() == True


def test_SendShutdownCommandToPythonServer_ExpectPythonServerShutdown():
    proto_message_stub = AgentStub(
        server_ip="127.0.0.1", target_server_port=5001, local_server_port=50100, buffer_size=4096)
    assert proto_message_stub.ShouldWaitForResponse() == False
    assert "uninit" in proto_message_stub.GetExecutionStatus()
    # prepare command
    proto_message_stub.ConvertToCmdProtoMessage(CreateShutDownJsonForTestDict())
    assert proto_message_stub.SendCmdToServer()
    assert "Command executed" in proto_message_stub.GetExecutionStatus(
    )
    result = proto_message_stub.GetResponseResult()
    assert result
    assert proto_message_stub.ShouldWaitForResponse() == True


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
