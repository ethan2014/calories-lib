CC	= g++
FLAGS	= -std=c++14 -Wall -Werror -pedantic -O3 -lboost_system -lboost_filesystem
SOURCE	= *.cpp
TARGET	= main

all: $(TARGET)

$(TARGET):
	$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm $(TARGET)
