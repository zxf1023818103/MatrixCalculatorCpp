#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include "Matrix.h"

/// <summary>��ʾ�������͵�ö���ࡣ</summary>
enum class matrix_type {
	/// <value>�������͵ľ���</value>
	matrix_integer,

	/// <value>���������͵ľ���</value>
	matrix_double
};

/// <summary>��ʾ���������ö����</summary>
enum class matrix_operation {
	/// <value>����ӷ���</value>
	matrix_plus,

	/// <value>���������</value>
	matrix_subtract,

	/// <value>����˷���</value>
	matrix_multiply,

	/// <value>��������˷���</value>
	matrix_scalar_multiply,

	/// <value>����ת�á�</value>
	matrix_transpose,

	/// <value>�������档</value>
	matrix_inverse
};

/// <summary>����������Ĳ����ࡣ</summary>
struct matrix_calculator_args {
	/// <value>�����ļ���·����</value>
	std::string input_file_path;

	/// <value>����ļ���·����</value>
	std::string output_file_path;

	/// <value>��ִ�еĲ�����</value>
	matrix_operation operation;
};

/// <summary>�������������ǲ��֡�</summary> 
/// <typeparam name="T">����Ԫ�ص��������͡�</typeparam>
template<typename T>
class matrix_calculator {
	/// <value>����������Ĳ�����</value>
	matrix_calculator_args args_;

	/// <value>ָ����������ָ�룬Ĭ��Ϊ��׼���롣</value>
	std::istream *ptr_istream_ = &std::cin;

	/// <value>ָ���������ָ�룬Ĭ��Ϊ��׼�����</value>
	std::ostream *ptr_ostream_ = &std::cout;

	/// <value>����������</value>
	matrix<T> a_;
	
	/// <value>������Ҿ���</value>
	matrix<T> b_;

	/// <value>����ı�����</value>
	T value_;

	/// <value>��������</value>
	matrix<T> result_;

public:
	/// <summary>�Ӹ����Ĳ�����������������</summary>
	/// <param name="args">�����Ĳ�����</param>
	explicit matrix_calculator(const matrix_calculator_args &args)
		: args_(args) {
		if (!args.input_file_path.empty())
			ptr_istream_ = new std::ifstream(args.input_file_path);
		if (!args.output_file_path.empty())
			ptr_ostream_ = new std::ofstream(args.output_file_path);
	}

	/// <summary>�����������ͷ���Դ��</summary>
	~matrix_calculator() {
		if (ptr_istream_ == &std::cin)
			delete ptr_istream_;
		if (ptr_ostream_ != &std::cout)
			delete ptr_ostream_;
	}

	/// <summary>��ʼ���㡣</summary>
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
