#include "builder/builder.h"
#include "builder/commands_buider.h"
#include <atomic>
#include <condition_variable>
#include <glog/logging.h>
#include <mutex>
#include <type_traits>

std::condition_variable main_server_condition_variable;
std::mutex server_mutex;
std::atomic<bool> server_is_operative{true};
void shutdownServerHandler(int code_value) {
  LOG(INFO) << "Shutdown Agent Server...";
  ::server_is_operative = false;
  ::main_server_condition_variable.notify_one();
}

int main(int argc, char* argv[]) {
  // TODO: Add Option handler from command line option
  // Configuration
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  FLAGS_max_log_size = 300;
  FLAGS_logtostderr = true;
  FLAGS_log_dir = std::move(std::string("./logs/"));
  google::InitGoogleLogging(argv[0]);
  // Catch Ctrl+C keyboard action
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = shutdownServerHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  // Create all commands
  agents::middleware::builders::Commands command_builder{};
  command_builder.Init();

  auto all_device_id = agents::middleware::builders::LoadDevicesIdsFromConfig();
  LOG(INFO) << "Total Devices loaded from DataBase:  " << std::to_string(all_device_id.size());

  LOG(INFO) << "Creating Device Proxy Manager";
  auto device_proxy_manager = agents::middleware::builders::CreateProxyManagerFromConfig();
  auto device_proxy_manager_ptr =
    std::make_shared<agents::middleware::builders::ProxyManagerType>(device_proxy_manager);
  LOG(INFO) << "Creating Internal Commands";
  auto internal_commands = agents::middleware::builders::CreateAllInternalCommandsHandlers(device_proxy_manager_ptr);
  LOG(INFO) << "Loading Server Options";
  auto server_options = agents::middleware::builders::LoadServerOptions();
  LOG(INFO) << "Build Message Handlers";
  auto message_handler = agents::middleware::builders::BuildMessageHandler();
  LOG(INFO) << "Configuring Message Handlers";
  message_handler = agents::middleware::builders::ConfigureMessageHandler(message_handler);
  LOG(INFO) << "Creating Main Udp server";
  auto main_udp_server =
    agents::middleware::builders::CreateAndConfigureMainServerFromConfig(message_handler, server_options);
  LOG(INFO) << "Initializing Server";
  main_udp_server->Init();
  LOG(INFO) << "Starting Server";
  main_udp_server->StartServerThread();
  {
    std::unique_lock<std::mutex> server_unique_lock(server_mutex);
    if (server_is_operative) {
      main_server_condition_variable.wait(server_unique_lock);
    }
    server_is_operative = false;
  }

  LOG(INFO) << "Server is operative";

  LOG(INFO) << "Shutting down Server";
  main_udp_server->Stop();
  // Create External Command Executor
  // Create Event Data Dispatcher
  // Create Telemetry Data Dispatcher
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
