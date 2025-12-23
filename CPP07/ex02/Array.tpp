/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinguyen <dinguyen@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 19:34:51 by dinguyen          #+#    #+#             */
/*   Updated: 2025/12/17 19:44:50 by dinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template<typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template<typename T>
Array<T>::Array(unsigned int n) : _size(n) {
	_data = new T[n]();
}

template<typename T>
Array<T>::Array(const Array &other) : _size(other._size) {
	_data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		_data[i] = other._data[i];
}

template<typename T>
Array<T>&	Array<T>::operator=(const Array &other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_data = new T[_size];
		for (unsigned int i = 0; i < _size; i++)
			_data[i] = other._data[i];
	}
	return (*this);
}

template<typename T>
Array<T>::~Array() {
	delete[] _data;
}

template<typename T>
const T&	Array<T>::operator[](unsigned int index) const {
	if (index >= _size)
		throw IndexNotFoundE();
	return (_data[index]);
}

template<typename T>
T&	Array<T>::operator[](unsigned int index) {
	if (index >= _size)
		throw	IndexNotFoundE();
	return (_data[index]);
}

template<typename T>
unsigned int	Array<T>::size() const {
	return (_size);
}

template<typename T>
const char*	Array<T>::IndexNotFoundE::what() const throw() {
	return ("Index out of bounds");
}
