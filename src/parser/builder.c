#include "../../headers/parser.h"
#include <stdlib.h>
#include <string.h>

t_cmd_builder *init_builder(t_token *tokens)
{
    t_cmd_builder *b = malloc(sizeof(t_cmd_builder));
    if (!b) return NULL;

    b->tokens = tokens;
    b->current = tokens;
    b->argc = 0;
    b->argv = NULL;
    b->redirs = NULL;   // 🔥 FALTAVA ISSO

    return b;
}

void add_arg(t_cmd_builder *b, char *arg)
{
    // Se ainda não existe argv, aloca espaço inicial
    if (!b->argv)
        b->argv = malloc(sizeof(char *) * 2); // 1 argumento + NULL
    else
        b->argv = realloc(b->argv, sizeof(char *) * (b->argc + 2));

    b->argv[b->argc] = arg;  // adiciona o argumento
    b->argc++;               // incrementa count
    b->argv[b->argc] = NULL; // termina com NULL
}

t_command *build_command(t_cmd_builder *b)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;

    cmd->argv = b->argv;
    cmd->redirs = b->redirs;
    cmd->next = NULL;

    // reset builder
    b->argc = 0;
    b->argv = NULL;
    b->redirs = NULL;

    return cmd;
}