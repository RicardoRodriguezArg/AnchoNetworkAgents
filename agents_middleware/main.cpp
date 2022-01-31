#include "builder/builder.h"

#include <type_traits>

int main() {
  // TODO: Add command line argument parser
  // TODO: Add Logger

  // Create all commandas
  const auto& commands_ids_lists = GetAllCommandsIDsFromDataBase();
  auto nano_commands_list = CreateAllNanoCommands(commands_ids_lists);
  auto internal_commands_list = CreateAllInternalCommands(commands_ids_lists);

  static_assert(nano_commands_list.size() == internal_commands_list.size());

  return 0;
}
