OBJECTS = nsh.o Program_Control.o Builtin_Cmds.o
	  #(listing all of you object files here, separated by space)
#HEADERS = Program_Control.h Builtin_Cmds.h
	  #(listing all header file here, separated by spaces)
nsh: $(OBJECTS)
	clear
	@g++ -Wall -g $^ -o nsh
	@./nsh # < testCmds.txt
%.o: %.cpp $(HEADERS)
	@g++ -c $< -o $@
clean:
	rm -f *.o nsh
g: $(OBJECTS)
	clear
	@g++ -Wall -g $^ -o nsh
	@gdb nsh
