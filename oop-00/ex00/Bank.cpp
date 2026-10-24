/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bank.hpp"
#include <climits>
#include <new>

Bank::Bank(int liquidity) : _liquidity(liquidity < 0 ? 0 : liquidity), _nextId(0)
{
}

Bank::~Bank()
{
	for (std::map<int, Account *>::iterator it = this->_accounts.begin(); it != this->_accounts.end(); ++it)
		delete it->second;
}

Account *Bank::_find(int id) const
{
	std::map<int, Account *>::const_iterator it = this->_accounts.find(id);

	if (it == this->_accounts.end())
		return NULL;

	return it->second;
}

/**
 * @brief Creates a new account with a fresh id. Ids are never reused, so two
 * accounts can never share one. Returns -1 instead of crashing if the bank
 * runs out of ids or memory.
 *
 * @return the new account id, or -1
 */
int Bank::createAccount()
{
	if (this->_nextId == INT_MAX)
		return -1;

	Account *account = NULL;

	try
	{
		account = new Account(this->_nextId);
		this->_accounts.insert(std::make_pair(this->_nextId, account));
	}
	catch (const std::bad_alloc &e)
	{
		delete account;
		return -1;
	}

	return this->_nextId++;
}

bool Bank::deleteAccount(int id)
{
	Account *account = this->_find(id);

	if (account == NULL)
		return false;

	delete account;
	this->_accounts.erase(id);

	return true;
}

/**
 * @brief Adds money to a client account. The bank keeps 5% of every inflow
 * (rounded down), the client gets the rest. amount / 20 is used instead of
 * amount * 5 / 100 so the computation cannot overflow.
 *
 * @param id
 * @param amount
 * @return true if the deposit was accepted
 */
bool Bank::deposit(int id, int amount)
{
	Account *account = this->_find(id);

	if (account == NULL || amount <= 0)
		return false;

	int fee = amount / 20;
	int credit = amount - fee;

	if (account->_value > INT_MAX - credit || this->_liquidity > INT_MAX - fee)
		return false;

	account->_value += credit;
	this->_liquidity += fee;

	return true;
}

bool Bank::withdraw(int id, int amount)
{
	Account *account = this->_find(id);

	if (account == NULL || amount <= 0 || amount > account->_value)
		return false;

	account->_value -= amount;

	return true;
}

/**
 * @brief Lends the bank's own money to a client, within the limits of its
 * liquidity. No 5% fee: the money comes from the bank itself, it is not a
 * client inflow.
 *
 * @param id
 * @param amount
 * @return true if the loan was granted
 */
bool Bank::giveLoan(int id, int amount)
{
	Account *account = this->_find(id);

	if (account == NULL || amount <= 0 || amount > this->_liquidity)
		return false;
	if (account->_value > INT_MAX - amount)
		return false;

	this->_liquidity -= amount;
	account->_value += amount;

	return true;
}

const int &Bank::getLiquidity() const
{
	return this->_liquidity;
}

const Account *Bank::getAccount(int id) const
{
	return this->_find(id);
}

const std::map<int, Account *> &Bank::getAccounts() const
{
	return this->_accounts;
}

std::ostream &operator<<(std::ostream &o, const Bank &bank)
{
	const std::map<int, Account *> &accounts = bank.getAccounts();

	o << "Bank informations : " << std::endl;
	o << "Liquidity : " << bank.getLiquidity() << std::endl;
	for (std::map<int, Account *>::const_iterator it = accounts.begin(); it != accounts.end(); ++it)
		o << *it->second << std::endl;

	return o;
}
