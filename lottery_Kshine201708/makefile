
CC:=gcc

DEPEND:=obj/main.o
DEPEND+=obj/lotcontrol.o
DEPEND+=obj/fun.o
DEPEND+=obj/udrl.o
DEPEND+=obj/lotview.o
DEPEND+=obj/loadsave.o
DEPEND+=obj/freelink.o
DEPEND+=obj/pic.o
DEPEND+=obj/lottery.o
DEPEND+=obj/gamejsd.o

bin/main:$(DEPEND)
	$(CC)    $^ -o $@
obj/%.o:src/%.c
	$(CC) -c $^ -o $@ -Iinclude

clean:
	rm -rf obj/$(DEPEND)
	rm -rf src/*.c~




