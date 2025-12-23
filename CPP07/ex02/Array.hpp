/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:09:25 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/17 19:42:58 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <exception>

template<typename T>
class	Array {

private:
	T*				_data;
	unsigned int	_size;
public:
	Array();
	Array(unsigned int n);
	Array(const Array &other);
	Array&	operator=(const Array &other);
	~Array();

	T&				operator[](unsigned int index);
	const T&		operator[](unsigned int index) const;
	unsigned int	size() const;

	class	IndexNotFoundE : public std::exception {
		public:
			virtual const char*	what() const throw();
	};
};

# include "Array.tpp"
# endif
