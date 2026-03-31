typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_cmd_builder
{
	t_token		*current;
	char		**args;
	int			arg_count;
	t_redir		*redirs;
}	t_cmd_builder;