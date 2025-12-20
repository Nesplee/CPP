/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:03:36 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:11:19 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) :
	AForm("PresidentialPardonForm", 25, 5), _target(target) {
		std::cout<<GRAY<<"PresidentialPardonForm constructor called with parameter : "<<RESET<<std::endl;
		std::cout<<GRAY<<"Target : "<<_target<<RESET<<std::endl;};

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) :
	AForm(other), _target(other._target) {
	std::cout<<GRAY<<"PresidentialPardonForm copy constructor called"<<RESET<<std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	std::cout<<GRAY<<"PresidentialPardonForm copy assignment operator called"<<RESET<<std::endl;
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout<<GRAY<<"PresidentialPardonForm destructor called"<<RESET<<std::endl;
}

void	PresidentialPardonForm::execute(const Bureaucrat &b) const {
	_checkExecution(b);
	std::cout<<BLUE<<_target<<" has been pardoned by Zaphod Beeblebrox."<<RESET<<std::endl;
}
