#include <iostream>
#include "Ndarray.h"

int main()
{
	Ndarray<std::size_t> ndarr = {
		{2,3},
		{2,2,6,1,3,6}
	};

	std::cout << "original Ndarray: " << '\n';
	ndarr.print_ndarray();
	std::cout << '\n';

	Ndarray<std::size_t> resized_arr = ndarr.resize({ 3,3 });
	resized_arr.print_ndarray();
}