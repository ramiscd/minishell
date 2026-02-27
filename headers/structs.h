#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>

/**
 * @struct s_token
 * @brief Represents a lexical token in the shell.
 *
 * This struct is a node of a doubly linked list created during lexical analysis.
 * Each node represents a single element of the user input, such as a command,
 * argument, pipe, or redirection operator.
 *
 * The linked list preserves the original order of the command and allows
 * traversal in both directions, which simplifies parsing and execution.
 *
 * Fields:
 * - cmd  : string value of the token (command, argument, or operator)
 * - type : token type identifier (word, pipe, redirect, etc.)
 * - next : pointer to the next token in the list
 * - prev : pointer to the previous token in the list
 */
typedef struct s_token
{
	char			*cmd;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


/**
 * @struct s_mini
 * @brief Stores the global state of the minishell.
 *
 * This struct acts as the main context container for the shell. It holds the
 * current user input, prompt, environment variables, and the list of tokens
 * generated from parsing the input. It also contains flags used to control
 * shell behavior, such as error state and exit condition.
 *
 * Fields:
 * - input  : raw command line entered by the user
 * - prompt : shell prompt string displayed to the user
 * - envp   : NULL-terminated array of environment variables
 * - token  : pointer to the head of the token linked list
 * - error  : flag indicating whether an error occurred
 * - exit   : flag indicating whether the shell should terminate
 */
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**envp;
	t_token	*token;
	char	error;
	char	exit;
}	t_mini;


/**
 * @struct s_expand
 * @brief Holds temporary state during environment variable expansion.
 *
 * This struct is used while parsing and expanding variables such as $HOME or
 * $PATH inside command strings. It stores indexes, flags, and temporary buffers
 * required to correctly extract and replace environment variables, while also
 * handling quote rules.
 *
 * Fields:
 * - hold_str : temporary storage used to build expanded strings
 * - ex       : expansion state flag
 * - start    : start index of the variable in the string
 * - end      : end index of the variable in the string
 * - quotes   : quote state indicator
 * - ex_n     : expansion counter or helper value
 * - i        : general-purpose index used during parsing
 */
typedef struct s_expand
{
	char	**hold_str;
	int		ex;
	int		start;
	int		end;
	int		quotes;
	int		ex_n;
	int		i;
}	t_expand;


/**
 * @struct s_executor
 * @brief Stores execution context for running commands and pipelines.
 *
 * This struct is responsible for managing process execution, including command
 * arguments, pipe file descriptors, process IDs, and execution status. It is
 * used during the execution phase to coordinate fork(), pipe(), and execve()
 * calls when running one or multiple commands connected by pipes.
 *
 * Fields:
 * - temp  : pointer used to traverse the token list during execution
 * - cmd   : NULL-terminated array of command arguments for execve()
 * - fd    : array of pipe file descriptors
 * - status: exit status of the last executed process
 * - pid   : array of process IDs created with fork()
 * - n_pros: number of processes to execute
 */
typedef struct s_executor
{
	t_token	*temp;
	char	**cmd;
	int		**fd;
	int		status;
	pid_t	*pid;
	int		n_pros;
}	t_executor;

#endif