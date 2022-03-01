import pytest
from flask import Flask
from flask.testing import FlaskClient
from agents-webapi-app import app


@pytest.fixture
def client():
    return app.test_client()


def test_home(client):
    resp = client.get('/agents-webapi/')
    assert resp.status_code == 200
    

def test_service(client):
    resp = client.post('/agents-webapi/cmd/', json={'command_id': '1', 'argument_count': '2', 'source': 'main_web','target': 'modem_wifi',
    	'argument_1': '0'})
    assert resp.status_code == 200
    assert resp.json.get('executed')
