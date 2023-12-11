/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:18:07 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 13:05:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#define MAX_CONTACTS 8

struct ContactField
{
	std::string name;
	std::string value;
};

class PhoneBook
{
public:
	PhoneBook();
	~PhoneBook();

	Contact *contacts[8];

	int count;
	int length;

	void add();
	void search();

private:
	std::string getTruncated(std::string str) const;
};

#endif /* PHONEBOOK_HPP */