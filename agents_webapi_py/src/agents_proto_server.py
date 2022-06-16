import socket
import argparse
import time
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Commands
from interface.message_interface_idl_pb2 import Header
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageType
from agents_webapi_py.src.agents_proxy_stub_utils import GetMessageSize
import logging
logging.basicConfig(filename='agents-python-server.log', level=logging.INFO)
log = logging.getLogger("server-proto-server")

class UdpAgentsServer():
    def __init__(self, server_port=5001, buffer_size=1024, used_for_testing=False):
        self.__sockect = socket.socket(
            family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.___server_ip = "127.0.0.1"
        self.__is_operative = False
        self.__server_port = server_port
        self.__buffer_size = buffer_size
        self.__used_for_testing = used_for_testing

    def __is_valid_command(self, command, message_type):
        condition = (message_type == Header.COMMAND_PROTO) and (
            command.header.request_ack == True)
        return condition

    def __process_command(self, command):
        if (self.__used_for_testing):
            command.state = CommandWithArguments.State.EXECUTED
            self.__is_operative = (
                command.id != Commands.SHUTDOWN_TESTING_SERVER)
            print("Command id: {} is operative: {}".format(command.id, self.__is_operative))
            return command

    def StartServer(self):
        self.__sockect.bind((self.___server_ip, self.__server_port))
        self.__is_operative = True
        while(self.__is_operative):
            bytesAddressPair = self.__sockect.recvfrom(self.__buffer_size)
            sockect_message_data = bytesAddressPair[0]
            client_address = bytesAddressPair[1]
            unpacked_data = UnpackBinaryData(sockect_message_data)
            result_command = ProcessProtoMessage(unpacked_data)
            if self.__is_valid_command(result_command, GetMessageType(unpacked_data)):
                # need to update timestamp
                self.__process_command(result_command)
                message = result_command.SerializeToString()
                # Custom Protocol AnchoNet
                packed_data = PackBinaryData(message)
                self.__sockect.sendto(packed_data, client_address)
        print("shunting down server")


def ParseArguments():
    parser = argparse.ArgumentParser(
        description='Python Server to used to send/receive anchonet protocol')
    parser.add_argument('-t', '--used_for_testing', type=bool, default=False,
                        help='Specify that this instance of the server is used for testing')

    parser.add_argument('--sever_port', type=int, default=5001,
                        help='specify server port')
    parser.add_argument('--buffer_size', type=int, default=1024,
                        help='specify server buffer size')
    args = parser.parse_args()
    return args


if __name__ == "__main__":
    print("Starting python server")
    inputs_arguments = ParseArguments()
    used_for_testing = bool(inputs_arguments.used_for_testing)
    server_port = inputs_arguments.sever_port
    buffer_size = inputs_arguments.buffer_size
    print("Starting python server on {} for Testing: {} Buffer Size: {}".format(
        server_port, used_for_testing, buffer_size))
    protocol_server = UdpAgentsServer(
        server_port=server_port, buffer_size=buffer_size, used_for_testing=used_for_testing)
    protocol_server.StartServer()
