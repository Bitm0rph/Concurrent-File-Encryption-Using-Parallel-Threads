# Multithreaded-File-Encryption-Engine

A high-performance, multithreaded C++ application designed to perform bulk file encryption and decryption. By utilizing a custom Thread Pool and modern C++ concurrency features, this engine processes multiple files simultaneously in the background, significantly reducing execution time for large directories.

## Features

* **Thread Pool Architecture:** Utilizes `<thread>`, `<mutex>`, and `<condition_variable>` to dynamically spawn worker threads based on hardware concurrency, allowing simultaneous processing of multiple files.
* **Thread-Safe Task Queue:** Implements a synchronized task queue to securely distribute file operations across background workers without race conditions.
* **Raw Binary File I/O:** Custom `<fstream>` module reads and writes data in strict binary mode, ensuring zero data corruption regardless of the file type (text, images, executables, etc.).
* **Modular OOP Design:** Clean separation of concerns with distinct modules for File Handling, Process Management, and Cryptography, making the codebase highly scalable and maintainable.
* **Secure Environment Configuration:** Dynamically extracts the encryption key from a hidden `.env` configuration file, demonstrating industry best practices for credential management.

## Prerequisites

To build and run this project, you will need:
* A C++ compiler that supports **C++17** (e.g., GCC, Clang).
* `make` build automation tool.
* A POSIX-compliant operating system (Linux/macOS) or Windows with MinGW/WSL.

## Installation & Compilation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/Multithreaded-File-Encryption-Engine.git](https://github.com/YOUR_USERNAME/Multithreaded-File-Encryption-Engine.git)
   cd Multithreaded-File-Encryption-Engine
2. **Setup the Environment Key:**
   ```bash
   echo "5" > .env
3. **Compile the engine:**
   ```bash
   make
   
## Usage
1. Run the executable: ./encrypt_app
2. Follow the on-screen prompts:
Directory Path: Provide the relative or absolute path to the folder containing the files you wish to process (e.g., Test_Files).
Action: Type ENCRYPT to secure the files, or DECRYPT to restore them to their original state.
   ```bash
   Enter the directory path: 
   Test_Files
   Enter the action ('ENCRYPT'/'DECRYPT'): 
   ENCRYPT
   Executing task: Test_Files/document.pdf,ENCRYPT on Thread ID: 140234
   Executing task: Test_Files/image.png,ENCRYPT on Thread ID: 140235
   Finished Encryption : 2026-09-18 14:30:00
   
 ## Project Structure
```text
Multithreaded-File-Encryption-Engine/
├── .env                        # Hidden file containing the secret numeric key
├── Makefile                    # Compilation rules
├── main.cpp                    # Application entry point and directory traversal
└── Src/
    └── App/
        ├── FileHandling/       # Secure file opening, closing, and environment reading
        │   ├── IO.hpp / .cpp
        │   └── ReadEnv.hpp / .cpp
        ├── Processes/          # Thread Pool, Mutex locks, and Task Queue logic
        │   ├── Task.hpp
        │   └── ProcessManagement.hpp / .cpp
        └── encryptDecrypt/     # Core cryptographic data manipulation
            └── Cryption.hpp / .cpp