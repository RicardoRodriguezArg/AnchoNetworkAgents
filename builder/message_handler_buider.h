#ifndef __AGENTS_MIDDLEWARE_MIDDLEWARE_MESSAGE_HANDLER_BUILDER_H_
#define __AGENTS_MIDDLEWARE_MIDDLEWARE_MESSAGE_HANDLER_BUILDER_H_
#include "builder/builder.h"
#include <glog/logging.h>

namespace agents {
  namespace middleware {
    namespace builders {
      class MessageHandlers {
      public:
        void Init() {}

        handlers::MessageHandlerManger GetMessageHandler() const { return message_handler_; }

      private:
        handlers::MessageHandlerManger message_handler_{};
      }; // namespace builders
    }    // namespace builders
  }      // namespace middleware
} // namespace agents
#endif
