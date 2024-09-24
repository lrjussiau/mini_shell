
# Minishell - A Simple Shell Implementation

## Description

*Minishell* is a project from 42 school where you are tasked with creating a simple shell similar to Bash. The goal is to create a command-line interpreter that supports various shell features, including executing commands, handling pipes, redirections, and managing environment variables. The project focuses on learning system calls and process management in Unix-based systems.

## Project Objectives

- Implement a basic shell with support for built-in commands.
- Manage processes, pipes, and file redirections.
- Handle signals, environment variables, and command execution.
- Enhance knowledge of system calls such as `fork()`, `execve()`, `pipe()`, and `dup2()`.

## Features

1. **Command Execution**
   - Executes basic shell commands like `ls`, `echo`, `pwd`, etc.
   - Handles the `PATH` environment variable to find executables.

2. **Built-in Commands**
   - `cd`: Change the current directory.
   - `echo`: Display a line of text.
   - `env`: Print the environment variables.
   - `export`: Set or modify environment variables.
   - `unset`: Unset an environment variable.
   - `exit`: Exit the shell.

3. **Pipes and Redirections**
   - Supports piping between commands (`|`).
   - Supports input redirection (`<`) and output redirection (`>` and `>>`).

4. **Environment Variables**
   - Manage environment variables using `export`, `env`, and `unset`.

5. **Signals**
   - Handle signals such as `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` gracefully.

## System Calls and Functions

Key system calls used in the project include:

- `fork()`: Create a new process.
- `execve()`: Execute a command by replacing the current process image.
- `pipe()`: Create a communication channel between processes.
- `dup2()`: Duplicate file descriptors for redirections.
- `wait()`: Wait for child processes to terminate.
- `signal()`: Handle signals for keyboard interruptions.

## Installation

To compile and run the *Minishell* project, follow these steps:

```bash
git clone https://github.com/your-repo/minishell.git
cd minishell
make
```

Run the shell with the following command:

```bash
./minishell
```

## Usage

Once launched, *Minishell* acts as a basic Unix shell where you can execute commands, pipe outputs, and use built-in commands like `cd`, `exit`, and more. Example:

```bash
echo "Hello, World!" | grep "Hello"
```

## Error Handling

The shell must handle:

- Invalid commands or missing executables.
- Syntax errors in pipes or redirections.
- Handling signals to prevent shell crashes.
- Correctly managing environment variables and built-in commands.

## Testing

Test the shell with different commands and built-in functions to ensure it behaves like a real shell.

```bash
ls -l | grep minishell > output.txt
cat output.txt
```

Check that the output matches expected behavior and that piping and redirections work correctly.

## Author

- **Louis** - 42 Lausanne Student
