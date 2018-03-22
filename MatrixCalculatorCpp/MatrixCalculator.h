#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include "Matrix.h"

/// <summary>矩阵计算器的参数类。</summary>
struct matrix_calculator_args {
	/// <value>输入文件的路径。</value>
	std::string input_file_path;

	/// <value>输出文件的路径。</value>
	std::string output_file_path;
};

/// <summary>矩阵计算器的外壳部分。</summary>
class matrix_calculator {
	/// <value>矩阵计算器的参数。</value>
	matrix_calculator_args args_;

	/// <value>指向输入流的指针，默认为标准输入。</value>
	std::istream *ptr_istream_ = &std::cin;

	/// <value>指向输出流的指针，默认为标准输出。</value>
	std::ostream *ptr_ostream_ = &std::cout;

public:
	/// <value>程序名。</value>
	const char PROGRAM_NAME[] = "matrixcalc";

	/// <summary>默认空构造函数。</summary>
	matrix_calculator() {}

	/// <summary>从给定的参数构造矩阵计算器。</summary>
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

	/// <summary>显示帮助。</summary>
	void help() const {
		std::cout << "Usage: " << PROGRAM_NAME << " -i <input file> -o <output file>" << std::endl;
	}

	/// <summary>解析命令行参数。</summary>
	/// <returns>解析得到的参数。若没有指定参数或解析时发生错误，对应的值为空。</returns>
	/// <param name="argc">命令行参数个数</param>
	/// <param name="argv">存储命令行参数的数组。</param>
	/// <exception cref="std::invalid_argument">当缺少参数或解析发生错误时抛出。</exception>
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

	/// <summary>开始计算。</summary>
	void start() {
		
	}
};
