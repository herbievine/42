/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 18:06:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef enum e_token_types {
	TOKEN_END,
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

typedef enum e_lexer_states {
	LEXER_STATE_DEFAULT,
	LEXER_STATE_IN_SQ,
	LEXER_STATE_IN_DQ,
}	t_lexer_states;

typedef struct s_token
{
	t_token_types	type;
	char			*value;
	int				length;
}	t_token;

# define TOKEN_FMT "Token(type=%d, value='%.*s')\n"

typedef struct s_subcommand
{
	char	*path;
	char	**args;
}	t_subcommand;

typedef struct s_lexer
{
	const char		*raw;
	t_lexer_states	state;
	int				length;
	int				cursor;
}	t_lexer;

typedef struct s_command
{
	const char	*raw;
	bool		is_valid;
}	t_command;

typedef struct s_shell
{
	char		**env;
	t_command	*current;
}	t_shell;

#endif /* STRUCTS_H */