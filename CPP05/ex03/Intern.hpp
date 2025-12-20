/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:15:15 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 16:33:52 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

class	AForm;
class	Intern {

private:
	AForm*	createShrubbery(const std::string &target);
	AForm*	createRobotomy(const std::string &target);
	AForm*	createPresidential(const std::string &target);

public:
	Intern();
	Intern(const Intern &other);
	Intern&	operator=(const Intern &other);
	~Intern();

	AForm*	makeForm(const std::string &formName, const std::string &target);

	class	InvalidFormNameE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
};

#endif
