/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:34 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:10:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"
#include <fstream>

Sed::Sed(std::string const &infile) : infile(infile), outfile(infile + ".replace")
{
}

Sed::~Sed()
{
}

void Sed::replace(std::string const &pattern, std::string const &replace)
{
	std::ifstream ifs(this->infile);
	
	if (!ifs.is_open())
	{
		std::cerr << "error: " << this->infile << " could not be opened." << std::endl;
		return;
	}

	std::ofstream ofs(this->outfile);
	
	if (!ofs.is_open())
	{
		std::cerr << "error: " << this->outfile << " could not be opened." << std::endl;
		ifs.close();
		return;
	}
	
	std::string line;
	
	while (std::getline(ifs, line))
	{
		size_t pos = line.find(pattern);
		while (pos != std::string::npos)
		{
			line.erase(pos, pattern.length());
			line.insert(pos, replace);
			pos = line.find(pattern, pos + replace.length());
		}
		ofs << line << std::endl;
	}
	
	ifs.close();
	ofs.close();
}
