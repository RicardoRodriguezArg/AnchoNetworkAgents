#ifndef __AGENTS_MIDDLEWARE_DATA_FACTORY_COMMAND_FACTORY_H_
#define __AGENTS_MIDDLEWARE_DATA_FACTORY_COMMAND_FACTORY_H_

#include "data_types/data_types.h"
#include <vector>

namespace agents {
  namespace middleware {
    using agents::middleware::commands;
    using InternalCommandsHandler =
      std::tuple<StopDeviceCommand, StartAllDevices, StartDevice, ResetDevice,
                 RequestStatusOfAllDevices, RequestCurrentStatus, StopDevice>;
    using CommandMessageDict =
      MessageDictionary<::agent_interface_CommandWithArguments>;

    std::vector<std::uint8_t> GetAllCommandsCodesFromDataBase();
    ::agent_interface_CommandWithArguments GetNanoCommandDefinitionFromDataBase(
      std::uint8_t);

    InternalCommandsHandler CreateAllInternalCommands();

    CommandMessageDict CreateAllNanoCommands();

  } // namespace middleware
} // namespace agents
#endif