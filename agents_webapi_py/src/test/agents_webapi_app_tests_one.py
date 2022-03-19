import pytest
from agents_webapi_py.src.agents_webapi_app import app


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
    assert "Main C++ Server Not Responding, timeout" in resp.json.get('execution_status') 



if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
