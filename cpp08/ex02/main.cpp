/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/07 16:38:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MutantStack.hpp"
#include <list>
#include <climits>

int main()
{
	std::cout << "MutantStack: " << std::endl;

	MutantStack<int> stack;

	stack.push(5);
	stack.push(17);

	std::cout << stack.top() << std::endl;

	stack.pop();

	std::cout << stack.size() << std::endl;

	stack.push(3);
	stack.push(5);
	stack.push(737);
	stack.push(0);
	stack.push(INT_MIN);
	stack.push(INT_MAX);

	MutantStack<int>::iterator stackBegin = stack.begin();
	MutantStack<int>::iterator stackEnd = stack.end();

	++stackBegin;
	--stackBegin;

	while (stackBegin != stackEnd)
	{
		std::cout << *stackBegin << std::endl;
		++stackBegin;
	}

	std::stack<int> s(stack);

	std::cout << s.size() << std::endl;

	std::cout << "List: " << std::endl;

	std::list<int> list;

	list.push_back(5);
	list.push_back(17);

	std::cout << list.back() << std::endl;

	list.pop_back();

	std::cout << list.size() << std::endl;

	list.push_back(3);
	list.push_back(5);
	list.push_back(737);
	list.push_back(0);
	list.push_back(INT_MIN);
	list.push_back(INT_MAX);	

	std::list<int>::iterator listBegin = list.begin();
	std::list<int>::iterator listEnd = list.end();

	++listBegin;
	--listBegin;

	while (listBegin != listEnd)
	{
		std::cout << *listBegin << std::endl;
		++listBegin;
	}

	std::list<int> l(list);

	std::cout << l.size() << std::endl;

	return 0;
}
