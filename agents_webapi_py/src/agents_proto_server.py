import socket
import datetime
from datetime import date
import time
import sys
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Header
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageType
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageSize
import logging


class UdpAgentsServer():
    def __init__(self, server_port=5001, buffer_size=1024):
        self.__sockect = socket.socket(
            family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.___server_ip = "127.0.0.1"
        self.__is_operative = False
        self.__server_port = server_port
        self.__buffer_size = buffer_size

    def StartServer(self):
        self.__sockect.bind((self.___server_ip, self.__server_port))
        self.__is_operative = True
        while(self.__is_operative):
            bytesAddressPair = self.__sockect.recvfrom(self.__buffer_size)
            sockect_message_data = bytesAddressPair[0]
            client_address = bytesAddressPair[1]
            unpacked_data = UnpackBinaryData(sockect_message_data)
            result_command = ProcessProtoMessage(unpacked_data)
            message_type = GetMessageType(unpacked_data)
            print("message from client: {}".format(client_address))
            condition = (message_type == Header.COMMAND_PROTO) and (
                result_command.id == 1) and (result_command.header.request_ack == True)
            if condition:
                # need to update timestamp
                result_command.state = CommandWithArguments.State.EXECUTED
                message = result_command.SerializeToString()
                # Custom Protocol AnchoNet
                packed_data = PackBinaryData(message)
                self.__sockect.sendto(packed_data, client_address)
                #self.__is_operative = False
            time.sleep(0.2)


if __name__ == "__main__":
    mock_server = UdpAgentsServer()
    mock_server.StartServer()
