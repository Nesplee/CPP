/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:27:26 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 13:15:34 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name("default name"), _isSigned(false), _signG(150), _execG(150) {
	std::cout<<GRAY<<"Form default constructor called"<<RESET<<std::endl;
}

Form::Form(const std::string &name, const int sign, const int exec) : _name(name), _isSigned(false), _signG(sign), _execG(exec) {
	if (_signG < 1 || _execG < 1)
		throw	GradeTooHighE();
	if (_signG > 150 || _execG > 150)
		throw	GradeTooLowE();
	std::cout<<GRAY<<"Bureaucrat constructor w/ parameters called: "<<RESET<<std::endl;
	std::cout<<GRAY<<"Form name  : "<<_name<<RESET<<std::endl;
	std::cout<<GRAY<<"Is signed  : "<<_isSigned<<RESET<<std::endl;
	std::cout<<GRAY<<"Sign grade : "<<_signG<<RESET<<std::endl;
	std::cout<<GRAY<<"Exec grade : "<<_execG<<RESET<<std::endl;
}

Form::Form(const Form &o) : _name(o._name), _isSigned(o._isSigned), _signG(o._signG), _execG(o._execG) {
	std::cout<<GRAY<<"Form copy constructor called: "<<RESET<<std::endl;
}

Form&	Form::operator=(const Form &o) {
	std::cout<<GRAY<<"Bureaucrat copy assignment operator called: "<<RESET<<std::endl;
	if (this != &o)
		_isSigned = o._isSigned;
	return (*this);
}

Form::~Form() {
	std::cout<<GRAY<<"Form destructor called"<<RESET<<std::endl;
}

const std::string&	Form::getName() const { return (_name); }
bool				Form::getIsSigned() const { return (_isSigned); }
int					Form::getSignG() const { return (_signG); }
int					Form::getExecG() const { return (_execG); }

void				Form::beSigned(const Bureaucrat &b) {
	if (_isSigned)
		throw AlreadySignedE();
	if (b.getGrade() > _signG)
		throw GradeTooLowE();
	_isSigned = true;
}

const char*	Form::GradeTooHighE::what() const throw() {
	return("Grade too high !");
}

const char*	Form::GradeTooLowE::what() const throw() {
	return ("Grade too low !");
}

const char*	Form::AlreadySignedE::what() const throw() {
	return ("Form already signed !");
}

std::ostream&	operator<<(std::ostream &os, const Form &o) {
	os<<BLUE<<"Form : "<<o.getName()<<" - is Signed : "<<o.getIsSigned()<<" - Sign Grade : "<<o.getSignG()<<" - Exec Grade : "<<o.getExecG()<<RESET;
	return (os);
}
