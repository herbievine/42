/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:05:23 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 09:32:54 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <iostream>
#include <vector>

DetectType detect(std::string channelOrNickname)
{
	if (channelOrNickname[0] == '#')
		return DetectType::Channel;
	return DetectType::Nickname;
}
