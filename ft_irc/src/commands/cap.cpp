/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 21:00:13 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The CAP command is used to negotiate capabilities between the client and the server.
 *
 * @param client
 * @param args
 *
 * @related https://ircv3.net/specs/extensions/capability-negotiation.html
 */

void cap(Client *client, std::vector<std::string> const &args)
{
	client->sendRaw(":ft_irc.server NOTICE * :***Server doesn't support negotiation capabilities\r\n");
}
