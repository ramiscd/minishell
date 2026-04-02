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
        // WORD → argumento
        if (b->current->type == WORD)
        {
            add_arg(b, b->current->cmd);
            b->current = b->current->next;
        }

        // REDIRECIONAMENTO → consome 2 tokens (op + file)
        else if (b->current->type == TOKEN_REDIR_IN ||
                 b->current->type == TOKEN_REDIR_OUT ||
                 b->current->type == TOKEN_HEREDOC ||
                 b->current->type == TOKEN_APPEND)
        {
            if (b->current->next)
            {
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

                // consome operador + arquivo
                b->current = b->current->next; // vai pro FILE
                if (b->current)
                    b->current = b->current->next;

                continue; // 🔥 não deixa o loop avançar de novo
            }
            else
            {
                // erro de sintaxe simples (opcional tratar melhor depois)
                break;
            }
        }

        // PIPE → fecha comando atual
        else if (b->current->type == PIPE)
        {
            t_command *cmd = build_command(b);

            if (!head)
                head = cmd;
            else
                last->next = cmd;

            last = cmd;

            // novo builder começa após o pipe
            b = init_builder(b->current->next);
            continue; // 🔥 evita avanço duplicado
        }

        // fallback de segurança
        else
        {
            b->current = b->current->next;
        }
    }

    // último comando (fim da linha)
    if (b && (b->argc > 0 || b->redirs != NULL))
    {
        t_command *cmd = build_command(b);

        if (!head)
            head = cmd;
        else if (last)
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
		cmd = cmd->next;
	}
}

/*
** ===================== MINISHELL - STATUS ATUAL =====================
**
** Responsável: Lexing e Parsing
**
** --------------------------------------------------------------------
** ETAPA ATUAL
**
** Parser parcialmente funcional:
**
** - Lexer já gera tokens corretamente (WORD, PIPE, REDIR, etc)
** - Parser já:
**   ✔ separa comandos por PIPE
**   ✔ monta argv básico
**   ✔ reconhece redirecionamentos (>, <, >>, <<)
**
** Problema atual:
**
** - Redirecionamentos ainda estão sendo interpretados como argumentos
**   em alguns casos
**
** Exemplo do bug atual:
**
**   input:
**     echo hello > out.txt | wc -l < in.txt
**
**   output atual:
**     Command: echo hello
**     Command: out.txt              ❌ errado
**     Command: wc -l < in.txt       ❌ errado
**
** Problemas identificados:
**
** 1. Tokens de redirecionamento não estão sendo consumidos corretamente
**    (REDIR + FILE devem ser tratados juntos)
**
** 2. Fluxo do parser (b->current) ainda está avançando incorretamente
**    em alguns cenários
**
** 3. build_command ainda não está integrando corretamente:
**    - argv
**    - redirs (estrutura t_redir)
**
**
** --------------------------------------------------------------------
** PRÓXIMAS ETAPAS (para finalizar parsing)
**
** 1. Corrigir consumo de redirecionamentos:
**    - Garantir que REDIR + FILE nunca entrem no argv
**    - Garantir avanço correto do ponteiro (b->current)
**
** 2. Integrar redirs no build_command:
**    - Copiar b->redirs → t_command->redirs
**
** 3. Ajustar print_commands:
**    - Exibir redirecionamentos corretamente
**
** 4. Garantir criação correta de comandos:
**    - Não criar comandos vazios
**    - Não perder comandos após PIPE
**
**
** --------------------------------------------------------------------
** PENDÊNCIAS IMPORTANTES
**
** Edge cases:
** - múltiplos redirecionamentos:
**     echo hi > a > b
**
** - redirecionamento sem arquivo:
**     echo hi >
**
** - pipes inválidos:
**     | ls
**     ls |
**
** - combinação complexa:
**     cat < in.txt | grep x > out.txt
**
**
** Norminette:
** - funções <= 25 linhas
** - dividir parse em helpers (handle_word, handle_redir, handle_pipe)
**
**
** Memory (Leaks):
** - liberar:
**   - tokens
**   - argv
**   - redirs
**   - commands
**
** - evitar leaks no builder (init_builder / rebuild)
**
**
** --------------------------------------------------------------------
** ESTADO GERAL
**
** ✔ Lexer praticamente pronto
** ⚠ Parser funcional mas inconsistente
** ⏳ Falta consolidar redirecionamentos + estrutura final
**
** Depois disso:
** → pronto para integração com executor
**
** ====================================================================
*/