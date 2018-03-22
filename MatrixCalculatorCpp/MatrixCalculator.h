#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include "Matrix.h"

/// <summary>����������Ĳ����ࡣ</summary>
struct matrix_calculator_args {
	/// <value>�����ļ���·����</value>
	std::string input_file_path;

	/// <value>����ļ���·����</value>
	std::string output_file_path;
};

/// <summary>�������������ǲ��֡�</summary>
class matrix_calculator {
	/// <value>����������Ĳ�����</value>
	matrix_calculator_args args_;

	/// <value>ָ����������ָ�룬Ĭ��Ϊ��׼���롣</value>
	std::istream *ptr_istream_ = &std::cin;

	/// <value>ָ���������ָ�룬Ĭ��Ϊ��׼�����</value>
	std::ostream *ptr_ostream_ = &std::cout;

public:
	/// <value>��������</value>
	const char PROGRAM_NAME[] = "matrixcalc";

	/// <summary>Ĭ�Ͽչ��캯����</summary>
	matrix_calculator() {}

	/// <summary>�Ӹ����Ĳ�����������������</summary>
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

	/// <summary>��ʾ������</summary>
	void help() const {
		std::cout << "Usage: " << PROGRAM_NAME << " -i <input file> -o <output file>" << std::endl;
	}

	/// <summary>���������в�����</summary>
	/// <returns>�����õ��Ĳ�������û��ָ�����������ʱ�������󣬶�Ӧ��ֵΪ�ա�</returns>
	/// <param name="argc">�����в�������</param>
	/// <param name="argv">�洢�����в��������顣</param>
	/// <exception cref="std::invalid_argument">��ȱ�ٲ����������������ʱ�׳���</exception>
	void parse_cmdline_args(int argc, const char **argv) {
		std::vector<std::string> v_arg;
		for (size_t i = 0; i < argc; i++)
			v_arg.emplace_back(argv[i]);
		const auto it_opt_h = std::find_if(v_arg.begin(), v_arg.end(), [](const std::string &s) {
			return s == "-h";
		});
		const auto it_opt_i = std::find_if(v_arg.begin(), v_arg.end(), [](const std::string &s) {
			return s == "-i";
		});
		const auto it_opt_o = std::find_if(v_arg.begin(), v_arg.end(), [](const std::string &s) {
			return s == "-o";
		});
		if (it_opt_h != v_arg.end())
			help();
		else if (v_arg.size() == 1 || it_opt_i == v_arg.end() || it_opt_o == v_arg.end())
			throw std::invalid_argument("No options provided.");
		else if (std::abs(std::distance(it_opt_i, it_opt_o)) != 2
			&& (std::distance(it_opt_i, v_arg.end()) == 2 || std::distance(it_opt_o, v_arg.end()) == 2)
			|| (it_opt_i + 1)->front() == '-' && (it_opt_i + 1)->size() != 1
			|| (it_opt_o + 1)->front() == '-' && (it_opt_o + 1)->size() != 1)
			throw std::invalid_argument("invalid options.");
		else if (std::distance(it_opt_i, v_arg.end()) == 1)
			throw std::invalid_argument("No input file provided.");
		else if (std::distance(it_opt_o, v_arg.end()) == 1)
			throw std::invalid_argument("No output file provided.");
		else {
			args_.input_file_path = *(it_opt_i + 1);
			args_.output_file_path = *(it_opt_o + 1);
		}
		if (args_.input_file_path == "-")
			args_.input_file_path.clear();
		if (args_.output_file_path == "-")
			args_.output_file_path.clear();
	}

	/// <summary>��ʼ���㡣</summary>
	void start() {
		
	}
};
