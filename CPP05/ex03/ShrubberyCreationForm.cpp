/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:57:04 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:10:48 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) :
	AForm("ShrubberyCreationForm", 145, 137), _target(target) {
		std::cout<<GRAY<<"ShrubberyCreationForm constructor called with parameter : "<<RESET<<std::endl;
		std::cout<<GRAY<<"Target : "<<_target<<RESET<<std::endl;};

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) :
	AForm(other), _target(other._target) {
	std::cout<<GRAY<<"ShrubberyCreationForm copy constructor called"<<RESET<<std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	std::cout<<GRAY<<"ShrubberyCreationForm copy assignment operator called"<<RESET<<std::endl;
	if (this != &other) {
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout<<GRAY<<"ShrubberyCreationForm destructor called"<<RESET<<std::endl;
}

void	ShrubberyCreationForm::execute(const Bureaucrat &b) const {
	_checkExecution(b);
	std::ofstream	outfile((_target + "_shrubbery").c_str());
	if (!outfile)
		throw ShrubberyCreationForm::OpenFileE();
	outfile<<"     ^     "<<std::endl;
	outfile<<"    ^^^    "<<std::endl;
	outfile<<"   ^^^^^   "<<std::endl;
	outfile<<"  ^^^^^^^  "<<std::endl;
	outfile<<" ^^^^^^^^^ "<<std::endl;
	outfile<<"     +     "<<std::endl;
	outfile.close();
}

const char*	ShrubberyCreationForm::OpenFileE::what() const throw() {
	return("Error opening file !");
}
