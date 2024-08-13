/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:05:23 by herbie            #+#    #+#             */
/*   Updated: 2024/07/02 17:02:14 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>
#include <vector>

std::vector<std::string> split(std::string str)
{
	std::vector<std::string> tokens;
	std::string tok = "";
	char c = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		c = str[i];

		if (c == ' ')
		{
			trim(tok);
			tokens.push_back(tok);
			tok = "";
		}
		else
			tok += c;
	}

	if (tok.length() > 0)
	{
		trim(tok);
		tokens.push_back(tok);
	}

	return tokens;
}