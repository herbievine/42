/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 16:12:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "usage: ./sed <filename> <pattern> <replace>." << std::endl;
		return 1;
	}

	Sed sed(argv[1]);
	sed.replace(argv[2], argv[3]);

	return 0;
}
