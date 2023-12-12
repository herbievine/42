/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sed.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:58:34 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 10:23:34 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SED_HPP
#define SED_HPP

#include <iostream>

class Sed
{
public:
	Sed(std::string infile);
	~Sed();
	void replace(std::string pattern, std::string replace);

private:
	std::string infile;
	std::string outfile;
};

#endif /* SED_HPP */