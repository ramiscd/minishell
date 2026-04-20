*This project was created as part of the curriculum at 42 by rdamasce, vade-mel.*

## Description

Minishell is a simplified Unix shell implemented in C, inspired by Bash. The project recreates the core behavior of an interactive shell: reading user input, parsing it into commands, and executing those commands — including support for pipelines, redirections, environment variable expansion, and built-in commands.

The implementation is split between two modules with a clean internal contract:

- **Parsing** (rdamasce): tokenizer, quote handling, `$VAR`/`$?` expansion, pipeline and redirection parsing, command builder.
- **Execution** (vade-mel): process forking, PATH resolution, pipeline plumbing via `pipe()`/`dup2()`, redirections (`<`, `>`, `>>`), and all built-in commands (`echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`).

Both modules share a common set of structs defined in `headers/structs.h`, which acts as the interface contract between parsing and execution.

## Instructions

### Requirements

- GCC or Clang with `-Wall -Wextra -Werror`
- GNU Readline (`libreadline-dev` on Debian/Ubuntu)

```bash
sudo apt-get install libreadline-dev
```

### Compilation

```bash
make
```

This builds `libft` and then the `minishell` binary at the project root.

```bash
make re      # full rebuild
make clean   # remove object files
make fclean  # remove objects and binary
```

### Running

```bash
./minishell
```

The shell displays a `minishell$ ` prompt. Type commands and press Enter. Exit with `exit` or Ctrl+D.

### Supported features

| Feature | Examples |
|---|---|
| Absolute and relative paths | `/bin/ls`, `./script.sh` |
| PATH-based lookup | `ls`, `grep`, `wc` |
| Pipelines | `ls \| grep .c \| wc -l` |
| Input/output redirections | `cat < file`, `ls > out`, `echo hi >> log` |
| Single quotes (no expansion) | `echo '$USER'` → `$USER` |
| Double quotes (expansion) | `echo "$USER"` → `rdamasce` |
| Variable expansion | `echo $HOME`, `echo $?` |
| Built-ins | `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit` |

### Running the test suite

```bash
bash tests/regua_test.sh
```

The suite covers all mandatory items from the 42 evaluation rubric and reports PASS / FAIL / SKIP for each case.

## Resources

The following references were used during development, organized by area:

### Shell behavior and POSIX specification

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative reference for quoting rules, parameter expansion, redirections, and pipeline semantics. Used throughout parsing and execution design.
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal specification for shell grammar and operator precedence. Used to validate edge cases in the parser.

### Readline

- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for `readline()`, `add_history()`, and `rl_outstream`. Used to implement the interactive prompt and command history.

### System calls

- `man 2 execve`, `man 2 fork`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid` — primary references for the execution layer and pipeline plumbing.
- `man 2 open`, `man 2 close` — used for redirection implementation.
- `man 3 getcwd`, `man 2 chdir` — used for the `cd` and `pwd` built-ins.

### Memory and debugging

- [Valgrind](https://valgrind.org/docs/manual/QuickStart.html) — used to check for memory leaks and invalid free operations during development.
