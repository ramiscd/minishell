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


# Divisão estrutura do projeto


A melhor forma de dividir é seguir o fluxo real do shell:

input → tokenizer → parser → estrutura → executor → processos

Vou separar em tarefas pequenas, com granularidade adequada e dependências claras. As estimativas consideram que vocês já têm experiência.

---

# Fase 1 — Fundação (bloqueia todo o resto)

Definir structs compartilhadas (t_command, t_redir, t_shell) - Parsing - 2pt
Criar arquivo include/minishell.h com structs e interfaces - Parsing - 1pt
Criar estrutura de pastas do projeto (parsing, execution, include, utils) - Parsing - 1pt
Implementar função free_commands para liberar estruturas - Parsing - 2pt

Criar função execute() que recebe t_command * - Execução - 1pt
Criar loop principal do shell (readline → parse → execute) - Execução - 2pt
Implementar controle básico de exit code global - Execução - 1pt

---

# Fase 2 — Tokenizer (Parsing puro)

Implementar detecção e separação de tokens por espaço - Parsing - 2pt
Implementar suporte a aspas simples ' ' - Parsing - 3pt
Implementar suporte a aspas duplas " " - Parsing - 3pt
Implementar identificação de operadores | - Parsing - 2pt
Implementar identificação de operadores > >> < << - Parsing - 3pt
Criar struct t_token e lista encadeada de tokens - Parsing - 2pt
Implementar função tokenize(input) - Parsing - 3pt

---

# Fase 3 — Parser (transformar tokens em comandos)

Implementar criação de t_command a partir de tokens - Parsing - 3pt
Implementar parsing de argv (comando + argumentos) - Parsing - 2pt
Implementar parsing de redirecionamento > - Parsing - 2pt
Implementar parsing de redirecionamento >> - Parsing - 2pt
Implementar parsing de redirecionamento < - Parsing - 2pt
Implementar parsing de heredoc << (estrutura apenas) - Parsing - 3pt
Implementar parsing de pipelines | - Parsing - 3pt
Implementar encadeamento de múltiplos comandos - Parsing - 2pt

Criar função parse() principal - Parsing - 2pt

---

# Fase 4 — Expansão

Implementar expansão de variáveis $VAR - Parsing - 3pt
Implementar expansão de $? - Parsing - 2pt
Implementar não expandir dentro de aspas simples - Parsing - 2pt
Implementar expandir dentro de aspas duplas - Parsing - 2pt

---

# Fase 5 — Validação sintática

Detectar pipe no início ou fim - Parsing - 1pt
Detectar redirecionamento sem destino - Parsing - 1pt
Detectar operadores duplicados inválidos - Parsing - 1pt
Retornar erro de sintaxe corretamente - Parsing - 2pt

---

# Fase 6 — Execução básica

Implementar execução de comando simples com execve - Execução - 3pt
Implementar busca de comando usando PATH - Execução - 3pt
Implementar fork e waitpid - Execução - 2pt
Implementar tratamento de comando não encontrado - Execução - 1pt

---

# Fase 7 — Redirecionamentos

Implementar redirecionamento > - Execução - 3pt
Implementar redirecionamento >> - Execução - 2pt
Implementar redirecionamento < - Execução - 2pt
Implementar heredoc << - Execução - 5pt

---

# Fase 8 — Pipes

Implementar criação de pipe entre dois comandos - Execução - 3pt
Implementar múltiplos pipes - Execução - 5pt
Implementar fechamento correto de file descriptors - Execução - 3pt
Garantir wait correto de todos os processos - Execução - 2pt

---

# Fase 9 — Builtins

Implementar echo - Execução - 2pt
Implementar pwd - Execução - 1pt
Implementar env - Execução - 1pt
Implementar cd - Execução - 3pt
Implementar export - Execução - 5pt
Implementar unset - Execução - 3pt
Implementar exit - Execução - 2pt

Implementar detecção de builtin no executor - Execução - 2pt

---

# Fase 10 — Sinais

Implementar tratamento de Ctrl+C no shell - Execução - 3pt
Implementar comportamento correto em processos filhos - Execução - 3pt
Implementar comportamento de Ctrl+D - Execução - 1pt
Implementar comportamento de Ctrl+\ - Execução - 2pt

---

# Fase 11 — Integração e estabilidade

Integrar parsing e execução completamente - Parsing - 2pt
Corrigir memory leaks principais - Parsing - 3pt
Corrigir vazamentos de file descriptor - Execução - 2pt
Testar cenários complexos (pipes + redirs + vars) - Execução - 3pt

---

# Ordem recomendada de execução

Você começa com:

1 Definir structs
2 tokenizer básico
3 parser básico

Vagner começa com:

1 execute simples
2 fork + execve
3 PATH

Depois ambos evoluem em paralelo.

---

# Caminho crítico mínimo (MVP funcional)

Essas tarefas já produzem um shell funcional:

Parsing:

* structs
* tokenizer básico
* parser argv
* parser pipe

Execução:

* execve
* fork
* pipe

Estimativa total MVP:

Parsing: ~18pt
Execução: ~18pt

Total: ~36pt (~3 semanas com folga)
