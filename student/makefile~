
CC:=gcc

DEPEND:=obj/main.o
DEPEND+=obj/student.o
DEPEND+=obj/stucontrol.o
DEPEND+=obj/stuview.o

bin/main:$(DEPEND)
	$(CC)    $^ -o $@
obj/%.o:src/%.c
	$(CC) -c $^ -o $@ -Iinclude

clean:
	rm -rf obj/$(DEPEND)
	rm -rf src/*.c~
