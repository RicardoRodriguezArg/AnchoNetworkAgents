import socket
from datetime import date
import time
import json
from interface.message_interface_idl_pb2 import CommandWithArguments
from interface.message_interface_idl_pb2 import Header
from agents_proxy_stub_utils import PackBinaryData
import logging

class AgentStub:
  def __init__(self, server_ip="127.0.0.1", server_port=5000, buffer_size=1024):
    self.__cmd_proto = None
    self.__bytesToSend = 0
    self.__server_ip = server_ip
    self.__server_port = server_port
    self.__buffer_size = buffer_size
    self.__udp_client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    self.__udp_client.settimeout(1)
    self.__wait_for_response = False
    self.__response_result = None
    self.__execution_status = { "message_id": -1, "status": "uninit"}
    self.__message_id = 0

  def ConvertToCmdProtoMessage(self, message_from_webapi):
    self.__cmd_proto = CommandWithArguments()
    cmd_proto.id = message_from_webapi['id']
    argument_count = int(message_from_webapi['argument_count'])
    cmd_proto.number_arg_count = argument_count
    cmd_proto.header = self.__CreateHeaderMessageFromJson(message_from_webapi)
    arguments = message_from_webapi['arguments']
    for index in range(argument_count):
        cmd_proto.name.append(arguments[index]['name'])
        cmd_proto.value.append(arguments[index]['value'])
    return cmd_proto

  def __CreateHeaderMessageFromJson(self, message_from_webapi):
    header= Header()
    header.target_agent_id = Header.SERVER_UDP_X86
    header.source_agent_id = Header.WEB_API_PYTHON
    current_year = date.today().year
    current_month = date.today().month
    current_day = date.today().day
    a_date = datetime.date(current_year, current_month, current_day)
    week_number = a_date.isocalendar()[1]
    header.year = current_year
    header.week_number = week_number
    header.timestamp = time.time()
    header.request_ack = message_from_webapi['request_ack']
    self.__wait_for_response = header.request_ack
    header.source_device_type = Header.WEB_API_PYTHON
    header.target_device_type = Header.SERVER_UDP_X86
    header.message_id =  self__message_id
    self.UpdatingExecutionResultMessageID(header.message_id)
    self.__message_id = self.__message_id + 1
    return header

  def SendCmdToServer(self):
    result = False
    if not self.__cmd_proto:
      self.__UpdatingExecutionResultStatus("Cmd Proto Empty")
      return result
    message = self.__cmd_proto.SerializeToString()
    packed_data = PackBinaryData(message)
    self.__udp_client.sendto(packed_data, (self.__server_ip, self.__server_port))
    self.__UpdatingExecutionResultStatus("Command Sent")
    if self.__wait_for_response:
      self.__UpdatingExecutionResultStatus("Command sent, waiting ACK")
      try:
         data, server = clientSocket.recvfrom(self.__buffer_size)
         unpacked_response = UnpackBinaryData(data)
         self.__response_result = ProcessProtoMessage(unpacked_response)
         self.__UpdatingExecutionResultStatus("Command executed")
         result = True
      except timeout:
        self.__UpdatingExecutionResultStatus("Main C++ Server Not Responding, timeout")
        print("Error on Execution Command")
    return result

    def __UpdatingExecutionResultMessageID(self, message_id):
      self.__execution_status["message_id"] = message_id

    def __UpdatingExecutionResultStatus(self, status_message):
          self.__execution_status["status"] = status_message

    def GetResponseResul(self):
      return self.__response_result

    def GetExecutionStatus(self):
      return json.dumps(self.__execution_status)
