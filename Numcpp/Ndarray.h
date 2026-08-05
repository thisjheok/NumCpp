#pragma once
#include <vector>
#include <cstddef>
#include <algorithm>

// ndarray의 사이즈, 생성자, n번째 원소에 접근, 출력, 범위 검사
// ndarry 생성 시 몇차원인지 어떻게 파악할까 => shape 
template <typename T>
class Ndarray
{
public:
	Ndarray(std::vector<std::size_t> shape);
	Ndarray(std::vector<std::size_t> shape, std::vector<T> data);

	std::size_t size() const;
	std::size_t ndim() const;

	Ndarray<T> copy() const;
	Ndarray<T> reshape(const std::vector<std::size_t> shape) const;

	void fill(const T& value); 
	void print_stride();
	void print_elem();
	void print_ndarray();
private:
	std::vector<T> data_;
	std::vector<std::size_t> shape_;
	std::vector<std::size_t> stride_;
};

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape)
	:shape_(std::move(shape))
{
	int data_size = 1;
	for (std::size_t elem : shape_)
	{
		data_size *= elem;
	}
	data_.resize(data_size);
}

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape, std::vector<T> data)
	:shape_(std::move(shape)),
	data_(std::move(data))
{
	stride_.reserve(shape_.size());
	for (std::size_t i = shape_.size(); i > 0; --i)// i: 3, 2, 1
	{
		std::size_t stride_elem = 1;
		for (int j = 0; j < i - 1; ++j) // i:3, j:0,1 | i:2, j:0 
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

// Fill the array with a scalar value.
template <typename T>
void Ndarray<T>::fill(const T& value)
{
	std::fill(data_.begin(), data_.end(), value);
}

// Return a copy of the array.
template <typename T>
Ndarray<T> Ndarray<T>::copy() const
{
	return *this;
}

// Returns an array containing the same data with a new shape.
template <typename T>
Ndarray<T> Ndarray<T>::reshape(const std::vector<std::size_t> shape) const
{
	auto reshaped_ndarr = *this;
	
	reshaped_ndarr.shape_ = shape;

	return reshaped_ndarr;
}


// Debugging function to print the stride of the ndarray
template <typename T>
void Ndarray<T>::print_stride()
{
	for (const T& elem : stride_)
	{
		std::cout << elem << ' ';
	}
	std::cout << '\n';
}

// Debugging function to print the element of the ndarray
template <typename T>
void Ndarray<T>::print_elem()
{
	for (const T& elem : data_)
	{
		std::cout << elem << ' ';
	}
	std::cout << '\n';
}

template <typename T>
void Ndarray<T>::print_ndarray()
{
	std::vector<T> data = this->data_;
	std::vector<std::size_t> shape = this->shape_;

	std::size_t bundle = 0;
	if (!shape.empty())
	{
		bundle = shape.back();
	}
	else {
		// TODO: exception
	}
	std::size_t count = 0;
	for (const T& elem : data)
	{
		std::cout << elem << ' ';
		count++;
		if (count == bundle)
		{
			std::cout << '\n';
			count = 0;
		}
	}

}

// TODO: shape만 형성되어있는 array에 원소 추가하기 
//		 API: empty, zeros, ones, full  
// TODO: 다차원 배열에 특정 원소에 대해서 접근하기 