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

typedef enum e_token {
	TOKEN_WHITESPACE,
	TOKEN_GREATER,
	TOKEN_LESSER,
	TOKEN_GREATER_GREATER,
	TOKEN_LESSER_LESSER,
	TOKEN_PIPE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_LITERAL
}	t_token;

typedef union u_token_value {
	char	*value;
	t_token	token;
}	t_token_value;

typedef struct s_subcommand
{
	char	*path;
	char	**args;
}	t_subcommand;

typedef struct s_list
{
	int				value;
	struct s_list	*next;
}	t_list;

typedef struct s_command
{
	const char	*raw;
	// int				in_fd;
	// int				out_fd;
	// char			*out_file;
	// bool			is_pipe;
	// bool			is_heredoc;
	bool				is_valid;
	// bool			is_complete;
	t_list				*lexer;
	// t_subcommand	*subcommands;
	// int				subcommands_count;	
}	t_command;

typedef struct s_shell
{
	char		**env;
	t_command	*current;
}	t_shell;

#endif /* STRUCTS_H */