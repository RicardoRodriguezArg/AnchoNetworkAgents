#include "builder/builder.h"
#include <glog/logging.h>
#include <iostream>
#include <type_traits>

int main(int argc, char* argv[]) {
  // TODO: Add Option handler from command line option
  FLAGS_max_log_size = 300;
  FLAGS_logtostderr = true;
  FLAGS_log_dir = std::move(std::string("./logs/"));
  google::InitGoogleLogging(argv[0]);
  // ...
  using namespace agents::middleware::builders;
  // Create all commandas
  LOG(INFO) << "Loading all commands from DataBase ";
  const auto& commands_ids_lists = GetAllCommandsIDsFromDataBase();
  LOG(INFO) << "Commands Ids loaded:  " << std::to_string(commands_ids_lists.size());
  LOG(INFO) << "Creating all nano commands from id and database ";
  auto nano_commands_list = CreateAllNanoCommands(commands_ids_lists);
  [&nano_commands_list]() {};
  auto all_device_id = LoadDevicesIdsFromConfig();
  LOG(INFO) << "Total Devices loaded from DataBase:  " << std::to_string(all_device_id.size());

  LOG(INFO) << "Creating Device Proxy Manager";
  auto device_proxy_manager = CreateProxyManagerFromConfig();
  auto device_proxy_manager_ptr = std::make_shared<ProxyManagerType>(device_proxy_manager);
  LOG(INFO) << "Creating Internal Commands";
  auto internal_commands = CreateAllInternalCommandsHandlers(device_proxy_manager_ptr);
  LOG(INFO) << "Loading Server Options";
  auto server_options = LoadServerOptions();
  LOG(INFO) << "Build Message Handlers";
  auto message_handler = BuildMessageHandler();
  LOG(INFO) << "Configuring Message Handlers";
  message_handler = ConfigureMessageHandler(message_handler);
  LOG(INFO) << "Creating Main Udp server";
  const auto main_udp_server = CreateAndConfigureMainServerFromConfig(message_handler, server_options);
  // Create External Command Executor
  // Create Event Data Dispatcher
  // Create Telemetry Data Dispatcher

  return 0;
}
