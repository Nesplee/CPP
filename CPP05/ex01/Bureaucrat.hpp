/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 10:58:13 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 13:11:39 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>
# include "Form.hpp"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define GRAY "\033[0;30m"
# define RESET "\033[0m"

class	Form;
class	Bureaucrat {

private:
	const std::string	_name;
	int					_grade;

public:
	Bureaucrat();
	Bureaucrat(const std::string &name, int grade);
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat&	operator=(const Bureaucrat &other);
	~Bureaucrat();

	const std::string&	getName() const;
	int					getGrade() const;
	void				incrementGrade();
	void				decrementGrade();

	void				signForm(Form &f);

	class	GradeTooHighE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};

	class	GradeTooLowE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
};

std::ostream&	operator<<(std::ostream &os, const Bureaucrat &o);

#endif
