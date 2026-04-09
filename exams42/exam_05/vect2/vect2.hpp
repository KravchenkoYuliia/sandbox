/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:13:34 by yukravch          #+#    #+#             */
/*   Updated: 2025/11/25 13:13:34 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {

public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2& other);
	
	vect2&	operator = (const vect2& other);
	int&	operator [] (int i);

	int	getX() const;
	int	getY() const;

	~vect2();

private:
	int	_x;
	int	_y;

};

vect2	operator * (int i, const vect2& other);
std::ostream&	operator << (std::ostream& out, const vect2& c);

#endif
