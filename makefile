OBJECTS = nsh.o Program_Control.o
	  #(listing all of you object files here, separated by space)
#HEADERS = Program_Control.h
	  #(listing all header file here, separated by spaces)
nsh: $(OBJECTS)
	clear
	@g++ $^ -o nsh
	@./nsh
%.o: %.cpp $(HEADERS)
	@g++ -c $< -o $@
clean:
	rm -f *.o nsh
