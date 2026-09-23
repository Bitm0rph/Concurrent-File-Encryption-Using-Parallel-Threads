CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall

SRC = main.cpp \
      Src/App/FileHandling/IO.cpp \
      Src/App/FileHandling/ReadEnv.cpp \
      Src/App/Processes/ProcessManagement.cpp \
      Src/App/encryptDecrypt/Cryption.cpp

OUT = encrypt_app

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)