# minishell
Implementação de um shell simplificado em C, inspirado no bash, capaz de interpretar e executar comandos, incluindo parsing, execução de processos, redirecionamentos, pipes e built-ins. O projeto segue os requisitos da 42 e foca em arquitetura modular, separando parsing e execução para maior clareza e manutenção.

Sim. O mínimo necessário para duas pessoas trabalharem em paralelo no minishell é definir o “contrato” entre parsing e execução. Isso consiste principalmente nas structs e nas interfaces.

Pense nisso como uma API interna. O parsing produz dados. A execução consome esses dados. Ambos precisam concordar exatamente no formato.

**1. Struct principal do comando**

Essa struct é o coração da integração:

```c
typedef enum e_redir_type
{
    REDIR_IN,      // <
    REDIR_OUT,     // >
    REDIR_APPEND,  // >>
    REDIR_HEREDOC  // <<
} t_redir_type;

typedef struct s_redir
{
    t_redir_type type;
    char *file;
    struct s_redir *next;
} t_redir;

typedef struct s_command
{
    char **argv;            // ["ls", "-la", NULL]
    t_redir *redirs;        // lista de redirecionamentos
    struct s_command *next; // próximo comando no pipeline
} t_command;
```

Exemplo para:

```
cat file.txt | grep hello > out.txt
```

Fica:

```
[cat file.txt] -> [grep hello > out.txt]
```

---

**2. Definir responsabilidade de cada lado**

Parsing (Pessoa A):

Entrada:

```
char *input;
```

Saída:

```
t_command *parse(char *input);
```

Execução (Pessoa B):

Entrada:

```
t_command *cmd;
```

Execução:

```
void execute(t_command *cmd);
```

Esse é o contrato principal.

---

**3. Struct de contexto global (muito recomendado)**

```c
typedef struct s_shell
{
    char **envp;
    int last_exit_code;
} t_shell;
```

Ambos os módulos usarão isso.

---

**4. Arquivos mínimos para começar**

Parsing:

```
parsing/
  tokenizer.c
  parser.c
  parser_utils.c
  parsing.h
```

Execução:

```
execution/
  execute.c
  exec_utils.c
  redirections.c
  pipes.c
  execution.h
```

Shared:

```
include/
  minishell.h
```

---

**5. minishell.h (arquivo mais importante no início)**

Ele define o contrato entre os dois:

```c
typedef struct s_command t_command;

t_command *parse(char *input);
void execute(t_command *cmd);
void free_commands(t_command *cmd);
```

---

**6. Ordem prática recomendada (passo a passo)**

Passo 1
Criar as structs

Passo 2
Criar um parser fake que retorna algo fixo

Passo 3
Criar executor que executa esse algo fixo com execve

Passo 4
Depois evoluir parsing e execução independentemente