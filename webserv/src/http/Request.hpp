/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 09:30:23 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

class Request
{
public:
	explicit Request();
	Request(const Request &src);
	~Request();

	Request &operator=(const Request &rhs);

private:
};
