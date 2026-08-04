#include "Ndarray.h"
#include <memory>
#include <iostream>

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape)
	:shape_(std::move(shape))
{
	int data_size = 1;
	for (std::size_t elem : shape)
	{
		data_size *= elem;
	}
	data_.reserve(data_size);
}

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape, std::vector<T> data)
	:shape_(std::move(shape)),
	data_(std::move(data))
{
	stride_.reserve(shape_.size());
	for(std::size_t i = shape_.size(); i > 0; --i)// i: 3, 2, 1
	{
		std::size_t stride_elem = 1;
		for (int j = 0; j < i-1; ++j) // i:3, j:0,1 | i:2, j:0 
		{
			stride_elem *= shape_[shape_.size() - j - 1]; // shape_[2..1..] | shape_[2]
		}
		stride_.push_back(stride_elem);
	}
}

template <typename T>
std::size_t Ndarray<T>::size() const
{
	return data_.size();
}

template <typename T>
std::size_t Ndarray<T>::ndim() const
{
	return shape_.size();
}

template <typename T>
void Ndarray<T>::print_stride()
{
	for (std::size_t elem : stride_)
	{
		std::cout << elem << '\n';
	}
}

template class Ndarray<std::size_t>;