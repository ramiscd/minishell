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

    if (tokens && tokens->type == PIPE)
    {
        printf("Syntax error near pipe\n");
        return NULL;
    }

    while (b->current)
    {
        if (b->current->type == WORD)
        {
            add_arg(b, b->current->cmd);
            b->current = b->current->next;
        }

        else if (b->current->type == TOKEN_REDIR_IN ||
                 b->current->type == TOKEN_REDIR_OUT ||
                 b->current->type == TOKEN_HEREDOC ||
                 b->current->type == TOKEN_APPEND)
        {
            if (!b->current->next || b->current->next->type != WORD)
            {
                printf("Syntax error near redirection\n");
                return NULL;
            }

            t_redir *r = create_redir(b->current, b->current->next);

            if (!b->redirs)
                b->redirs = r;
            else
            {
                t_redir *tmp = b->redirs;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = r;
            }

            b->current = b->current->next->next;
            continue;
        }

        else if (b->current->type == PIPE)
        {
            if (b->argc == 0 && b->redirs == NULL)
            {
                printf("Syntax error near pipe\n");
                return NULL;
            }

            t_command *cmd = build_command(b);

            if (!head)
                head = cmd;
            else
                last->next = cmd;

            last = cmd;

            if (!b->current->next)
            {
                printf("Syntax error near pipe\n");
                return NULL;
            }

            b = init_builder(b->current->next);
            continue;
        }

        else
        {
            b->current = b->current->next;
        }
    }

    if (b && (b->argc > 0 || b->redirs != NULL))
    {
        t_command *cmd = build_command(b);

        if (!head)
            head = cmd;
        else
            last->next = cmd;
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

        t_redir *r = cmd->redirs;
        while (r)
        {
            if (r->type == REDIR_IN)
                printf("  redir: < %s\n", r->file);
            else if (r->type == REDIR_OUT)
                printf("  redir: > %s\n", r->file);
            else if (r->type == APPEND)
                printf("  redir: >> %s\n", r->file);
            else if (r->type == HEREDOC)
                printf("  redir: << %s\n", r->file);

            r = r->next;
        }

        cmd = cmd->next;
    }
}
