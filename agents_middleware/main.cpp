#include "builder/builder.h"
#include "communication/server.h"

#include <type_traits>

int main() {
  const auto& commands_ids_lists = GetAllCommandsIDsFromDataBase();
  auto nano_commands_list = CreateAllNanoCommands(commands_ids_lists);
  auto internal_commands_list = CreateAllInternalCommands(commands_ids_lists);

  static_assert(nano_commands_list.size() == internal_commands_list.size());

  return 0;
}
