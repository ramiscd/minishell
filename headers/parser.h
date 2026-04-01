#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_command      *parse(t_token *tokens);
void           print_commands(t_command *cmd);

/* builder */
t_cmd_builder  *init_builder(t_token *tokens);
void           add_arg(t_cmd_builder *b, char *arg);
t_command      *build_command(t_cmd_builder *b); // declarar aqui

#endif