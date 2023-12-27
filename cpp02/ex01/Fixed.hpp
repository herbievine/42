
#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
public:
	Fixed();
	explicit Fixed(int const value);
	explicit Fixed(float const value);
	Fixed(const Fixed &rhs);
	Fixed &operator=(const Fixed &rhs);
	~Fixed();

	float toFloat(void) const;
	int toInt(void) const;

	int getRawBits(void) const;
	void setRawBits(int const raw);

private:
	int fixedPointValue;
	static const int fractionalBits = 8;
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif /* FIXED_HPP */
