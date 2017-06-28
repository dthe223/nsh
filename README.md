# nsh (New Shell)
unix shell developed in C++

# Syntax

- nsh is somewhat similar to existing shells such as csh, bash, ksh, and tcsh. However, it lacks many of the features of those shells. It also has a different command syntax and a different command set.
- nsh takes commands from standard input and directs all its output to standard output.
- Like other shells, nsh accepts both built-in commands and program-control commands.
- Commands are constructed out of tokens. A token can be either a single word or a string surrounded by double-quotes. Tokens are subject to variable substitution, as described below. There can be any amount of empty space before and after tokens.
- The % symbol introduces a comment, which continues to the end of the line. You may assume that % never appears within a token. nsh ignores all characters in a comment. If a line is empty (except perhaps for spaces) except for a comment, it is a valid command that has no effect

# Built-in Commands

- `set variable value`  
   Here, variable is any reasonable variable name (starting with a letter, continuing with letters or numbers), and value is a token. It is conventional for users to represent variables in ALL CAPITALS, but nsh does not enforce this convention. Variable names are case-sensitive.
- `prompt newPrompt`  
   Set the shell prompt to "newPrompt", which is a token. Do not add or subtract spaces at the end of the new prompt. The initial prompt in nsh is "nsh > " (There is a space after the >).  
   Ex: So `prompt Purple` would change "nsh > "  -->  "Purple> "
- `dir directoryName`  
   This command changes the current directory to directoryName. The dir command must have a single parameter. The directoryName may be either absolute (starting with /) or relative (not starting with /).
- `procs`  
   nsh lists all processes running in the background. nsh keeps a list and does not rely on external programs to create its output.
- `done`  
   nsh exits with exit status 0. Also accepts <control-D> (end-of-file) on the input stream and treats it as if the user had typed "done".
