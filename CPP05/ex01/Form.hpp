/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:15:33 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 13:45:14 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include "Bureaucrat.hpp"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define GRAY "\033[0;30m"
# define RESET "\033[0m"

class	Bureaucrat;
class	Form {

private:
	const std::string	_name;
	bool				_isSigned;
	const int			_signG;
	const int			_execG;

public:
	Form();
	Form(const std::string &name, const int sign, const int exec);
	Form(const Form &o);
	Form&	operator=(const Form &o);
	~Form();

	const std::string&	getName() const;
	bool				getIsSigned() const;
	int					getSignG() const;
	int					getExecG() const;
	void				beSigned(const Bureaucrat &b);

	class	GradeTooHighE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
	class	GradeTooLowE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
	class	AlreadySignedE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
};

std::ostream&	operator<<(std::ostream &os, const Form &o);

#endif
