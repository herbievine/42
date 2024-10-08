/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:05:23 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:02:52 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string &str, int sep)
{
	std::vector<std::string> tokens;
	std::string tok = "";

	for (size_t i = 0; i < str.length(); i++)
	{
		char c = str[i];

		if (c == sep)
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
