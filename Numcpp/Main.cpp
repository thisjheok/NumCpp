#include <iostream>
#include "Ndarray.h"

int main()
{
	Ndarray<std::size_t> ndarr = {
		{2,3},
		{1,2,3,4,5,6}
	};

	ndarr.print_stride();
	std::cout << "ndarr.ndim: " << ndarr.ndim() << '\n';
	std::cout << "ndarr.size: " << ndarr.size() << '\n';
}