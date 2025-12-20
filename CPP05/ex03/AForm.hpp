/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 12:15:33 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:00:08 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AForm_HPP
# define AForm_HPP

# include <iostream>
# include <string>
# include "Bureaucrat.hpp"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define GRAY "\033[0;30m"
# define RESET "\033[0m"

class	Bureaucrat;
class	AForm {

private:
	const std::string	_name;
	bool				_isSigned;
	const int			_signG;
	const int			_execG;

protected:
	void	_checkExecution(const Bureaucrat &b) const;

public:
	AForm();
	AForm(const std::string &name, const int sign, const int exec);
	AForm(const AForm &o);
	AForm&	operator=(const AForm &o);
	virtual ~AForm();

	const std::string&	getName() const;
	bool				getIsSigned() const;
	int					getSignG() const;
	int					getExecG() const;
	void				beSigned(const Bureaucrat &b);
	virtual void		execute(const Bureaucrat &b) const = 0;

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
	class	NotSignedE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
};

std::ostream&	operator<<(std::ostream &os, const AForm &o);

#endif
