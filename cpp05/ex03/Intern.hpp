/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2024/04/22 10:13:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AForm.hpp"

class Intern
{
public:
	explicit Intern();
	Intern(const Intern &src);
	~Intern();

	Intern &operator=(const Intern &rhs);

	AForm *makeForm(const std::string &name, const std::string &target) const;
};
