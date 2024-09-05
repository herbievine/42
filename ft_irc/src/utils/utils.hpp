/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:05:13 by herbie            #+#    #+#             */
/*   Updated: 2024/09/05 17:01:35 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string &str, int sep = ' ');
void trim(std::string &s);
size_t stringToInt(const std::string &str);

#endif /* UTILS_HPP */
