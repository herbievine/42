/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 09:24:20 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

class Config
{
public:
	explicit Config(std::string path);
	Config(const Config &src);
	~Config();

	Config &operator=(const Config &rhs);

private:
	std::string _path;
};
