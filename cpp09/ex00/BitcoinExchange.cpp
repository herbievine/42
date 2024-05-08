/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/08 20:25:41 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

BitcoinExchange::BitcoinExchange()
{
	_loadCsv("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string &file)
{
	_loadCsv(file);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	return *this;
}

/**
 * @brief The getExchangeRates function takes a string file as input and reads
 * the contents of the file. It then parses the data points and finds the
 * exchange rate for each date. If the date is not found, the function finds the
 * exchange rate for the previous date.
 *
 * @param file
 */
void BitcoinExchange::getExchangeRates(const std::string &file)
{
	std::ifstream ifs(file);

	if (!ifs.is_open())
		throw CannotOpenFileException();

	std::string line;

	while (std::getline(ifs, line))
	{
		if (line.empty() || line.compare("date | value") == 0)
			continue;

		BE::DataPoint dp = _parseDataPoint(line);

		if (!dp.isValid)
		{
			std::cerr << "Error: " << dp.invalidReason << std::endl;
			continue;
		}

		_getRate(dp);
	}
}

/**
 * @brief The _loadCsv function takes a string file as input and loads the
 * contents of the file into the _csv map. It also checks if the file is
 * valid and throws an exception if it is not.
 *
 * @param file
 */
void BitcoinExchange::_loadCsv(const std::string &file)
{
	std::ifstream ifs(file);

	if (!ifs.is_open())
		throw CannotOpenFileException();

	std::string line;

	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		if (line.empty())
			continue;

		size_t pos = line.find(',');

		if (pos == std::string::npos)
			throw InvalidFileException();

		std::string date = line.substr(0, pos);
		std::string price = line.substr(pos + 1);

		_csv[date] = std::stof(price);
	}
}

/**
 * @brief The _parseDataPoint function takes a string line as input and returns
 * a DataPoint object. It checks if the line is valid and returns the data
 * point. If the line is not valid, the function returns an invalid DataPoint
 * object.
 *
 * @param line
 * @return BitcoinExchange::DataPoint
 */
BitcoinExchange::DataPoint BitcoinExchange::_parseDataPoint(const std::string &line) const
{
	BE::DataPoint dp;

	size_t pos = line.find(" | ");

	if (pos == std::string::npos)
	{
		dp.price = 0;
		dp.isValid = false;
		dp.invalidReason = "Bad input => " + line;

		return dp;
	}

	try
	{
		dp.price = _parsePrice(line.substr(pos + 3));
		dp.date = _parseDate(line.substr(0, pos));
		dp.isValid = true;
	}
	catch (const std::exception &e)
	{
		dp.price = 0;
		dp.isValid = false;
		dp.invalidReason = e.what();

		return dp;
	}

	return dp;
}

/**
 * @brief The _parseDate function takes a string date as input and returns the
 * same date if it is valid. If the date is not valid, the function throws an
 * exception. It checks if the date is in the format "YYYY-MM-DD".
 *
 * @param date
 * @return std::string
 */
std::string BitcoinExchange::_parseDate(const std::string &date) const
{
	if (date.length() != 10)
		throw std::runtime_error("Invalid date format");

	int year, month, day;

	year = std::stoi(date.substr(0, 4));
	month = std::stoi(date.substr(5, 2));
	day = std::stoi(date.substr(8, 2));

	if (month < 1 || month > 12)
		throw std::runtime_error("Invalid month");

	int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	bool isLeapYear = false;

	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		isLeapYear = true;

	if (isLeapYear)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		throw std::runtime_error("Invalid day");

	return date;
}

/**
 * @brief The _parsePrice function takes a string price as input and returns
 * a float equivalent. If the price is not valid, the function throws an
 * exception. It checks if the price is a positive number and less than 10000.
 *
 * @param price
 * @return float
 */
float BitcoinExchange::_parsePrice(const std::string &price) const
{
	float value = std::stof(price);

	if (value < 0)
		throw std::runtime_error("Not a positive number");
	else if (value > 10000)
		throw std::runtime_error("Too high a number");

	return value;
}

/**
 * @brief The _getRate function takes a DataPoint object as input finds the
 * exchange rate for the given date. If the date is not found, the function
 * finds the exchange rate for the previous date.
 *
 * @param dp
 */
void BitcoinExchange::_getRate(const DataPoint &dp)
{
	std::map<std::string, float>::iterator it = _csv.lower_bound(dp.date);

	if (it == _csv.end())
	{
		--it;

		std::cout << dp.date << " => " << dp.price << " = " << dp.price * it->second << std::endl;
	}
	else if (it == _csv.begin())
		std::cerr << "Error: No previous data" << std::endl;
	else
	{
		if (it->first != dp.date)
			--it;

		std::cout << dp.date << " => " << dp.price << " = " << dp.price * it->second << std::endl;
	}
}
