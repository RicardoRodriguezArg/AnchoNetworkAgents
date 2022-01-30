#include "data_factory.h"
namespace agents {
  namespace middleware {
    {
      std::vector<std::uint8_t> GetAllCommandsCodesFromDataBase() { return {}; }
      ::agent_interface_CommandWithArguments
      GetNanoCommandDefinitionFromDataBase(std::uint8_t) {
        ::agent_interface_CommandWithArguments result;
        return result;
      }

      InternalCommandsHandler CreateAllInternalCommands() {
        InternalCommandsHandler internal_commands;
        return internal_commands;
      }

      MessageDictionary<::agent_interface_CommandWithArguments>
      CreateAllNanoCommands() {
        MessageDictionary<::agent_interface_CommandWithArguments> result;
        return result;
      }
    } // namespace middleware
  }   // namespace middleware