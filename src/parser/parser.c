#include "../../headers/parser.h"

t_command	*parse(t_token *tokens)
{
	t_cmd_builder	*b;
	t_command		*head;
	t_command		*last;

	b = init_builder(tokens);
	head = NULL;
	last = NULL;
	while (b->current)
	{
		if (b->current->type == WORD)
			add_arg(b, b->current->cmd);
		else if (b->current->type == PIPE)
		{
			t_command *cmd = build_command(b);
			if (!head)
				head = cmd;
			else
				last->next = cmd;
			last = cmd;

			b = init_builder(b->current->next);
		}
		b->current = b->current->next;
	}
	return (head);
}