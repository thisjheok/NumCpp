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

	void fill(const T& value); 
	void print_stride();
	void print_elem();
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

template <typename T>
void Ndarray<T>::fill(const T& value)
{
	std::fill(data_.begin(), data_.end(), value);
}

// Debugging function to print the stride of the ndarray
template <typename T>
void Ndarray<T>::print_stride()
{
	for (std::size_t elem : stride_)
	{
		std::cout << elem << ' ';
	}
	std::cout << '\n';
}

// Debugging function to print the element of the ndarray
template <typename T>
void Ndarray<T>::print_elem()
{
	for (std::size_t elem : data_)
	{
		std::cout << elem << ' ';
	}
	std::cout << '\n';
}


// TODO: shape만 형성되어있는 array에 원소 추가하기 
//		 API: empty, zeros, ones, full  
// TODO: 다차원 배열에 특정 원소에 대해서 접근하기 