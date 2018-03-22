#pragma once

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <sstream>

/// <summary>矩阵类，定义了矩阵相关操作。</summary>
/// <typeparam name="T">矩阵元素的数据类型。</typeparam>
template<typename T>
class matrix {
	/// <value>存储矩阵的所有元素。</value>
	std::vector<std::vector<T>> data_;

	/// <value>存储矩阵元素的文本。</value>
	std::vector<std::string> element_texts_;
	
	/// <value>文本表示的矩阵元素的最大长度。</value>
	size_t max_text_size_ = 0;

public:
	/// <summary>默认构造函数，构造一个空矩阵。</summary>
	matrix<T>() {}

	/// <summary>从已存在的矩阵拷贝构造一个新矩阵。</summary>
	/// <param name="mat">待拷贝构造的矩阵。</param>
	matrix<T>(const matrix<T> &mat)
		: data_(mat.data_) {}

	/// <summary>构造一个指定列数和行数的空矩阵。</summary>
	/// <param name="cols">列数。</param>
	/// <param name="rows">行数。</param>
	matrix<T>(const size_t cols, const size_t rows) {
		resize(cols, rows);
	}

	/// <summary>从初始化列表构造矩阵。</summary>
	/// <param name="lists">给定的初始化列表。</param>
	matrix<T>(const std::initializer_list<std::initializer_list<T>> &lists) {
		const size_t max_cols = std::max_element(lists.begin(), lists.end(),
			[](auto a, auto b) {
			return a.size() < b.size();
		})->size();
		resize(max_cols, lists.size());
		size_t i = 0;
		for (auto list : lists) {
			size_t j = 0;
			for (auto element : list)
				data_[i][j++] = element;
			i++;
		}
	}

	/// <summary>从给定的<c>std::vector&lt;T&gt;</c>容器中构造矩阵。</summary>
	/// <param name="data">给定的<c>std::vector&lt;T&gt;</c>容器。</param>
	explicit matrix<T>(const std::vector<std::vector<T>> &data) {
		this->data_ = data;
		const size_t max_cols = std::max_element(this->data_.begin(), this->data_.end(),
			[](auto a, auto b) {
			return a.size() < b.size();
		})->size();
		setcols(max_cols);
	}

	/// <summary>获取矩阵的行数。</summary>
	/// <returns>矩阵的行数。</returns>
	size_t rows() const {
		return data_.size();
	}

	/// <summary>获取矩阵的列数。</summary>
	/// <returns>矩阵的列数。</returns>
	size_t cols() const {
		return data_.empty() ? 0 : data_.front().size();
	}

	/// <summary>设置矩阵的行数。</summary>
	/// <param name="rows">待设置的行数。</param>
	void setrows(size_t rows) {
		const size_t old_rows = this->rows();
		data_.resize(rows);
		for (auto i = old_rows; i < rows; i++)
			data_[i].resize(cols());
	}

	/// <summary>设置矩阵的列数。</summary>
	/// <param name="cols">待设置的列数。</param>
	void setcols(size_t cols) {
		for (size_t i = 0; i < data_.size(); i++)
			data_[i].resize(cols);
	}

	/// <summary>重新调整矩阵的大小。</summary>
	/// <param name="rows">待设置的行数。</param>
	/// <param name="cols">待设置的列数。</param>
	void resize(size_t cols, size_t rows) {
		size_t i = 0;
		for (; i < this->rows(); i++)
			data_[i].resize(cols);
		data_.resize(rows);
		for (; i < this->rows(); i++)
			data_[i].resize(cols);
	}

	/// <summary>将矩阵元素清零。</summary>
	void clear() {
		for (size_t i = 0; i < data_.size(); i++)
			data_[i].clear();
	}

	/// <summary>指示矩阵是否为空。</summary>
	/// <returns>若为空返回<c>true</c>，否则返回<c>false</c>。</returns>
	bool empty() const {
		return data_.empty();
	}

	/// <summary>返回矩阵指定的行。</summary>
	/// <param name="pos">行的下标。</param>
	/// <returns>返回一个存储该行的元素的对象。</returns>
	auto& operator[](const size_t pos) {
		return data_[pos];
	}

	/// <summary>返回矩阵指定的行（只读）。</summary>
	/// <param name="pos">行的下标。</param>
	/// <returns>返回一个存储该行的元素的对象。</returns>
	auto operator[](const size_t pos) const {
		return data_[pos];
	}

	/// <summary>返回两矩阵的和。</summary>
	/// <param name="mat">待相加的右矩阵。</param>
	/// <returns>两矩阵的和。</returns>
	/// <exception cref="std::invalid_argument">当两矩阵非同型时抛出。</exception>
	matrix<T> operator+(const matrix<T> &mat) const {
		matrix<T> result;
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		result.resize(cols(), rows());
		for (size_t i = 0; i < result.rows(); i++)
			for (size_t j = 0; j < result.cols(); j++)
				result.data_[i][j] = data_[i][j] + mat.data_[i][j];
		return result;
	}

	/// <summary>返回两矩阵的差。</summary>
	/// <param name="mat">待相减的右矩阵。</param>
	/// <returns>两矩阵的差。</returns>
	/// <exception cref="std::invalid_argument">当两矩阵非同型时抛出。</exception>
	matrix<T> operator-(const matrix<T> &mat) const {
		matrix<T> result;
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		result.resize(cols(), rows());
		for (size_t i = 0; i < result.rows(); i++)
			for (size_t j = 0; j < result.cols(); j++)
				result.data_[i][j] = data_[i][j] - mat[i][j];
		return result;
	}

