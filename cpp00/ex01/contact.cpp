/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:33:59 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 11:29:56 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"
#include <iostream>
#include <cstring>

Contact::Contact(std::string firstName,
								 std::string lastName,
								 std::string nickname,
								 std::string phone,
								 std::string darkestSecret)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->nickname = nickname;
	this->phone = phone;
	this->darkestSecret = darkestSecret;
}

Contact::~Contact()
{
}

void Contact::print() const
{
	std::cout << "First name: " << this->firstName << std::endl;
	std::cout << "Last name: " << this->lastName << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone number: " << this->phone << std::endl;
	std::cout << "Darkest Secret: " << this->darkestSecret << std::endl;
}

std::string Contact::getFirstName() const
{
	return this->firstName;
}

std::string Contact::getLastName() const
{
	return this->lastName;
}

std::string Contact::getNickname() const
{
	return this->nickname;
}
