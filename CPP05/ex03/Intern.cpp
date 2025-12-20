/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:18:13 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 16:31:26 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {
	std::cout<<GRAY<<"Intern default constructor called"<<RESET<<std::endl;
}
Intern::Intern(const Intern &other) {
	std::cout<<GRAY<<"Intern copy constructor called"<<RESET<<std::endl;
	(void)other;
}
Intern&	Intern::operator=(const Intern &other) {
	std::cout<<GRAY<<"Intern copy assignment operator called"<<RESET<<std::endl;
	(void)other;
	return (*this);
}
Intern::~Intern() {
	std::cout<<GRAY<<"Intern destructor called"<<RESET<<std::endl;
}

AForm*	Intern::createShrubbery(const std::string &target) {
	AForm	*f = new ShrubberyCreationForm(target);
	return (f);
}

AForm*	Intern::createRobotomy(const std::string &target) {
	AForm	*f = new RobotomyRequestForm(target);
	return (f);
}

AForm*	Intern::createPresidential(const std::string &target) {
	AForm	*f = new PresidentialPardonForm(target);
	return (f);
}

AForm*	Intern::makeForm(const std::string &formName, const std::string &target) {
	std::string	goodForms[3] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	AForm*	(Intern::*functions[3])(const std::string&) = { &Intern::createShrubbery, &Intern::createRobotomy, &Intern::createPresidential};
	for (int i = 0; i < 3; i++) {
		if (formName == goodForms[i]) {
			std::cout<<BLUE<<"Intern creates "<<goodForms[i]<<RESET<<std::endl;
			return ((*this).*functions[i])(target);
		}
	}
	throw InvalidFormNameE();
	return (NULL);
}

const char*	Intern::InvalidFormNameE::what() const throw() {
	return ("Invalid form name !");
}


