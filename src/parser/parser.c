#include "../../headers/parser.h"
#include "../../headers/structs.h"
#include "../../headers/lexer.h"
#include <stdio.h>
#include <stdlib.h>

t_command *build_command(t_cmd_builder *b);

t_command *parse(t_token *tokens)
{
    t_cmd_builder *b = init_builder(tokens);
    t_command *head = NULL;
    t_command *last = NULL;

    while (b->current)
    {
        if (b->current->type == WORD)
            add_arg(b, b->current->cmd);
        else if (b->current->type == PIPE)
        {
            t_command *cmd = build_command(b); // <- aqui só chama
            if (!head)
                head = cmd;
            else
                last->next = cmd;
            last = cmd;

            b = init_builder(b->current->next);
        }
        b->current = b->current->next;
    }
    return head;
}

void print_commands(t_command *cmd)
{
    while (cmd)
    {
        printf("Command:\n");
        for (int i = 0; cmd->argv && cmd->argv[i]; i++)
            printf("  argv[%d]: %s\n", i, cmd->argv[i]);
        cmd = cmd->next;
    }
}