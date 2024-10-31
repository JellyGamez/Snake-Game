SRC := main.cpp

ifeq ($(OS),Windows_NT)
	FLAGS := -o
	TARGET := main.exe
	CLEAN := del
else
	FLAGS := -lncurses -o
	TARGET := main
	CLEAN := rm
endif

all:
	g++ $(SRC) $(FLAGS) $(TARGET)
clean:
	$(CLEAN) -rf $(TARGET)
