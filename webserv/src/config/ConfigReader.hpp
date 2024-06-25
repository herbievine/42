/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 10:44:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>

class ConfigReader
{
public:
	explicit ConfigReader();
	ConfigReader(const ConfigReader &src);
	~ConfigReader();

	ConfigReader &operator=(const ConfigReader &rhs);

	std::vector<std::string> read(std::string path) const;
};
