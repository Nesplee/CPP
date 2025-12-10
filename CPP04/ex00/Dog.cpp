/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:29:28 by dinguyen          #+#    #+#             */
/*   Updated: 2025/11/25 10:42:08 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal() {
	_type = "Dog";
	std::cout<<"Dog default constructor called"<<std::endl;
}

Dog::Dog(const Dog &other) : Animal(other) {
	std::cout<<"Dog copy constructor called"<<std::endl;
}

Dog&	Dog::operator=(const Dog &other) {
	if (this != &other) {
		Animal::operator=(other);
	}
	return (*this);
}

Dog::~Dog() {
	std::cout<<"Dog destructor called"<<std::endl;
}

void	Dog::makeSound() const {
	std::cout<<"WOOOF!WOOOFFFFFFF! GRRRRRRRR"<<std::endl;
}

