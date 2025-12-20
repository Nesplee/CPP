/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:27:26 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 13:43:13 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : _name("default name"), _isSigned(false), _signG(150), _execG(150) {
	std::cout<<GRAY<<"AForm default constructor called"<<RESET<<std::endl;
}

AForm::AForm(const std::string &name, const int sign, const int exec) : _name(name), _isSigned(false), _signG(sign), _execG(exec) {
	if (_signG < 1 || _execG < 1)
		throw	GradeTooHighE();
	if (_signG > 150 || _execG > 150)
		throw	GradeTooLowE();
	std::cout<<GRAY<<"Bureaucrat constructor w/ parameters called: "<<RESET<<std::endl;
	std::cout<<GRAY<<"AForm name  : "<<_name<<RESET<<std::endl;
	std::cout<<GRAY<<"Is signed  : "<<_isSigned<<RESET<<std::endl;
	std::cout<<GRAY<<"Sign grade : "<<_signG<<RESET<<std::endl;
	std::cout<<GRAY<<"Exec grade : "<<_execG<<RESET<<std::endl;
}

AForm::AForm(const AForm &o) : _name(o._name), _isSigned(o._isSigned), _signG(o._signG), _execG(o._execG) {
	std::cout<<GRAY<<"AForm copy constructor called: "<<RESET<<std::endl;
}

AForm&	AForm::operator=(const AForm &o) {
	std::cout<<GRAY<<"Bureaucrat copy assignment operator called: "<<RESET<<std::endl;
	if (this != &o)
		_isSigned = o._isSigned;
	return (*this);
}

AForm::~AForm() {
	std::cout<<GRAY<<"AForm destructor called"<<RESET<<std::endl;
}

const std::string&	AForm::getName() const { return (_name); }
bool				AForm::getIsSigned() const { return (_isSigned); }
int					AForm::getSignG() const { return (_signG); }
int					AForm::getExecG() const { return (_execG); }

void				AForm::beSigned(const Bureaucrat &b) {
	if (_isSigned)
		throw AlreadySignedE();
	if (b.getGrade() > _signG)
		throw GradeTooLowE();
	_isSigned = true;
}

void				AForm::_checkExecution(const Bureaucrat &b) const {
	if (!getIsSigned())
		throw	NotSignedE();
	if (b.getGrade() > getExecG())
		throw	GradeTooLowE();
}

const char*	AForm::GradeTooHighE::what() const throw() {
	return("Grade too high !");
}

const char*	AForm::GradeTooLowE::what() const throw() {
	return ("Grade too low !");
}

const char*	AForm::AlreadySignedE::what() const throw() {
	return ("AForm already signed !");
}

const char*	AForm::NotSignedE::what() const throw() {
	return("Form not signed !");
}

std::ostream&	operator<<(std::ostream &os, const AForm &o) {
	os<<BLUE<<"AForm : "<<o.getName()<<" - is Signed : "<<o.getIsSigned()<<" - Sign Grade : "<<o.getSignG()<<" - Exec Grade : "<<o.getExecG()<<RESET;
	return (os);
}
