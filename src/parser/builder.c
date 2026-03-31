#include "../../headers/parser.h"
#include <stdlib.h>

t_command	*build_command(t_cmd_builder *b)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = b->args;
	cmd->redirs = b->redirs;
	cmd->next = NULL;
	return (cmd);
}