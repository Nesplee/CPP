/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:01:30 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:11:59 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) :
	AForm("RobotomyRequestForm", 72, 45), _target(target) {
		std::cout<<GRAY<<"RobotomyRequestForm constructor called with parameter : "<<RESET<<std::endl;
		std::cout<<GRAY<<"Target : "<<_target<<RESET<<std::endl;};

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) :
	AForm(other), _target(other._target) {
	std::cout<<GRAY<<"RobotomyRequestForm copy constructor called"<<RESET<<std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	std::cout<<GRAY<<"RobotomyRequestForm copy assignment operator called"<<RESET<<std::endl;
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout<<GRAY<<"RobotomyRequestForm destructor called"<<RESET<<std::endl;
}

void	RobotomyRequestForm::execute(const Bureaucrat &b) const {
	_checkExecution(b);
	std::cout<<BLUE<<" * DRILLING NOISES * "<<RESET<<std::endl;
	if (std::rand() % 2 == 0)
		std::cout<<BLUE<<_target<<" has been robotomized successfully!"<<RESET<<std::endl;
	else
		std::cout<<BLUE<<_target<<" : robotomy failed!"<<RESET<<std::endl;
}
