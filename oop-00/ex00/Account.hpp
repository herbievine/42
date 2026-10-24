/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <iostream>

class Account
{
	// Bank is the sole authority on accounts: it creates, credits, debits and
	// deletes them, so money can never reach an account without going through it.
	friend class Bank;

public:
	// Const getters by reference: readable by anyone, modifiable by no one.
	const int &getId() const;
	const int &getValue() const;

private:
	// Assigned once by Bank and never changed, so there is no setter.
	int _id;
	// Changes only through Bank rules (fee, funds checks), so no public setter.
	int _value;

	// Private: only Bank can create or destroy an account, so it controls ids
	// and ownership.
	explicit Account(int id);
	~Account();

	// Private and not implemented: an account must never be duplicated, a copy
	// would duplicate its id.
	Account(const Account &src);
	Account &operator=(const Account &rhs);
};

std::ostream &operator<<(std::ostream &o, const Account &account);

#endif /* ACCOUNT_HPP */
