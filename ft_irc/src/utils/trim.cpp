/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:58:53 by herbie            #+#    #+#             */
/*   Updated: 2024/07/02 17:08:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

void trim(std::string &s)
{
	s.erase(0, s.find_first_not_of("\t\n\v\f\r "));
	s.erase(s.find_last_not_of("\t\n\v\f\r ") + 1);
}
