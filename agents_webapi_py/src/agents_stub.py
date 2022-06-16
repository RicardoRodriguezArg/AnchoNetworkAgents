import socket
import datetime
from datetime import date
import time
import json
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Header
from agents_webapi_py.src.agents_proxy_stub_utils import PackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import UnpackBinaryData
from agents_webapi_py.src.agents_proxy_stub_utils import ProcessProtoMessage
import logging


class AgentStub:
    def __init__(self, server_ip="127.0.0.1", target_server_port=5001, local_server_port=50100, buffer_size=1024):
        self.__cmd_proto = None
        self.__bytesToSend = 0
        self.__server_ip = server_ip
        self.__server_port = target_server_port
        self.__buffer_size = buffer_size
        self.__udp_sock = socket.socket(
            family=socket.AF_INET, type=socket.SOCK_DGRAM)
        self.__udp_sock.settimeout(3)
        self.__wait_for_response = False
        self.__response_result = None
        self.__execution_status = {"message_id": -1, "execution": "uninit"}
        self.__message_id = 0

    def command_proto(self):
        return self.__cmd_proto

    def __check_argument_count(self, message_dict_from_webapi):
        argument_count = int(message_dict_from_webapi["argument_count"])
        arguments = message_dict_from_webapi['arguments']
        print("arguments: {}".format(len(arguments)))
        print("argument_count".format(argument_count))
        print("checking arg count: {}".format(
            len(arguments) == argument_count))
        return len(arguments) == argument_count

    def __check_proper_arguments_in_message(self, message_from_webapi):
        arguments_to_check = ["id", "argument_count",
                              "source", "target", "request_ack", "arguments"]
        result = True
        for argument in arguments_to_check:
            if not argument in message_from_webapi:
                result = False
                break
        return result

    def __is_valid_webapi_message(self, dictionary_message_from_webapi):
        if len(dictionary_message_from_webapi) == 0:
            return False
        elif not self.__check_proper_arguments_in_message(dictionary_message_from_webapi):
            return False
        elif not self.__check_argument_count(dictionary_message_from_webapi):
            return False
        return True

    def ConvertToCmdProtoMessage(self, message_from_webapi):
        if not self.__is_valid_webapi_message(message_from_webapi):
            logging.error('Invalid Input Json Dictionary Detected')
            return
        self.__cmd_proto = CommandWithArguments()
        self.__cmd_proto.id = int(message_from_webapi['id'])
        self.__cmd_proto.state = CommandWithArguments.State.SENT
        argument_count = int(message_from_webapi['argument_count'])
        self.__cmd_proto.number_arg_count = argument_count
        processed_header = self.__CreateHeaderMessageFromJson(
            message_from_webapi)
        self.__cmd_proto.header.CopyFrom(processed_header)
        arguments = message_from_webapi['arguments']
        for index in range(argument_count):
            self.__cmd_proto.name.append(arguments[index]['name'])
            self.__cmd_proto.value.append(arguments[index]['value'])

    def __UpdatingExecutionResultMessageID(self, message_id):
        self.__execution_status["message_id"] = message_id

    def __GetTargetsIdFromJson(self, target_id_string):
        switcher = {
            'server_udp_x86_talca': Header.SERVER_UDP_X86_TALCA_ID,
            'web_api_python_client': Header.WEB_API_PYTHON_CLIENT_ID,
            'generic_tp_link_router': Header.GENERIC_TP_LINK_ROUTER_ID,
            'main_web': Header.MAIN_WEB_SITE
        }
        return switcher[target_id_string]

    def __CreateHeaderMessageFromJson(self, message_from_webapi):
        header = Header()
        header.target_agent_id = self.__GetTargetsIdFromJson(
            message_from_webapi["target"])
        header.source_agent_id = self.__GetTargetsIdFromJson(
            message_from_webapi["source"])
        current_year = date.today().year
        current_month = date.today().month
        current_day = date.today().day
        a_date = datetime.date(current_year, current_month, current_day)
        week_number = a_date.isocalendar()[1]
        header.year = current_year
        header.week_number = week_number
        header.timestamp = time.time()
        header.request_ack = int(False)
        if message_from_webapi['request_ack'] == "true":
            header.request_ack = int(True)
        self.__wait_for_response = header.request_ack
        header.source_device_type = Header.PYTHON_CLIENT
        header.target_device_type = Header.SERVER_UDP_X86
        header.message_type = Header.COMMAND
        """
        this is a mandatory field for message comming from entities
        like this, a administrative id force the server to check
        the id on the interface list of ID to validate the source
        id, if this is not set command will be not executed
        """
        header.has_administrative_id = int(True)
        header.message_id = self.__message_id
        self.__UpdatingExecutionResultMessageID(header.message_id)
        self.__message_id = self.__message_id + 1
        return header

    def __UpdatingExecutionResultStatus(self, status_message=None):
        if status_message:
            self.__execution_status["execution"] = status_message

    def GetExecutionStatus(self):
        return json.dumps(self.__execution_status)

    def GetResponseResult(self):
        return self.__response_result

    def ShouldWaitForResponse(self):
        return self.__wait_for_response

    def SendCmdToServer(self):
        print('Sending to Ip: {} and port: {}'.format
              (
                  self.__server_ip, self.__server_port))
        result = False
        if not self.__cmd_proto:
            print("Exit due to empty protocol buffer")
            self.__UpdatingExecutionResultStatus("Cmd Proto Empty")
            return result
        message = self.__cmd_proto.SerializeToString()
        self.__cmd_proto.Clear()
        packed_data = PackBinaryData(message)
        self.__udp_sock.sendto(
            packed_data, (self.__server_ip, self.__server_port))
        self.__UpdatingExecutionResultStatus("Command Sent")
        print("Wait for response: {}".format(self.__wait_for_response))
        if self.__wait_for_response:
            self.__UpdatingExecutionResultStatus("Command sent, waiting ACK")
            step = 0
            max_step_count = 1
            while step < max_step_count:
                try:
                    data = self.__udp_sock.recvfrom(self.__buffer_size)
                    unpacked_response = UnpackBinaryData(data[0])
                    self.__response_result = ProcessProtoMessage(unpacked_response)
                    print("Command Executed!!")
                    self.__UpdatingExecutionResultStatus("Command executed")
                    result = True
                except Exception as error:
                    self.__response_result = None
                    self.__UpdatingExecutionResultStatus(
                        "Communication Error: {}".format(str(error)))
                    print("Error on Execution Command: {}".format(str(error)))
                step = step + 1
                time.sleep(1)
        return result
