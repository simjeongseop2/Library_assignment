CXX = g++
TARGET = hw1
OBJECTS = main.o member.o resource.o library.o space.o

$(TARGET) : member.h resource.h date.h library.h space.h main.o member.o resource.o library.o space.o
	$(CXX) -o $(TARGET) $(OBJECTS)
main.o : member.h resource.h date.h library.h space.h main.cpp
	$(CXX) -c -o main.o main.cpp

member.o : member.h date.h member.cpp
	$(CXX) -c -o member.o member.cpp

resource.o : member.h resource.h date.h resource.cpp
	$(CXX) -c -o resource.o resource.cpp

space.o : space.h date.h space.cpp
	$(CXX) -c -o space.o space.cpp

library.o : member.h resource.h space.h date.h member.cpp resource.cpp library.cpp
	$(CXX) -c -o library.o library.cpp

clean :
	rm *.o $(TARGET)
