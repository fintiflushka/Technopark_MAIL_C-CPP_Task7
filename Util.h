#ifndef ___UTIL_H___
#define ___UTIL_H___


#include <type_traits>


namespace util // Пространство имён util
{
	template <typename Type> 
	constexpr const Type &max(const Type &a, const Type &b) //
	{
		return (a > b ? a : b);
	}

	template <typename Type>
	constexpr const Type &min(const Type &a, const Type &b)
	{
		return (a < b ? a : b);
	}

	template <typename Type>
	bool is_zero(const Type &value)
	{
		if constexpr (std::is_arithmetic_v<Type>) // Шаблонная переменная constexpr bool is_arithmetic_v = is_arithmetic<T>::value
			return value == static_cast<Type>(0);
		else
			return false;
	}

	template <typename Type>
	bool is_one(const Type &value)
	{
		if constexpr (std::is_arithmetic_v<Type>)
			return value == static_cast<Type>(1);
		else
			return false;
	}

	template <typename Type>
	bool is_negative(const Type &value)
	{
		if constexpr (std::is_arithmetic_v<Type>)
			return value < static_cast<Type>(0);
		else
			return false;
	}
}

#endif // ___UTIL_H___
