/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/11/10 10:00:19 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <sys/types.h>

extern int	g_signal;

typedef enum e_token_types
{
	TOKEN_EOF,
	TOKEN_INVALID,
	TOKEN_SYMBOL,
	TOKEN_GT,
	TOKEN_LT,
	TOKEN_GT_GT,
	TOKEN_LT_LT,
	TOKEN_PIPE,
	TOKEN_SQ,
	TOKEN_DQ,
	TOKEN_IN_FILE,
	TOKEN_OUT_FILE,
	TOKEN_CMD,
}	t_token_types;

typedef enum e_lexer_states
{
	LEXER_STATE_DEFAULT,
	LEXER_STATE_IN_SQ,
	LEXER_STATE_IN_DQ,
}	t_lexer_states;

typedef struct s_token
{
	t_token_types	type;
	const char		*value;
	int				length;
	struct s_token	*next;
}	t_token;

// # define TOKEN_FMT "Token(type=%d, value='%.*s')\n"
// # define TOKEN_ARG(token) token.type, token.length, token.value

typedef struct s_bash_token_map
{
	char			*value;
	t_token_types	type;
}	t_bash_token_map;

typedef struct s_lexer
{
	const char		*raw;
	t_lexer_states	state;
	int				length;
	int				cursor;
}	t_lexer;

typedef enum e_mode
{
	MODE_WRITE,
	MODE_APPEND
}	t_mode;

typedef struct s_subcommand
{
	int					in_fd;
	int					out_fd;
	int					builtin;
	char				*path;
	char				**args;
	char				**envp;
	char				**cpy_envp;
	char				*out_file_name;
	t_mode				mode;
	bool				is_executable;
	bool				is_heredoc;
	struct s_subcommand	*next;
}	t_subcommand;

typedef struct s_command
{
	t_token			*tokens;
	int				token_length;
	t_subcommand	*subcommands;
	int				subcommand_length;
}	t_command;

// # define SUBCOMMAND_FMT
// 	"Subcommand(in_fd=%d, out_fd=%d, path='%s',
// 	mode=%d, is_heredoc=%d)\n"
// # define SUBCOMMAND_ARG(subcommand)
// 	subcommand.in_fd, subcommand.out_fd, subcommand.path,
// 	subcommand.mode, subcommand.is_heredoc
typedef struct s_shell
{
	char	**env;
}	t_shell;

// Constants

# define PIPE_ERROR -1

# define PID_CHILD 0
# define PID_ERROR -1

#endif /* STRUCTS_H */