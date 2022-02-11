#include "builder/builder.h"

#include <type_traits>

int main() {
  // TODO: Add command line argument parser
  // TODO: Add Logger
  using namespace agents::middleware::builders;

  // Create all commandas
  const auto& commands_ids_lists = GetAllCommandsIDsFromDataBase();
  auto nano_commands_list = CreateAllNanoCommands(commands_ids_lists);
  auto all_device_id = LoadDevicesIdsFromConfig();
  [&commands_ids_lists, &nano_commands_list, &all_device_id] {}();

  return 0;
}