	/// <summary>返回两矩阵的积。</summary>
	/// <param name="mat">待相乘的右矩阵。</param>
	/// <returns>两矩阵的积。</returns>
	/// <exception cref="std::invalid_argument">当左矩阵的列数不等于右矩阵的行数时抛出。</exception>
	matrix<T> operator*(const matrix<T> &mat) const {
		matrix<T> result;
		if (cols() != mat.rows())
			throw std::invalid_argument("Left matrix's columns is not equal to right matrix's rows.");
		result.resize(rows(), mat.cols());
		for (size_t i = 0; i < result.rows(); i++)
			for (size_t j = 0; j < result.cols(); j++)
				for (size_t k = 0; k < cols(); k++)
					result.data_[i][j] += data_[i][k] * mat.data_[k][j];
		return result;
	}

	/// <summary>返回矩阵与数的积。</summary>
	/// <param name="value">待相乘的数。</param>
	/// <returns>两矩阵的积。</returns>
	matrix<T> operator*(const T &value) const {
		matrix<T> result(cols(), rows());
		for (size_t i = 0; i < result.rows(); i++)
			for (size_t j = 0; j < result.cols(); j++)
				result[i][j] = data_[i][j] * value;
		return result;
	}

	/// <summary>将矩阵与指定矩阵进行“自增”操作。</summary>
	/// <param name="mat">待相加矩阵。</param>
	/// <returns>被操作矩阵自身。</returns>
	matrix<T>& operator+=(const matrix<T> &mat) {
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				data_[i][j] += mat.data_[i][j];
		return *this;
	}

	/// <summary>将矩阵与指定矩阵进行“自减”操作。</summary>
	/// <param name="mat">待相减矩阵。</param>
	/// <returns>被操作矩阵自身。</returns>
	matrix<T>& operator-=(const matrix<T> &mat) {
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		for (size_t i = 0; i < mat.rows(); i++)
			for (size_t j = 0; j < mat.cols(); j++)
				data_[i][j] -= mat.data_[i][j];
		return *this;
	}

	/// <summary>将矩阵与指定矩阵进行“自乘”操作。</summary>
	/// <param name="mat">待相乘矩阵。</param>
	/// <returns>被操作矩阵自身。</returns>
	matrix<T>& operator*=(const matrix<T> &mat) {
		const matrix<T> result = *this * mat;
		*this = result;
		return *this;
	}

	/// <summary>将矩阵与指定数进行“自乘”操作。</summary>
	/// <param name="mat">待相乘的数。</param>
	/// <returns>被操作矩阵自身。</returns>
	matrix<T>& operator*=(const T &value) {
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				data_[i][j] *= value;
		return *this;
	}

	/// <summary>将矩阵转置。</summary>
	/// <returns>转置后的矩阵。</returns>
	matrix<T> transpose() const {
		matrix<T> result(rows(), cols());
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				result[j][i] = data_[i][j];
		return result;
	}
	
	/// <summary>求矩阵的逆矩阵。</summary>
	/// <returns>被操作矩阵的逆矩阵。</returns>
	matrix<T> inverse() const {
		// TODO
		throw std::logic_error("Unimplemented.");
	}

	/// <summary>返回矩阵的文本表示。列之间使用空格分隔，行之间使用回车分隔。</summary>
	/// <returns>矩阵的文本表示，由数字、空格和回车组成的多行文本。</returns>
	std::string to_string() {
		update_element_texts();
		std::string result;
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++) {
				result += std::string(max_text_size_ - element_texts_[i * cols() + j].size(), ' ');
				result += element_texts_[i * cols() + j];
				if (i != rows() - 1 || j != cols() - 1)
					result += j == cols() - 1 ? '\n' : ' ';
			}
		return result;
	}

	/// <summary>输出由 to_string() 生成的文本到指定的输出流。</summary>
	/// <param name="os">指定的标准输出流。</param>
	/// <param name="mat">待输出的矩阵。</param>
	friend std::ostream& operator<<(std::ostream &os, matrix<T> &mat) {
		const std::ostream::sentry s(os);
		if (s)
			os.write(mat.to_string());
		return os;
	}

	/// <summary>由指定的输入流读入文本生成矩阵，输入格式同 to_string 方法所生成的文本格式。</summary>
	/// <param name="os">指定的标准输入流。</param>
	/// <param name="mat">待输入至的矩阵对象。</param>
	friend std::istream& operator>>(std::istream &is, matrix<T> &mat) {
		const std::istream::sentry s(is);
		if (!s)
			return is;
		if (mat.empty()) {
			std::vector<std::vector<T>> elements;
			std::string line;
			for (size_t i = 0; std::getline(is, line); i++) {
				std::vector<T> v;
				std::stringstream sstream;
				sstream << line;
				T element;
				for (size_t j = 0; sstream >> element; j++)
					v.emplace_back(element);
				elements.emplace_back(v);
			}
			mat = elements;
		}
		else {
			for (size_t i = 0; i < mat.rows(); i++)
				for (size_t j = 0; j < mat.cols(); j++) {
					T element;
					if (!(is >> element))
						throw std::invalid_argument("Too few elements.");
					mat[i][j] = element;
				}
		}
		return is;
	}

private:
	/// <summary>更新矩阵文本。</summary>
	void update_element_texts() {
		// update text
		element_texts_.resize(cols() * rows());
		size_t cur = 0;
		for (auto row : data_)
			for (auto element : row)
				element_texts_[cur++] = std::to_string(element);
		max_text_size_ = std::max_element(element_texts_.begin(), element_texts_.end(),
			[](auto a, auto b) {
			return a.size() < b.size();
		})->size();
	}
};
