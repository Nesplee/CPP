/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:47:23 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/16 17:03:31 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template<typename T>
void	swap(T &a, T &b) {
	T	temp = a;
	a = b;
	b = temp;
}

template<typename T>
T	min(T a, T b) {
	if (a < b)
		return (a);
	return (b);
}

template<typename T>
T	max(T a, T b) {
	if (a > b)
		return (a);
	return (b);
}

#endif
