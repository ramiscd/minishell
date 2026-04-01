#include "../../headers/structs.h"
#include "../../headers/lexer.h"
#include <stdlib.h>
#include <string.h>

t_redir *create_redir(t_token *token)
{
    t_redir *r = malloc(sizeof(t_redir));
    if (!r)
        return NULL;

    r->file = strdup(token->cmd);

    if (token->type == TOKEN_REDIR_IN)
        r->type = REDIR_IN;
    else if (token->type == TOKEN_REDIR_OUT)
        r->type = REDIR_OUT;
    else if (token->type == TOKEN_HEREDOC)
        r->type = HEREDOC;
    else if (token->type == TOKEN_APPEND)
        r->type = APPEND;

    r->next = NULL;
    return r;
}

void add_redir(t_command *cmd, t_redir *redir)
{
    t_redir *tmp;

    if (!cmd->redirs)
        cmd->redirs = redir;
    else
    {
        tmp = cmd->redirs;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = redir;
    }
}