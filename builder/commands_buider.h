#ifndef __AGENTS_MIDDLEWARE_MIDDLEWARE_COMMAND_BUILDER_H_
#define __AGENTS_MIDDLEWARE_MIDDLEWARE_COMMAND_BUILDER_H_
#include "builder/builder.h"
#include <glog/logging.h>

namespace agents {
  namespace middleware {
    namespace builders {
      class Commands {
      public:
        explicit Commands(const std::string_view path_to_database = "") : path_to_database_(path_to_database) {}

        void Init() {
          if (path_to_database_.empty()) {
            // 1.-load database
            LOG(INFO) << "Default construction - Loading Default commands id - no database specify";
            commands_id_from_database_ = agents::middleware::builders::GetAllCommandsIDsFromDataBase();
            // 2.- Create system Commands from inputs IDs
            LOG(INFO) << "Default construction - Creating System commands ";
            sys_commands_dictory_ =
              agents::middleware::builders::CreateAllSystemCommands(commands_id_from_database_); // Done
          }
        }

        const CommandMessageDict& GetSystemCommandsIds() const { return sys_commands_dictory_; }

      private:
        const std::string_view path_to_database_;
        std::vector<std::uint8_t> commands_id_from_database_{};
        CommandMessageDict sys_commands_dictory_;
      };
    } // namespace builders
  }   // namespace middleware
} // namespace agents
#endif
