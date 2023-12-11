/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:33:56 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 11:29:46 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CONTACT_HPP
#define CONTACT_HPP

class Contact
{
public:
	Contact(std::string firstName,
					std::string lastName,
					std::string nickname,
					std::string phone,
					std::string darkestSecret);
	~Contact();
	void print() const;
	bool isEmpty() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getNickname() const;

private:
	std::string firstName;
	std::string lastName;
	std::string nickname;
	std::string phone;
	std::string darkestSecret;
};

#endif /* CONTACT_H */