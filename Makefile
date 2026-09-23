CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall

SRC = main.cpp \
      src/App/FileHandling/IO.cpp \
      src/App/FileHandling/ReadEnv.cpp \
      src/App/Processes/ProcessManagement.cpp \
      src/App/encryptDecrypt/Cryption.cpp

OUT = encrypt_app

.PHONY: all run clean

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)