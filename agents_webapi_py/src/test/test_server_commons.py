def CreateJsonForTestDict():
    json_to_send = {"id": "1",
                    "argument_count": "2",
                    "source": "main_web",
                    "target": "generic_tp_link_router",
                    "request_ack": "true",
                    "arguments": [
                        {"name": "speed",
                          "value": "300"
                         },
                        {"name": "service_type",
                         "value": "home"
                         }
                    ]
                    }
    return json_to_send


def CreateShutDownJsonForTestDict():
    json_to_send = {"id": "4",
                    "argument_count": "0",
                    "source": "main_web",
                    "target": "web_api_python_client",
                    "request_ack": "true",
                    "arguments": [
                    ]
                    }
    return json_to_send


def CreateEmptyJsonDict():
    return {}


def CreateJsonDictWithInvalidArgumentCount():
    json_to_send = {"id": "1",
                    "argument_count": "3",
                    "source": "main_web",
                    "target": "generic_tp_link_router",
                    "request_ack": "true",
                    "arguments": [
                        {"name": "speed",
                          "value": "300"
                         },
                        {"name": "service_type",
                         "value": "home"
                         }
                    ]
                    }
    return json_to_send
