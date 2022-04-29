import pytest
import subprocess
from agents_webapi_py.src.agents_webapi_app import app
import logging

class BashSystemCommandsManager:
    def __init__(self):
        pass

    def __execute_commands(self, command_to_execute):
        process = subprocess.Popen([command_to_execute],stdout=subprocess.PIPE,stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        return (len(stderr) == 0)

    def init_agents_server(self):
        result = self.__execute_commands('agents_middleware_server')
        return result

    def kill_agents_server(self):
        result = self.__execute_commands('killall agents_middleware_server')
        return result


@pytest.fixture
def client():
    return app.test_client()


def test_home(client):
    resp = client.get('/agents-webapi/')
    print("testing commands...")
    assert resp.status_code == 200


def test_service_fail(client):
    resp = client.post('/agents-webapi/cmd/', \
        json={'id': '1', 'argument_count': '2', 'source': 'main_web','target': 'modem_wifi',\
        'request_ack': 'true',\
        'arguments': [
                      { "name":"speed" ,  "value":"300" }, \
                      { "name":"service_type" , "value":"home" }\
                      ]})
    assert resp.status_code == 200
    execution_status = resp.json.get('execution_status')
    print("print: {}".format(execution_status))
    assert "Communication Error: timed out" in execution_status


def test_service_agent_commands(client):
    bash_command_executor = BashSystemCommandsManager()
    logging.info('Test Server C++ Agent')
    #bash_result = bash_command_executor.init_agents_server()
    #assert bash_result
    resp = client.post('/agents-webapi/cmd/', \
        json={'id': '1', 'argument_count': '2', 'source': 'main_web','target': 'modem_wifi',\
        'request_ack': 'true',\
        'arguments': [
                      { "name":"speed" ,  "value":"300" }, \
                      { "name":"service_type" , "value":"home" }\
                      ]})
    #assert resp.status_code == 200
    #expected_valid_result = "Main C++ Server Not Responding, timeout" in resp.json.get('execution_status')
    #bash_result = bash_command_executor.init_agents_server()



if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
