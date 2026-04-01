#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

t_token	*lexer(char *input);
t_token	*token_create(char *cmd, int type);
void	add_token_back(t_token **head, t_token *new);
char	*extract_word(char *input, int *i);

#endif