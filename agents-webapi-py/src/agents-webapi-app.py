from flask import Flask
from flask import request
import logging
app = Flask(__name__)


logging.basicConfig(filename='agents-webapi-server.log', level=logging.INFO)

@app.route('/agents-webapi/', methods=['GET'])
def Welcome():
    return 'Agents WebApi'

@app.route('/agents-webapi/cmd/', methods=['POST'])
def commands():
    commands = request.get_json()
    command_id = commands['id']
    argument_count = Int(request_data['argument_count'])
    arguments = commands['arguments']
    for index in xrange(argument_count):
        command_name = arguments[index]['name']
        command_value = arguments[index]['value']
    #executing command on agents-middleware
    return {'executed': True}


if __name__ == '__main__':
    logging.info('Agents WebApi init at port 5000')
    app.run(host='127.0.0.1', port=5000)
