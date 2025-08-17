TARGET = bin/output
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run : clean default
	./$(TARGET) -n -f testfile.db

default: $(TARGET)

clean:
	rm -f bin/*
	rm -f obj/*.o
	rm -f *.db

$(TARGET) : $(OBJ)
	gcc -o $@ $?

obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinclude
