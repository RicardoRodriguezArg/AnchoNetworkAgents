from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Header
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
from agents_webapi_py.src.agents_stub import AgentStub

import logging


def SendCommandToServer(WepAppiCommand):
    logging.info('Sendign Command to Main C++ Server')
    server_stub = AgentStub()
    server_stub.ConvertToCmdProtoMessage(WepAppiCommand)
    server_stub.SendCmdToServer()
    return (server_stub.GetExecutionStatus(), server_stub.GetResponseResult())
