#include <iostream>
#include "Ndarray.h"

int main()
{
	Ndarray<std::size_t> ndarr = {
		{2,3},
		{1,2,3,4,5,6}
	};

	std::cout << "original Ndarray: " << '\n';
	ndarr.print_ndarray();
	std::cout << '\n';

	Ndarray<std::size_t> reshaped_ndarr = ndarr.reshape({ 3,2 });
	
	std::cout << "reshaped Ndarray: " << '\n';
	reshaped_ndarr.print_ndarray();
	std::cout << '\n';
}