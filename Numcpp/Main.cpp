#include <iostream>
#include "Ndarray.h"

int main()
{
	Ndarray<std::size_t> ndarr = {
		{3,3,3},
		{2,2,6,1,3,6,1,0,1,2,2,6,1,3,6,1,0,1,2,2,6,1,3,6,1,0,1}
	};

	std::cout << "original Ndarray: " << '\n';
	ndarr.print_ndarray();
	std::cout << '\n';

	Ndarray<std::size_t> reshaped_ndarr = ndarr.reshape({ 3,3 });
	
	std::cout << "reshaped Ndarray: " << '\n';
	reshaped_ndarr.print_ndarray();
	std::cout << '\n';

	std::size_t result = ndarr.item({ 1,2,2 });
	std::cout << "result: " << result;
}