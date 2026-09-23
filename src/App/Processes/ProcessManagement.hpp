#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class ProcessManagement
{
public:
   ProcessManagement();
   ~ProcessManagement();
   bool submitToQueue(std::unique_ptr<Task> &task);
   void executeTasks();

private:
   std::queue<std::unique_ptr<Task>> taskQueue;
   std::vector<std::thread> workers;
   std::mutex queueMutex;
   std::mutex coutMutex;
   std::condition_variable cv;
   bool stopPool;

   void workerThread();
};

#endif