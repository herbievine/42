/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:18:58 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 09:28:20 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: please provide a config file" << std::endl;
		return 1;
	}

	return 0;
}
