/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:05:13 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 09:32:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

enum class DetectType
{
	Channel,
	Nickname
};

DetectType detect(std::string channelOrNickname);
std::vector<std::string> split(std::string str, int sep = ' ');
void trim(std::string &s);

#endif /* UTILS_HPP */
