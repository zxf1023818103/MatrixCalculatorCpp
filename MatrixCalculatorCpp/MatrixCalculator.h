#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include "Matrix.h"

/// <summary>表示矩阵类型的枚举类。</summary>
enum class matrix_type {
	/// <value>整数类型的矩阵。</value>
	matrix_integer,

	/// <value>浮点数类型的矩阵。</value>
	matrix_double
};

/// <summary>表示矩阵操作的枚举类</summary>
enum class matrix_operation {
	/// <value>矩阵加法。</value>
	matrix_plus,

	/// <value>矩阵减法。</value>
	matrix_subtract,

	/// <value>矩阵乘法。</value>
	matrix_multiply,

	/// <value>矩阵标量乘法。</value>
	matrix_scalar_multiply,

	/// <value>矩阵转置。</value>
	matrix_transpose,

	/// <value>矩阵求逆。</value>
	matrix_inverse
};

/// <summary>矩阵计算器的参数类。</summary>
struct matrix_calculator_args {
	/// <value>输入文件的路径。</value>
	std::string input_file_path;

	/// <value>输出文件的路径。</value>
	std::string output_file_path;

	/// <value>待执行的操作。</value>
	matrix_operation operation;
};

/// <summary>矩阵计算器的外壳部分。</summary> 
/// <typeparam name="T">矩阵元素的数据类型。</typeparam>
template<typename T>
class matrix_calculator {
	/// <value>矩阵计算器的参数。</value>
	matrix_calculator_args args_;

	/// <value>指向输入流的指针，默认为标准输入。</value>
	std::istream *ptr_istream_ = &std::cin;

	/// <value>指向输出流的指针，默认为标准输出。</value>
	std::ostream *ptr_ostream_ = &std::cout;

	/// <value>输入的左矩阵。</value>
	matrix<T> a_;
	
	/// <value>输入的右矩阵。</value>
	matrix<T> b_;

	/// <value>输入的标量。</value>
	T value_;

	/// <value>计算结果。</value>
	matrix<T> result_;

public:
	/// <summary>从给定的参数构造矩阵计算器。</summary>
	/// <param name="args">给定的参数。</param>
	explicit matrix_calculator(const matrix_calculator_args &args)
		: args_(args) {
		if (!args.input_file_path.empty())
			ptr_istream_ = new std::ifstream(args.input_file_path);
		if (!args.output_file_path.empty())
			ptr_ostream_ = new std::ofstream(args.output_file_path);
	}

	/// <summary>析构函数，释放资源。</summary>
	~matrix_calculator() {
		if (ptr_istream_ == &std::cin)
			delete ptr_istream_;
		if (ptr_ostream_ != &std::cout)
			delete ptr_ostream_;
	}

	/// <summary>开始计算。</summary>
	void start() {
		*ptr_istream_ >> a_;
		*ptr_istream_ >> b_;
		switch (args_.operation) {
		case matrix_operation::matrix_plus:
			*ptr_istream_ >> b_;
			result_ = a_ + b_;
			break;
		case matrix_operation::matrix_subtract:
			*ptr_istream_ >> b_;
			result_ = a_ - b_;
			break;
		case matrix_operation::matrix_multiply:
			*ptr_istream_ >> b_;
			result_ = a_ * b_;
			break;
		case matrix_operation::matrix_scalar_multiply:
			*ptr_istream_ >> value_;
			result_ = a_ * value_;
			break;
		case matrix_operation::matrix_transpose:
			result_ = a_.transpose();
			break;
		case matrix_operation::matrix_inverse:
			result_ = a_.inverse();
			break;
		default:
			throw std::invalid_argument("Invalid operation.");
		}
		*ptr_ostream_ << result_ << std::endl;
	}
};
