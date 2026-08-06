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

	std::size_t size() const;
	std::size_t ndim() const;
	std::size_t shape_size() const;

	Ndarray<T> copy() const;
	Ndarray<T> reshape(const std::vector<std::size_t> shape) const;
	Ndarray<T> resize(const std::vector<std::size_t> shape);
	Ndarray<T> tranpose(const std::vector<std::size_t> shape);

	void fill(const T& value); 
	void print_stride();
	void update_stride();
	void print_elem();
	void print_ndarray();

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
Ndarray<T> tranpose(const std::vector<std::size_t> axes)
{

}