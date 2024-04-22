/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:42:43 by codespace         #+#    #+#             */
/*   Updated: 2024/04/22 08:57:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
public:
	explicit RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &src);
	~RobotomyRequestForm();

	RobotomyRequestForm &operator=(const RobotomyRequestForm &rhs);

	// cppcheck-suppress missingOverride
	void execute(const Bureaucrat &executor) const;

private:
	const std::string target;
};
