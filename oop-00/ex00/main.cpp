/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bank.hpp"

static void check(const char *action, bool ok)
{
	std::cout << action << " : " << (ok ? "OK" : "REFUSED") << std::endl;
}

int main()
{
	Bank bank(999);

	int a = bank.createAccount();
	int b = bank.createAccount();
	int c = bank.createAccount();

	std::cout << "Created accounts " << a << ", " << b << ", " << c << std::endl;
	std::cout << bank << std::endl;

	check("Deposit 100 on A (95 to A, 5 to bank)", bank.deposit(a, 100));
	check("Deposit 100 on B (95 to B, 5 to bank)", bank.deposit(b, 100));
	check("Deposit 19 on C (fee rounds down to 0)", bank.deposit(c, 19));
	std::cout << bank << std::endl;

	check("Withdraw 50 from A", bank.withdraw(a, 50));
	check("Withdraw 1000 from B (insufficient funds)", bank.withdraw(b, 1000));
	check("Deposit -10 on A (negative amount)", bank.deposit(a, -10));
	std::cout << bank << std::endl;

	check("Loan 400 to A (bank has enough)", bank.giveLoan(a, 400));
	check("Loan 10000 to B (bank has not enough)", bank.giveLoan(b, 10000));
	std::cout << bank << std::endl;

	check("Delete C", bank.deleteAccount(c));
	check("Delete C again (no longer exists)", bank.deleteAccount(c));
	check("Deposit on C (no longer exists)", bank.deposit(c, 100));
	check("Deposit on 42 (unknown id)", bank.deposit(42, 100));
	check("Withdraw from 42 (unknown id)", bank.withdraw(42, 100));
	check("Loan to 42 (unknown id)", bank.giveLoan(42, 100));

	int d = bank.createAccount();

	std::cout << "New account gets a fresh id (deleted ids are not reused): " << d << std::endl;

	const Account *accountA = bank.getAccount(a);

	if (accountA)
		std::cout << "Account A : " << *accountA << std::endl;
	if (bank.getAccount(42) == NULL)
		std::cout << "Account 42 : not found" << std::endl;

	std::cout << " ----- " << std::endl;
	std::cout << bank << std::endl;

	// None of the following compiles anymore:
	// Account account;                   // constructor is private: only Bank creates accounts
	// accountA->_value = 1000000;        // _value is private
	// bank._liquidity -= 200;            // _liquidity is private
	// bank.getAccounts()[a]->_value = 0; // const map, and _value is private
	// Bank copy = bank;                  // copy constructor is private: Bank owns its accounts

	return 0;
}
