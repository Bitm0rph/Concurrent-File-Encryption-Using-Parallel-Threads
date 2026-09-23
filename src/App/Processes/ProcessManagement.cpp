#include "ProcessManagement.hpp"
#include "../encryptDecrypt/Cryption.hpp"
#include <iostream>

ProcessManagement::ProcessManagement() : stopPool(false) {}

ProcessManagement::~ProcessManagement()
{
  stopPool = true;
  cv.notify_all();
  for (auto &thread : workers)
  {
    if (thread.joinable())
    {
      thread.join();
    }
  }
}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> &task)
{
  {
    std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.push(std::move(task));
  }
  cv.notify_one();
  return true;
}

void ProcessManagement::workerThread()
{
  while (true)
  {
    std::unique_ptr<Task> taskToExecute;

    {
      std::unique_lock<std::mutex> lock(queueMutex);
      cv.wait(lock, [this]()
              { return stopPool || !taskQueue.empty(); });

      if (stopPool && taskQueue.empty())
      {
        return;
      }
      taskToExecute = std::move(taskQueue.front());
      taskQueue.pop();
    }

    const std::string task_to_exe = taskToExecute->toString();

    {
      std::lock_guard<std::mutex> coutLock(coutMutex);
      std::cout << "Executing task: " << task_to_exe
                << " on Thread ID: " << std::this_thread::get_id() << std::endl;
    }

    excecuteCryption(task_to_exe);
  }
}

void ProcessManagement::executeTasks()
{
  unsigned int numThreads = std::thread::hardware_concurrency();
  if (numThreads == 0)
    numThreads = 4;

  for (unsigned int i = 0; i < numThreads; ++i)
  {
    workers.emplace_back(&ProcessManagement::workerThread, this);
  }

  stopPool = true;
  cv.notify_all();

  for (auto &thread : workers)
  {
    if (thread.joinable())
    {
      thread.join();
    }
  }

  workers.clear();
  stopPool = false;
}