/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 13:25:21 by herbie           ###   ########.fr       */
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

void cap(Client *client, std::vector<std::string> const &args)
{
	client->sendRaw(":ft_irc.server NOTICE * :*** Server doesn't support negotiation capabilities\r\n");
}
