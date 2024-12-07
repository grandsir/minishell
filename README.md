# Minishell

**Minishell** is a simple shell implementation in C, designed to simulate the basic functionality of a Unix shell. It aims to handle user input, execute commands, manage processes, and perform basic built-in operations like `cd`, `echo`, and `exit`. This project is a great way to understand how shells work and how system calls are used in C.

---

## Features

- **Command Parsing:** Accepts and parses user input into commands and arguments.
- **Process Management:** Uses `fork()` and `exec()` to launch external programs.
- **Built-in Commands:** Supports basic shell built-ins like `cd`, `echo`, `exit`.
- **Environment Variables:** Supports the use of environment variables (e.g., `$HOME`, `$PATH`).
- **Redirection:** Handles input/output redirection with `<` and `>`.
- **Pipes:** Supports piping commands using `|`.
- **Command History:** Keeps track of recently executed commands.
