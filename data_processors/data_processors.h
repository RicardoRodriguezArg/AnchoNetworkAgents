#ifndef __AGENTS_MIDDLEWARE_DATA_PROCESSOR_H_
#define __AGENTS_MIDDLEWARE_DATA_PROCESSOR_H_
#include <algorithm>
#include <condition_variable>
#include <thread>

#include "common/commons.h"

#include "utils/utils.h"

namespace agents {
  namespace middleware {

    template <typename Processor>
    class DataProcessor {
    public:
      explicit DataProcessor(const Processor& processor) : processor_(processor) {}

      void Enqueue(const std::string& raw_message) {
        std::lock_guard<std::mutex> lock(data_processor_mutex_);
        if (is_working_ && !raw_message.empty()) {
          message_queue_.push_back(raw_message);
          condition_variable_.notify_one();
        }
      }

      ~DataProcessor() {
        Stop();
        working_thread_.join();
      }

      void Start() {
        if (!is_working_) {
          is_working_ = true;
          working_thread_ = std::thread(&DataProcessor::run, this);
        }
      }

      void Stop() {
        std::lock_guard<std::mutex> lock(data_processor_mutex_);
        is_working_ = false;
        condition_variable_.notify_one();
      }

    private:
      void run() {
        while (is_working_) {
          std::unique_lock<std::mutex> lock(data_processor_mutex_);
          while (is_working_ && message_queue_.empty()) {
            condition_variable_.wait(lock);
          }

          if (!is_working_) {
            data_processor_mutex_.unlock();
            condition_variable_.notify_one();
            break;
          }

          if (!message_queue_.empty()) {
            const auto& raw_message = message_queue_.top();
            processor_.Process(raw_message);
          }
        }
      }

      const Processor& processor_;
      std::atomic<bool> is_working_;
      std::queue<std::string> message_queue_;
      std::condition_variable condition_variable_;
      std::mutex data_processor_mutex_;
      std::thread working_thread_;
    };

  } // namespace middleware
} // namespace agents
#endif
