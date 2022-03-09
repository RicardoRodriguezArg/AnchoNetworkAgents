from flask import Flask
from flask import request
from agents_proxy import SendCommandToServer
import logging
import os
dir_path = os.path.dirname(os.path.realpath(__file__))
app = Flask(__name__)


logging.basicConfig(filename='agents-webapi-server.log', level=logging.INFO)

@app.route('/agents-webapi/', methods=['GET'])
def Welcome():
    return 'Agents WebApi'

@app.route('/agents-webapi/cmd/', methods=['POST'])
def commands():
    webapi_command = request.get_json()
    command_id = webapi_command['id']
    print("command_id: {}".format(command_id))
    argument_count = int(webapi_command['argument_count'])
    arguments = webapi_command['arguments']
    for index in range(argument_count):
        argument_name = arguments[index]['name']
        command_value = arguments[index]['value']
        print("name:  {} value: {}".format(argument_name, command_value))
    #executing command on agents-middleware
    response_from_server = SendCommandToServer(webapi_command)
    execution_status = response_from_server(0)
    command_response = response_from_server(1)
    return {'status':execution_status, 'response':command_response}


if __name__ == '__main__':
    logging.info('Agents WebApi init at port 5000')
    app.run(host='127.0.0.1', port=5000)
