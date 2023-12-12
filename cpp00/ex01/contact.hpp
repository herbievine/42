/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:33:56 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 13:42:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CONTACT_HPP
#define CONTACT_HPP

class Contact
{
public:
	Contact(std::string const &firstName,
					std::string const &lastName,
					std::string const &nickname,
					std::string const &phone,
					std::string const &darkestSecret);
	~Contact();
	void print() const;
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