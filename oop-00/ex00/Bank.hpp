/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <map>
#include "Account.hpp"

// Bank owns its accounts and is the only entry point to move money anywhere.
// Every operation returns false (and changes nothing) when it is not legal,
// so the program never crashes on bad input.
class Bank
{
public:
	explicit Bank(int liquidity);
	~Bank();

	// Returns the new account id, or -1 if the account could not be created.
	int createAccount();
	bool deleteAccount(int id);

	// The only ways money enters or leaves an account.
	bool deposit(int id, int amount);
	bool withdraw(int id, int amount);
	bool giveLoan(int id, int amount);

	// Const getters by reference, no setters: liquidity only moves through the
	// rules above. getAccount returns a pointer (not a copy) so an unknown id
	// can be reported as NULL instead of crashing.
	const int &getLiquidity() const;
	const Account *getAccount(int id) const;
	const std::map<int, Account *> &getAccounts() const;

private:
	int _liquidity;
	// Only ever increases, so two accounts can never share an id.
	int _nextId;
	// Keyed by id: direct lookup, and keys are unique by construction.
	std::map<int, Account *> _accounts;

	Account *_find(int id) const;

	// Private and not implemented: Bank owns raw pointers, a copy would
	// double-free them.
	Bank(const Bank &src);
	Bank &operator=(const Bank &rhs);
};

std::ostream &operator<<(std::ostream &o, const Bank &bank);

#endif /* BANK_HPP */
