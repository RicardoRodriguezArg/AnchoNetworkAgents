from flask import Flask
from flask import request
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
    commands = request.get_json()
    command_id = commands['id']
    print("command_id: {}".format(command_id))
    argument_count = int(commands['argument_count'])
    arguments = commands['arguments']
    for index in range(argument_count):
        argument_name = arguments[index]['name']
        command_value = arguments[index]['value']
        print("name:  {} value: {}".format(argument_name, command_value))
    #executing command on agents-middleware
    return {'executed': True}


if __name__ == '__main__':
    logging.info('Agents WebApi init at port 5000')
    app.run(host='127.0.0.1', port=5000)
