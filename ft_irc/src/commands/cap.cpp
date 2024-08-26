/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 13:43:14 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The CAP command is used to negotiate capabilities between the client
 * and the server.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#cap-message
 */

void cap(const Client *client, std::vector<std::string> const &args)
{
	client->write(":ft_irc.server NOTICE * :*** Server doesn't support negotiation capabilities\r\n");
}
