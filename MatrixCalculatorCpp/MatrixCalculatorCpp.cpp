#include "MatrixCalculator.h"

/// <summary>程序名。</summary>
const char PROGRAM_NAME[] = "matrixcalc";

// TODO: 完成命令行解析模块

matrix_calculator_args parse_cmdline_args(int argc, const char **argv) {
	matrix_calculator_args args;
	
	return args;
}

/// <summary>打印帮助并退出。</summary>
void help() {
	std::cout << "Usage: " << PROGRAM_NAME << " -i <input file> -o <output file> -O <operation>" << std::endl;
}

int main(int argc, const char **argv) {

}
