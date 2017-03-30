# nsh
New Shell (nsh) - shell developed in c++

# Syntax

nsh is somewhat similar to existing shells such as csh, bash, ksh, and tcsh. However, it lacks many of the features of those shells. It also has a different command syntax and a different command set.

nsh takes commands from standard input and directs all its output to standard output.

Like other shells, nsh accepts both built-in commands and program-control commands.

Commands are constructed out of tokens. A token can be either a single word or a string surrounded by double-quotes. Tokens are subject to variable substitution, as described below. There can be any amount of empty space before and after tokens.

The % symbol introduces a comment, which continues to the end of the line. You may assume that % never appears within a token. nsh ignores all characters in a comment. If a line is empty (except perhaps for spaces) except for a comment, it is a valid command that has no effect.

# Built-in Commands

set variable value
Here, variable is any reasonable variable name (starting with a letter, continuing with letters or numbers), and value is a token. It is conventional for users to represent variables in ALL CAPITALS, but nsh does not enforce this convention. Variable names are case-sensitive, that is, home and HOME represent different variables. The effect of this command is to associate the name with the value of the variable in a data structure inside nsh.
prompt newPrompt
Set the shell prompt to newPrompt, which is a token. Do not add or subtract spaces at the end of the new prompt. The initial prompt in nsh is nsh > . (There is a space after the >.)
dir directoryName
This command changes the current directory to directoryName. The dir command must have a single parameter. See the getwd(3) and chdir(2) system calls. the directoryName may be either absolute (starting with /) or relative (not starting with /).
procs
nsh lists all processes running in the background, in any format you like. nsh should keep a list and not rely on external programs like ps to create its output.
done
nsh exits with exit status 0. nsh should also accept <control-D> (end-of-file) on the input stream and treat it as if the user had typed done. That is, if a user types <control-D> at the input, nsh performs exactly the same as when it receives the built-in command done.
Program-control commands

do cmd param* The user submits a do command to execute a program. The keyword do must appear as the first token on the command line, followed by the command to be executed. Here, cmd is a token that specifies the filename of the program the user wants to execute. It is followed by zero or more tokens specifying parameters. nsh should wait for the program to finish before it prompts for and accepts the next command.
nsh looks for cmd in a list of directories indicated by the variable PATH, whose value is a colon-separated list of directories. By default, PATH has value /bin:/usr/bin; the user can change that value by assigning a new value to PATH. If, however, cmd starts with a / character, it is a full path name starting at the root. Similarly, a cmd that starts with ./ is a path name starting in the current directory.

back cmd param* The back command is identical to the do command, except that the program should run in the background, that is, nsh should immediately prompt for and accept the next command.
tovar variable cmd param*
The tovar command executes the program cmd along with its parameters, if any, and assigns its output to the variable specified by variable. Like the do command, the variable PATH contains a colon-separated list of directories where nsh looks for the file to be executed. The file name to be executed may also be specified as a full path name or a name relative to the current directory.

# Invalid commands

If the user inputs an invalid command, nsh should simply print an error message (to stderr) and prompt for the next command.

# Sample commands

	set PATH "/bin:/usr/bin" % this is the default setting
	set HOME "/home/mylogin" % a useful shorthand
	set Myfile "/etc/hosts" % the quotes are unnecessary but valid
	set Filebase "paper"
	set ShowTokens 1 % a special token, described later
	do echo "my path is $PATH" % should output "my path is /bin:/usr/bin"
	dir /usr/bin % no output expected
	do ls awk % prints "awk".
	dir ../misc/oldstuff % prints an error message.
	dir $HOME
	do /usr/bin/wc -l $Myfile % prints "9 /etc/hosts".
	back wc -l $Myfile $Myfile % prints three lines
	back /bin/sleep 10 % immediately gives a new prompt
	procs % should list at least the /bin/sleep, maybe the wc process
	tovar TextFile /bin/echo -e $Filebase "\b.txt"
	do echo $TextFile % prints "paper.txt"
	do /bin/ls
	do ls -l -F -g -s /tmp
	done
  
# Details

You should write procedures to read a line from standard input, break the line into tokens (scanner), then analyze the line for correctness (parser). As it does so, if the ShowTokens variable has the value 1, nsh should print a list of the tokens. You may use whatever format you wish for this list, and you may include other information about the tokens (such as reserved word or string), but extra information is not required. If the syntax of the line is correct, nsh should take appropriate action.

If the command is do, back, or tovar, nsh should use fork() and exec() to start a process to execute the command given on the command line. You may not use the Unix system() library routine to execute the command line. If the command is do or tovar, then nsh should wait for the command it has just started to complete before issuing a prompt for the next command. (You might want to use waitpid()). On the other hand, if the command is back, then nsh should add this command to its list of background jobs and immediately issue a prompt for a new command.

If the command is tovar, the child nsh that is forked from the parent should close standard output and reopen it to a temporary file (preferably in /tmp/), all before using exec() to start the child process. After the command completes, nsh should read the contents of the temporary file and assign it to the variable specified in the command (see below for a description of how to store variable names and values).

# Variable definition and substitution

When nsh encounters a variable definition, such as set variable "value", it should store the name and definition. Later, when it encounters $variable either as a token or within a string, nsh should replace $variable with its stored definition. It is valid to modify the definition of a variable by a later definition.

# Lex and Yacc

If you know lex and yacc, (or their Gnu implementations, flex and bison), you may certainly use use them to write the scanner and parser.

lex (flex) builds a scanner from a description file, and yacc (bison) builds a parser from a description file. These programs require that you understand regular expressions and context-free grammars. If you have not used these tools before, you are probably better off not using them.

# Testing

You can test nsh by typing commands interactively at its prompt. An easier way to test nsh program is to prepare a file of commands and invoke nsh with standard input redirected from that file. For example, if you have a file named testfile that contains:

        dir directory_1
        do /bin/cat file1 file2 file3
        do ls -lt
        do /bin/wc file1
you can test nsh on these commands by invoking: nsh < testfile. Your program must be able to execute commands fed to it this way, because we will test nsh by using this method.
A (hopefully) working program is available for you to test against:

	wget www.cs.uky.edu/~raphael/courses/CS485/proj4/workingProgram
	chmod +x workingProgram

# Helpful manual pages

You may not use resources on the net except to learn about proper use of the calls in the following list of Unix routines that may be helpful in the assignment: fopen(3), close(2), fread(3), fork(2), execv(3), execve(3), chdir(2), malloc(3), perror(3), exit(2), wait(2), waitpid(2), kill(2), getcwd(3), string(3). You can follow the links above, or you can view these manual pages with the Unix man program. You may use a numeric option to specify the section of the Unix manual (shown in paranthesis above). For example, man fork or man 2 chdir. Section 2 contains operating-system calls; section 3 contains C library utilities. You may call these routines from C or C++ programs.
