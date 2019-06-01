#ifndef ___POLYNOM_H___
#define ___POLYNOM_H___


#include <initializer_list> //обеспечивает доступ к массиву объектов типа T
#include <iterator>
#include <type_traits> 
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cstring>
#include <iostream>
#include "Util.h"

template <class Type, size_t POWER>
class Polynom
{
	Type data[POWER + 1];

public:
	Polynom() : data{} {};

	Polynom(const std::initializer_list<Type> &list)
	{
		using namespace std::string_literals;

		if (list.size() > POWER + 1)
			throw std::invalid_argument
			(
				"Invalid initializer list size: "s 
				+ std::to_string(list.size()) 
				+ ". It must be less or equal" 
				+ std::to_string(POWER + 1)
			);

		size_t data_begin = POWER + 1 - list.size();
		if (list.size() <= POWER)
			for (size_t i = 0, end = data_begin; i < end; ++i)
				data[i] = 0;

		auto &&it = list.end() - 1; 
		for (size_t i = data_begin; i <= POWER; ++i, --it)
			data[i] = *it;

		
	}

	Polynom(Type initial_value)
	{
		std::fill_n(std::begin(data), POWER + 1, initial_value);
	}

	Polynom(const Polynom &) = default;

	Polynom &operator=(const Polynom &rhs)
	{
		if (this != &rhs)
			std::copy(std::begin(rhs.data), std::end(rhs.data), std::begin(data));
		return *this;
	}


	~Polynom() = default;

	const Type &operator[](size_t index) const
	{
		if (index > POWER)
			throw std::out_of_range
			(
				"Index " + std::to_string(index) + " is out of range. " 
				+ "Max index is " + std::to_string(POWER - 1)
			);

		return data[POWER - index];
	}

	Type &operator[](size_t index)
	{
		if (index > POWER)
			throw std::out_of_range
			(
				"Index " + std::to_string(index) + " is out of range. "
				+ "Max index is " + std::to_string(POWER - 1)
			);

		return data[POWER - index];
	}

	template <size_t RHS_POWER> // RHS - ride side hand
	auto operator+(const Polynom<Type, RHS_POWER> &rhs) const
	{
		constexpr size_t MAX_POWER = util::max(POWER, RHS_POWER),
						 MIN_POWER = util::min(POWER, RHS_POWER);

		Polynom<Type, MAX_POWER> result;

		if constexpr (POWER == MAX_POWER) // Позволяет включать и выключать ветки компиляции
			for (size_t i = POWER; i > RHS_POWER; --i)
				result.data[i] = data[i];
		else
			for (size_t i = RHS_POWER; i > POWER; --i)
				result.data[i] = rhs.data[i];
		
		for (size_t i = 0; i <= MIN_POWER; ++i)
			result.data[i] = data[i] + rhs.data[i];

		return result;
	}

	template <size_t RHS_POWER>
	auto operator-(const Polynom<Type, RHS_POWER> &rhs) const
	{
		constexpr size_t MAX_POWER = util::max(POWER, RHS_POWER),
						 MIN_POWER = util::min(POWER, RHS_POWER);

		Polynom<Type, MAX_POWER> result;

		if constexpr (POWER == MAX_POWER)
			for (size_t i = POWER; i > RHS_POWER; --i)
				result.data[i] = data[i];
		else
			for (size_t i = RHS_POWER; i > POWER; --i)
				result.data[i] = -(rhs.data[i]);

		for (size_t i = 0; i <= MIN_POWER; ++i)
			result.data[i] = data[i] - rhs.data[i];

		return result;
	}

	template <size_t RHS_POWER>
	auto operator*(const Polynom<Type, RHS_POWER> &rhs) const
	{
		Polynom<Type, POWER + RHS_POWER> result;

		for(size_t i = POWER, j; i != -1; --i)
			for (j = RHS_POWER; j != -1; --j)
				result.data[i + j] += data[i] * rhs.data[j];
			
		return result;
	}

	template <typename Type, size_t POLYNOM_POWER>
	friend std::ostream &operator<<(std::ostream &os, const Polynom<Type, POLYNOM_POWER> &polynom);

	template <typename T, size_t N>
	friend class Polynom;
};


template <typename Type, size_t POLYNOM_POWER>
std::ostream &operator<<(std::ostream &os, const Polynom<Type, POLYNOM_POWER> &polynom)
{
	bool is_written = false;
	bool is_one = false;

	for (size_t i = POLYNOM_POWER; i != -1; --i)
		if (!util::is_zero(polynom.data[i]))
		{
			if (is_written)
				os << (util::is_negative(polynom.data[i]) ? " - " : " + ");

			is_one = util::is_one(polynom.data[i]);

			if (!is_one || i == 0)
			{
				if (std::is_arithmetic_v<Type> && i != POLYNOM_POWER)
					os << std::abs(polynom.data[i]);
				else
					os << polynom.data[i];
			}

			if (!is_one && i != 0)
				os << "*";

			if (i == 1)
				os << "x";
			else if (i != 0)
				os << "x^" << std::to_string(i);

			is_written = true;
		}

	return os;
}

#endif // ___POLYNOM_H___
