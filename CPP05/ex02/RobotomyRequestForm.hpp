/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:51:55 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/20 14:02:50 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include "AForm.hpp"
# include <ctime>
# include <cstdlib>

class	Bureaucrat;
class	RobotomyRequestForm : public AForm {

private:
	std::string	_target;

public:
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	RobotomyRequestForm&	operator=(const RobotomyRequestForm &other);
	~RobotomyRequestForm();

	void	execute(const Bureaucrat &b) const;
};

#endif
