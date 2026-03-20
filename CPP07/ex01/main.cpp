/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguyendimitri <nguyendimitri@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 08:29:50 by dinguyen          #+#    #+#             */
/*   Updated: 2026/03/19 10:42:24 by nguyendimit      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>

void	print(int x) {
	std::cout<<x<<std::endl;
}

int	main() {
	int	arr[] = {1, 2, 3};
	iter(arr, 3, print);
	return (0);
}
