/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:13:34 by yukravch          #+#    #+#             */
/*   Updated: 2025/11/25 13:13:34 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2(): _x(0), _y(0) {}

vect2::vect2(int x, int y): _x(x), _y(y) {}

vect2::vect2(const vect2& other) { *this = other; }

vect2&	vect2::operator=(const vect2& other) {

	if (this != &other) {
		this->_x = other._x;
		this->_y = other._y;
	}
	return *this;
}

int&	vect2::operator [] (int i) {

	if (i == 0)
		return this->_x;
	if (i == 1)
		return this->_y;
	return _x;
}

int	vect2::getX() const { return _x; }
int	vect2::getY() const { return _y; }

vect2	operator * (int i, const vect2& other) {

	vect2	temp(i*other.getX(), i*other.getY());
	return temp;
}


vect2::~vect2() {}


std::ostream&	operator << (std::ostream& out, const vect2& c) {

	out << "{" << c.getX() << ", " << c.getY() << "}";
	return out;
}
