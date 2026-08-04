#include <iostream>
#include "Ndarray.h"

int main()
{
	Ndarray<std::size_t> ndarr = {
		{2,3}
	};

	ndarr.fill(1);
	ndarr.print_elem();
}