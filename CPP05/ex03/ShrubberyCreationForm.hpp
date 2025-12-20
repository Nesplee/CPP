/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:51:29 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:09:37 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include "AForm.hpp"
# include <fstream>
class	ShrubberyCreationForm : public AForm {

private:
	std::string	_target;

public:
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &o);
	ShrubberyCreationForm&	operator=(const ShrubberyCreationForm &o);
	~ShrubberyCreationForm();

	void	execute(const Bureaucrat &b) const;

	class	OpenFileE : public std::exception  {
		public:
			virtual const char*	what() const throw();
	};
};

#endif
