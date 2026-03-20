/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguyendimitri <nguyendimitri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 08:05:15 by dinguyen          #+#    #+#             */
/*   Updated: 2026/03/19 10:37:36 by nguyendimit      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
