/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:59:00 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 11:29:53 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default name"), _grade(150) {
	std::cout<<GRAY<<"Bureaucrat default constructor called"<<RESET<<std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name) {
	if (grade < 1)
		throw	GradeTooHighE();
	if (grade > 150)
		throw	GradeTooLowE();
	_grade = grade;
	std::cout<<GRAY<<"Bureaucrat constructor w/ parameters called: "<<RESET<<std::endl;
	std::cout<<GRAY<<"Name  : "<<_name<<RESET<<std::endl;
	std::cout<<GRAY<<"Grade : "<<_grade<<RESET<<std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {
	std::cout<<GRAY<<"Bureaucrat copy constructor called: "<<RESET<<std::endl;
}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat &other) {
	std::cout<<GRAY<<"Bureaucrat copy assignment operator called: "<<RESET<<std::endl;
	if (this != &other)
		_grade = other._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {
	std::cout<<GRAY<<"Bureaucrat destructor called"<<RESET<<std::endl;
}

const std::string&	Bureaucrat::getName() const { return (_name); }
int					Bureaucrat::getGrade() const { return (_grade); }

void	Bureaucrat::incrementGrade() {
	if (_grade <= 1)
		throw GradeTooHighE();
	_grade -= 1;
}

void	Bureaucrat::decrementGrade() {
	if (_grade >= 150)
		throw GradeTooLowE();
	_grade += 1;
}

const char*	Bureaucrat::GradeTooHighE::what() const throw() {
	return ("Grade too high !");
}

const char*	Bureaucrat::GradeTooLowE::what() const throw() {
	return ("Grade too low !");
}

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &o) {
	os<<GREEN<<o.getName()<<", bureaucrat grade "<<o.getGrade()<<RESET;
	return (os);
}
