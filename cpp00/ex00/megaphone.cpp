/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:58:21 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 10:52:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

void str_toupper(std::string &str)
{
	int i;

	for (i = 0; str[i]; i++)
		str[i] = toupper(str[i]);
}

int main(int argc, char **argv)
{
	int i;

	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (i = 1; i < argc; i++)
	{
		std::string str(argv[i]);
		str_toupper(str);
		std::cout << str;
	}
	std::cout << std::endl;
	return (0);
}
