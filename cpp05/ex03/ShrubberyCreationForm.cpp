/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:48:11 by codespace         #+#    #+#             */
/*   Updated: 2024/04/22 09:05:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("Shrubbery Creation Form", 145, 137), target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src) : AForm(src), target(src.target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
{
	(void)rhs;
	return *this;
}

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	if (!getIsSigned())
		throw NotSignedException();
	if (executor.getGrade() > this->getGradeToExec())
		throw GradeTooLowException();

	std::ofstream file(this->target + "_shrubbery");

	file << "            .        +          .      .          ." << std::endl;
	file << "     .            _        .                    ." << std::endl;
	file << "  ,              /;-._,-.____        ,-----.__" << std::endl;
	file << " ((        .    (_:#::_.:::. `-._   /:, /-._, `._," << std::endl;
	file << "  `                 \\   _|`\"=:_::.`.);  \\ __/ /" << std::endl;
	file << "                      ,    `./  \\:. `.   )==-'  ." << std::endl;
	file << "    .      ., ,-=-.  ,\\, +#./`   \\:.  / /           ." << std::endl;
	file << ".           \\/:/`-' , ,\\ '` ` `   ): , /_  -o" << std::endl;
	file << "       .    /:+- - + +- : :- + + -:'  /(o-) \\)     ." << std::endl;
	file << "  .      ,=':  \\    ` `/` ' , , ,:' `'--\".--\"---._/`7" << std::endl;
	file << "   `.   (    \\: \\,-._` ` + '\\, ,\"   _,--._,---\":.__/" << std::endl;
	file << "              \\:  `  X` _| _,\\/'   .-'" << std::endl;
	file << ".               \":._:`\\____  /:'  /      .           ." << std::endl;
	file << "                    \\::.  :\\/:'  /              +" << std::endl;
	file << "   .                 `.:.  /:'  }      ." << std::endl;
	file << "           .           ):_(:;   \\           ." << std::endl;
	file << "                      /:. _/ ,  |" << std::endl;
	file << "                   . (|::.     ,`                  ." << std::endl;
	file << "	   .                |::.    {\\" << std::endl;
	file << "                      |::.\\  \\ `." << std::endl;
	file << "                      |:::(\\    |" << std::endl;
	file << "              O       |:::/{ }  |                  (o" << std::endl;
	file << "               )  ___/#\\::`/ (O \"==._____   O, (O  /`" << std::endl;
	file << "          ~~~w/w~\"~~,\\` `:/,-(~`\"~~~~~~~~\"~o~\\~/~w|/~" << std::endl;
	file << "    ~~~~~~~~~~~~~~~~~~~~~~~\\W~~~~~~~~~~~~\\|/~~" << std::endl;

	file.close();
}
