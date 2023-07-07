/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:38:24 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 15:38:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"
#include "str.h"
#include "structs.h"
#include <unistd.h>

void	ft_error(char *message)
{
	ft_dprintf(STDERR_FILENO, "%s\n", message);
}

void	ft_invalid_token(char *command, t_lexer lexer, t_token token)
{
	int	i;
	int	prompt_length;

	prompt_length = ft_strlen("minishell> ");
	while (prompt_length--)
		ft_dprintf(STDERR_FILENO, " ");
	i = -1;
	while (++i < lexer.cursor - 1)
		ft_dprintf(STDERR_FILENO, " ");
	i = -1;
	while (++i < token.length)
		ft_dprintf(STDERR_FILENO, "^");
	ft_dprintf(STDERR_FILENO, " invalid token\n");
}
