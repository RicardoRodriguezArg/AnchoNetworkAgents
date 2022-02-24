from flask import Flask
from flask import request

app = Flask(__name__)

@app.route('/agents-webapi/cmd/', methods=['POST'])
def commands():
    commands = request.get_json()
    command_id = commands['id']
    argument_count = Int(request_data['argument_count'])
    arguments = commands['arguments']
    for index in xrange(argument_count):
        command_name = arguments[index]['name']
        command_value = arguments[index]['value']


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=105)
