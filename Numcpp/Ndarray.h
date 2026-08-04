#pragma once
#include <vector>
#include <cstddef>

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

	void print_stride();
private:
	std::vector<T> data_;
	std::vector<std::size_t> shape_;
	std::vector<std::size_t> stride_;
};
