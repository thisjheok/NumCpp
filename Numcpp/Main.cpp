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

	Ndarray<std::size_t> transposed_arr = ndarr.transpose({ 1,0 });
	transposed_arr.print_ndarray();
}