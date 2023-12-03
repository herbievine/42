/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/11/27 10:21:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <sys/types.h>

# ifndef __MACH__
#  define __MACH__ 0
# endif /* __MACH__ */

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
}	t_token_types;

typedef enum e_quote_state
{
	STATE_DEFAULT,
	STATE_IN_SQ,
	STATE_IN_DQ,
}	t_quote_state;

typedef struct s_token
{
	t_token_types	type;
	const char		*value;
	int				length;
	bool			is_malloced;
	struct s_token	*next;
}	t_token;

typedef struct s_bash_token_map
{
	char			*value;
	t_token_types	type;
}	t_bash_token_map;

typedef struct s_lexer
{
	const char		*raw;
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
	char			***env;
}	t_command;

typedef struct s_shell
{
	char	**env;
}	t_shell;

# define PIPE_ERROR -1

# define PID_CHILD 0
# define PID_ERROR -1

#endif /* STRUCTS_H */