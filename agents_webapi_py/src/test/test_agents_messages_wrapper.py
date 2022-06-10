import pytest
from threading import Thread
import socket
from agents_webapi_py.src.agents_stub import AgentStub
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
from agents_webapi_py.src.test.test_server_commons import CreateJsonForTestDict


def LoadServer(path_to_script):
    exec(open(path_to_script).read())

def CreateServer(server_ip="127.0.0.1", server_port=5001, buffer_size=1024):
    # Create a datagram socket
    UDPServerSocket = socket.socket(
        family=socket.AF_INET, type=socket.SOCK_DGRAM)
    # Bind to address and ip
    UDPServerSocket.bind((server_ip, 5001))

    server_up = True
    print("-------Starting Server----------")
    while(server_up):
        bytesAddressPair = UDPServerSocket.recvfrom(buffer_size)
        message = bytesAddressPair[0]
        address = bytesAddressPair[1]
        clientMsg = "Message from Client:{}".format(message)
        clientIP = "Client IP Address:{}".format(address)
        if len(clientMsg) > 0:
            print(clientMsg)
            print(clientIP)
            server_up = False
        if not server_up:
            break


def test_CorrectMessageEncodingDecodingOverUdpServer():
    proto_message_stub = AgentStub(
        server_ip="127.0.0.1", target_server_port=5001, local_server_port=50100, buffer_size=4096)
    LoadServer("/home/operador/Documents/temp/server.py")
    #server_thread = Thread(target=CreateServer, args=(3,))
    #server_thread.start()
    assert proto_message_stub.ShouldWaitForResponse() == False
    assert "uninit" in proto_message_stub.GetExecutionStatus()
    ## prepare command
    proto_message_stub.ConvertToCmdProtoMessage(CreateJsonForTestDict())
    assert proto_message_stub.SendCmdToServer()
    #assert proto_message_stub.GetExecutionStatus(
    #)["execution_status"] == "Command executed"
    #result = proto_message_stub.GetResponseResul()
    #assert not result
    #assert proto_message_stub.ShouldWaitForResponse() == True


if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
