/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/13 08:27:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>

class BitcoinExchange
{
public:
	typedef BitcoinExchange BE;

	explicit BitcoinExchange();
	explicit BitcoinExchange(const std::string &file);
	BitcoinExchange(const BitcoinExchange &src);
	~BitcoinExchange();

	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	typedef struct
	{
		std::string date;
		float price;
		bool isValid;
		std::string invalidReason;
	} DataPoint;

	void getExchangeRates(const std::string &file);

	class CannotOpenFileException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Cannot open file";
		}
	};

	class InvalidFileException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Invalid file";
		}
	};

private:
	std::map<std::string, float> _csv;

	void _loadCsv(const std::string &file);

	DataPoint _parseDataPoint(const std::string &line) const;
	std::string _parseDate(const std::string &date) const;
	float _parsePrice(const std::string &price) const;
	void _getRate(const DataPoint &dp);
};
