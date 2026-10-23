/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

// x and y are private with const getters and no setters: a point is set once
// at construction and nobody (not even Graph) can move it afterwards, so a
// validated point stays valid.
class Vector2
{
public:
	explicit Vector2(float x, float y);
	Vector2(const Vector2 &src);
	~Vector2();

	Vector2 &operator=(const Vector2 &rhs);

	const float &getX() const;
	const float &getY() const;

private:
	float _x;
	float _y;
};

#endif /* VECTOR2_HPP */
