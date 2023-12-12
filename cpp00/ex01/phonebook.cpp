/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:44:06 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 13:42:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
#include "contact.hpp"
#include <iostream>
#include <cstring>
#include <iomanip>

PhoneBook::PhoneBook() : contacts(), count(0), length(0)
{
}

PhoneBook::~PhoneBook()
{
}

void PhoneBook::add()
{
	ContactField fields[5] = {
			{.name = "First name",
			 .value = ""},
			{.name = "Last name",
			 .value = ""},
			{.name = "Nickname",
			 .value = ""},
			{.name = "Phone number",
			 .value = ""},
			{.name = "Darkest secret",
			 .value = ""}};

	// find correct index, If the user tries to add a 9th contact, replace the oldest one by the new one.
	if (this->count == MAX_CONTACTS)
		this->count = 0;

	for (int j = 0; j < 5; j++)
	{
		std::cout << fields[j].name << ": ";
		while (fields[j].value.empty() && fields[j].value.length() == 0)
		{
			if (std::cin.eof())
				return;
			std::getline(std::cin, fields[j].value);
		}
	}

	this->contacts[count] = new Contact(fields[0].value,
																			fields[1].value,
																			fields[2].value,
																			fields[3].value,
																			fields[4].value);
	this->count++;
	this->length++;
}

void PhoneBook::search()
{
	int i;
	std::string index;

	std::cout << "+==========+==========+==========+==========+" << std::endl;
	std::cout << "|" << std::left << std::setw(10) << "Index";
	std::cout << "|" << std::left << std::setw(10) << "First name";
	std::cout << "|" << std::left << std::setw(10) << "Last name";
	std::cout << "|" << std::left << std::setw(10) << "Nickname";
	std::cout << "|" << std::endl;
	std::cout << "+==========+==========+==========+==========+" << std::endl;
	for (i = 0; i < std::min(MAX_CONTACTS, this->length); i++)
	{
		std::cout << "|" << std::left << std::setw(10) << i;
		std::cout << "|" << std::left << std::setw(10) << this->getTruncated(this->contacts[i]->getFirstName());
		std::cout << "|" << std::left << std::setw(10) << this->getTruncated(this->contacts[i]->getLastName());
		std::cout << "|" << std::left << std::setw(10) << this->getTruncated(this->contacts[i]->getNickname());
		std::cout << "|" << std::endl;
		if (i < std::min(MAX_CONTACTS, this->length) - 1)
			std::cout << "+----------+----------+----------+----------+" << std::endl;
	}
	std::cout << "+==========+==========+==========+==========+" << std::endl;

	std::cout << "Enter index: ";
	std::getline(std::cin, index);

	if (std::cin.eof())
		return;
	else if (index.empty())
		return;
	else if (index.length() > 1)
		return;
	else if (index[0] < '0' || index[0] > '7')
		return;
	else if (index[0] - '0' >= std::min(MAX_CONTACTS, this->length))
		return;
	else
		this->contacts[index[0] - '0']->print();
}

std::string PhoneBook::getTruncated(std::string str) const
{
	if (str.length() > 10)
	{
		str.resize(9);
		str.append(".");
	}
	return str;
}
