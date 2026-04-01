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
    return b;
}

void add_arg(t_cmd_builder *b, char *arg)
{
    // exemplo mínimo
    b->argc++;
    b->argv = realloc(b->argv, sizeof(char *) * (b->argc + 1));
    b->argv[b->argc - 1] = arg;
    b->argv[b->argc] = NULL;
}

t_command *build_command(t_cmd_builder *b)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL;
    cmd->argv = b->argv;
    cmd->redirs = NULL;
    cmd->next = NULL;

    // reset do builder para próximo comando
    b->argc = 0;
    b->argv = NULL;

    return cmd;
}