/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

Account::Account(int id) : _id(id), _value(0)
{
}

Account::~Account()
{
}

const int &Account::getId() const
{
	return this->_id;
}

const int &Account::getValue() const
{
	return this->_value;
}

std::ostream &operator<<(std::ostream &o, const Account &account)
{
	o << "[" << account.getId() << "] - [" << account.getValue() << "]";
	return o;
}
