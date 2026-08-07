#pragma once
#include <vector>
#include <cstddef>
#include <algorithm>
#include <typeinfo>
#include <type_traits>
#include <memory>

template <typename T>
class Ndarray
{
public:
	Ndarray(std::vector<std::size_t> shape);
	Ndarray(std::vector<std::size_t> shape, std::vector<T> data);
	Ndarray(std::vector<std::size_t> shape, std::vector<T> data, std::vector<T> stride);

	std::size_t size() const;
	std::size_t ndim() const;
	std::size_t shape_size() const;

	Ndarray<T> copy() const;
	Ndarray<T> reshape(const std::vector<std::size_t> shape) const;
	Ndarray<T> resize(const std::vector<std::size_t> shape);
	Ndarray<T> transpose(const std::vector<std::size_t> shape);

	void fill(const T& value); 
	void print_stride();
	void update_stride();
	void print_elem();
	void print_ndarray() const;
	void print_shape();

	T item(const std::vector<std::size_t> indices) const;
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
	update_stride();
}

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape, std::vector<T> data)
	:shape_(std::move(shape)),
	data_(std::move(data))
{
	update_stride();
}

template <typename T>
Ndarray<T>::Ndarray(std::vector<std::size_t> shape, std::vector<T> data, std::vector<T> stride)
	:shape_(std::move(shape)),
	data_(std::move(data)),
	stride_(std::move(stride))
{
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
std::size_t Ndarray<T>::shape_size() const
{
	std::size_t result = 1;
	for (auto elem : shape_)
	{
		result *= elem;
	}
	return result;
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

	reshaped_ndarr.update_stride();
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

template <typename T>
void Ndarray<T>::print_shape()
{
	for (const T& elem : shape_)
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

// stride-offset 반영된 ndarray print 함수 
template <typename T>
void Ndarray<T>::print_ndarray() const
{
	if (shape_.empty())
	{
		return;
	}

	const std::size_t ndim = this->ndim();

	std::vector<std::size_t> indices(ndim, 0); // 크기가 ndim이고, 모든 원소가 0인 vector 

	std::size_t total = 1;

	// 실제로 출력해야하는 원소의 수; slice 구현 후 data_수와 출력해야하는 수가 다를 수 있다.
	for (auto dim : shape_)
	{
		total *= dim;
	}

	for (std::size_t n = 0; n < total; ++n)
	{
		std::size_t offset = 0;

		for (std::size_t axis = 0; axis < ndim; ++axis)
		{
			offset += indices[axis] * stride_[axis];
		}

		std::cout << data_[offset] << ' ';

		// 한 줄 끝났다면 줄 바꿈 
		if (indices.back() + 1 == shape_.back())
		{
			std::cout << '\n';
		}

		for (std::size_t axis = ndim; axis-- > 0;)
		{
			++indices[axis];

			// 추가로 출력할게 남은 상황인지 확인 
			if (indices[axis] < shape_[axis])
			{
				break; // 더 남았다면 반복문 탈출해서 출력하러 가기
			}
			indices[axis] = 0; // 더 남지 않았다면 다음으로 
		}
	}
	std::cout << "dtype=" << typeid(T).name() << '\n';
}

template <typename T>
T Ndarray<T>::item(const std::vector<std::size_t> indices) const
{
	std::size_t index = 0;
	std::vector<std::size_t> data_copy = data_;

	for (std::size_t i = 0; i < indices.size(); ++i)
	{
		index += indices[i] * stride_[i];
	}
	std::cout << "index:" << index << '\n';
	return data_copy[index];
}

template <typename T>
Ndarray<T> Ndarray<T>::resize(const std::vector<std::size_t> shape)
{	
	std::size_t shape_mul = 1;

	for (auto elem : shape)
	{
		shape_mul *= elem;
	}

	if (shape_mul > shape_size())
	{
		for (std::size_t i = 0; i < shape_mul - shape_size(); ++i)
		{
			data_.push_back(0);
		}
	}
	return reshape(shape);
}

// stride update function: when shape_ is recalculating, this function have to be called
template <typename T>
void Ndarray<T>::update_stride()
{
	stride_.resize(shape_.size());
	
	std::size_t stride = 1;
	for (std::size_t i = shape_.size(); i > 0; i--)
	{
		stride_[i-1] = stride;
		stride *= shape_[i-1];
	}
}

// Returns a view of the array with axes transposed 
template <typename T>
Ndarray<T> Ndarray<T>::transpose(const std::vector<std::size_t> axes)
{
	std::vector<std::size_t> old_shape = shape_;
	std::vector<std::size_t> new_shape;

	std::vector<std::size_t> old_stride = stride_;
	std::vector<std::size_t> new_stride;

	new_shape.reserve(shape_.size());
	new_stride.reserve(stride_.size());

	for (auto i : axes)
	{
		new_shape.push_back(old_shape[i]);
		new_stride.push_back(old_stride[i]);
	}

	Ndarray<T> new_ndarr(new_shape, data_, new_stride);
	return new_ndarr;
}