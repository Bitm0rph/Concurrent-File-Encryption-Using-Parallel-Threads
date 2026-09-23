#include <iostream>
#include <filesystem>
#include "src/App/Processes/ProcessManagement.hpp"
#include "src/App/Processes/Task.hpp"
#include "src/App/FileHandling/IO.hpp"
#include <string>
#include <exception>

int main()
{
  std::string directory;
  std::string action;

  std::cout << "Enter the directory path: " << std::endl;
  std::getline(std::cin, directory);

  std::cout << "Enter the action ('ENCRYPT'/'DECRYPT'): " << std::endl;
  std::getline(std::cin, action);

  try
  {
    if (std::filesystem::exists(directory) && std::filesystem::is_directory(directory))
    {
      ProcessManagement processManagement;
      for (const auto &entry : std::filesystem::recursive_directory_iterator(directory))
      {
        if (entry.is_regular_file())
        {
          std::string filePath = entry.path().string();
          IO io(filePath);
          std::fstream f_stream = io.getFileStream();

          if (f_stream.is_open())
          {
            Action act = (action == "ENCRYPT") ? Action::ENCRYPT : Action::DECRYPT;
            auto task = std::make_unique<Task>(std::move(f_stream), act, filePath);
            processManagement.submitToQueue(task);
          }
          else
          {
            std::cout << "Unable to Open File: " << filePath << std::endl;
          }
        }
      }
      // Starts the thread pool and encrypts everything simultaneously
      processManagement.executeTasks();
    }
    else
    {
      std::cout << "Directory does not exist or action is invalid" << std::endl;
    }
  }
  catch (const std::filesystem::filesystem_error &ex)
  {
    std::cout << "File System Error : " << ex.what() << std::endl;
  }

  return 0;
}