#include "Polynom.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;


template <typename Type, size_t power>
Polynom<Type, power> summ(Polynom<Type, power> p[5]);


int main()
{
	random_device rd; // Начальные значения для генератора.
	mt19937 gen(rd()); // Вихрь Мерсена
	uniform_int_distribution<int> rand_int(-5, 5);
	uniform_real_distribution<double> rand_double(2, 11);

	Polynom<int, 4> p_int[5];
	Polynom<double, 3> p_real[5];


	for (int i = 0; i < 5; i++)
	{
		p_int[i] = { rand_int(gen), rand_int(gen), rand_int(gen), rand_int(gen) };
		p_real[i] = { rand_double(gen), rand_double(gen), rand_double(gen)};
	}

	cout << summ(p_int) << endl;
	cout << summ(p_real) << endl;

}


template <typename Type, size_t power>
Polynom<Type, power> summ(Polynom<Type, power> p[5]) {
	Polynom<Type, power> p_res = p[0];
 
	for (int i = 1; i < 5; i++) 
	{
		p_res = p_res + p[i]; 
	}

	return p_res;
}

