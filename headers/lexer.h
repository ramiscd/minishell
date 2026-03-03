#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
} t_token_type;

t_token *lexer(char *input);

#endif

/* input = "ls -la | grep .c > out.txt"

Output: 
[WORD: "ls"]
[WORD: "-la"]
[PIPE: "|"]
[WORD: "grep"]
[WORD: ".c"]
[REDIR_OUT: ">"]
[WORD: "out.txt"] */