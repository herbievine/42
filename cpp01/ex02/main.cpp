/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 15:36:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

using namespace std;

int main(void)
{
	string str = "HI THIS IS BRAIN";

	string *ptr = &str;
	string &ref = str;

	cout << &str << ": " << str << endl;
	cout << ptr << ": " << *ptr << endl;
	cout << &ref << ": " << ref << endl;

	return 0;
}
