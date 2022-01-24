#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_EVENTS_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_EVENTS_H_

#include "data_processors/data_processor_commons.h"

namespace agents {
namespace middleware {
struct EventsProcessor {
  void Process(const std::string &raw_message) {
    if (!raw_message.empty()) {
      const auto decoded_event = data_decoder_.DecodeToEvent(raw_message);
      ProcessEvents(decoded_command);
    }
  }

private:
  void ProcessEvents(const ::_agent_interface_Event &event) {
    switch (event.id) {
    case 1: {

    } break default : {
    }
      break;
    }
  }

  DataDecoder data_decoder_;
  ;
};
} // namespace middleware
} // namespace agents
#endif