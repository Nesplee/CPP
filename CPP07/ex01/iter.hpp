/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 08:05:15 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/17 08:29:03 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

template<typename T>
void	iter(T* array, const int length, void (*func)(T)) {
	for (int i = 0; i < length; i++)
		func(array[i]);
}

template<typename T>
void	iter(T* array, const int length, void (*func)(const T &)) {
	for (int i = 0; i < length; i++) {
		func(array[i]);
	}
}
