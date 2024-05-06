/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/06 16:43:29 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <class T>
class Array
{
public:
	explicit Array();
	explicit Array(unsigned int n);
	Array(const Array &src);
	~Array();

	Array &operator=(const Array &rhs);
	T &operator[](unsigned int index) const;

	unsigned int size() const;

	class OutOfBoundsException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Out of bounds";
		}
	};

private:
	T *_data;
	unsigned int _size;
};

template <typename T>
Array<T>::Array()
{
	_data = NULL;
	_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int n)
{
	_data = new T[n];
	_size = n;
}

template <typename T>
Array<T>::Array(const Array &src)
{
	_data = new T[src._size];
	_size = src._size;

	for (unsigned int i = 0; i < src._size; i++)
		_data[i] = src._data[i];
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
	if (&rhs != this)
	{
		delete[] _data;
		_data = new T[rhs._size];
		_size = rhs._size;

		for (unsigned int i = 0; i < rhs._size; i++)
			_data[i] = rhs._data[i];
	}

	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template <typename T>
unsigned int Array<T>::size() const
{
	return (_size);
}

template <typename T>
T &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();

	return _data[index];
}
