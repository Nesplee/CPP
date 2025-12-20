/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:50:38 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:03:26 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "AForm.hpp"

class	Bureaucrat;
class	PresidentialPardonForm : public AForm {

private:
	std::string	_target;

public:
	PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	PresidentialPardonForm&	operator=(const PresidentialPardonForm &f);
	~PresidentialPardonForm();

	void	execute(const Bureaucrat &b) const;
};

#endif
