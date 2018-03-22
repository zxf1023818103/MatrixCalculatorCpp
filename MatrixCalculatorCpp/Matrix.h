#pragma once

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <sstream>

/// <summary>�����࣬�����˾�����ز�����</summary>
/// <typeparam name="T">����Ԫ�ص��������͡�</typeparam>
template<typename T>
class matrix {
	/// <value>�洢���������Ԫ�ء�</value>
	std::vector<std::vector<T>> data_;

	/// <value>�洢����Ԫ�ص��ı���</value>
	std::vector<std::string> element_texts_;
	
	/// <value>�ı���ʾ�ľ���Ԫ�ص���󳤶ȡ�</value>
	size_t max_text_size_ = 0;

public:
	/// <summary>Ĭ�Ϲ��캯��������һ���վ���</summary>
	matrix<T>() {}

	/// <summary>���Ѵ��ڵľ��󿽱�����һ���¾���</summary>
	/// <param name="mat">����������ľ���</param>
	matrix<T>(const matrix<T> &mat)
		: data_(mat.data_) {}

	/// <summary>����һ��ָ�������������Ŀվ���</summary>
	/// <param name="cols">������</param>
	/// <param name="rows">������</param>
	matrix<T>(const size_t cols, const size_t rows) {
		resize(cols, rows);
	}

	/// <summary>�ӳ�ʼ���б������</summary>
	/// <param name="lists">�����ĳ�ʼ���б�</param>
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

	/// <summary>�Ӹ�����<c>std::vector&lt;T&gt;</c>�����й������</summary>
	/// <param name="data">������<c>std::vector&lt;T&gt;</c>������</param>
	explicit matrix<T>(const std::vector<std::vector<T>> &data) {
		this->data_ = data;
		const size_t max_cols = std::max_element(this->data_.begin(), this->data_.end(),
			[](auto a, auto b) {
			return a.size() < b.size();
		})->size();
		setcols(max_cols);
	}

	/// <summary>��ȡ�����������</summary>
	/// <returns>�����������</returns>
	size_t rows() const {
		return data_.size();
	}

	/// <summary>��ȡ�����������</summary>
	/// <returns>�����������</returns>
	size_t cols() const {
		return data_.empty() ? 0 : data_.front().size();
	}

	/// <summary>���þ����������</summary>
	/// <param name="rows">�����õ�������</param>
	void setrows(size_t rows) {
		const size_t old_rows = this->rows();
		data_.resize(rows);
		for (auto i = old_rows; i < rows; i++)
			data_[i].resize(cols());
	}

	/// <summary>���þ����������</summary>
	/// <param name="cols">�����õ�������</param>
	void setcols(size_t cols) {
		for (size_t i = 0; i < data_.size(); i++)
			data_[i].resize(cols);
	}

	/// <summary>���µ�������Ĵ�С��</summary>
	/// <param name="rows">�����õ�������</param>
	/// <param name="cols">�����õ�������</param>
	void resize(size_t cols, size_t rows) {
		size_t i = 0;
		for (; i < this->rows(); i++)
			data_[i].resize(cols);
		data_.resize(rows);
		for (; i < this->rows(); i++)
			data_[i].resize(cols);
	}

	/// <summary>������Ԫ�����㡣</summary>
	void clear() {
		for (size_t i = 0; i < data_.size(); i++)
			data_[i].clear();
	}

	/// <summary>ָʾ�����Ƿ�Ϊ�ա�</summary>
	/// <returns>��Ϊ�շ���<c>true</c>�����򷵻�<c>false</c>��</returns>
	bool empty() const {
		return data_.empty();
	}

	/// <summary>���ؾ���ָ�����С�</summary>
	/// <param name="pos">�е��±ꡣ</param>
	/// <returns>����һ���洢���е�Ԫ�صĶ���</returns>
	auto& operator[](const size_t pos) {
		return data_[pos];
	}

	/// <summary>���ؾ���ָ�����У�ֻ������</summary>
	/// <param name="pos">�е��±ꡣ</param>
	/// <returns>����һ���洢���е�Ԫ�صĶ���</returns>
	auto operator[](const size_t pos) const {
		return data_[pos];
	}

	/// <summary>����������ĺ͡�</summary>
	/// <param name="mat">����ӵ��Ҿ���</param>
	/// <returns>������ĺ͡�</returns>
	/// <exception cref="std::invalid_argument">���������ͬ��ʱ�׳���</exception>
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

	/// <summary>����������Ĳ</summary>
	/// <param name="mat">��������Ҿ���</param>
	/// <returns>������Ĳ</returns>
	/// <exception cref="std::invalid_argument">���������ͬ��ʱ�׳���</exception>
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

	/// <summary>����������Ļ���</summary>
	/// <param name="mat">����˵��Ҿ���</param>
	/// <returns>������Ļ���</returns>
	/// <exception cref="std::invalid_argument">�������������������Ҿ��������ʱ�׳���</exception>
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

	/// <summary>���ؾ��������Ļ���</summary>
	/// <param name="value">����˵�����</param>
	/// <returns>������Ļ���</returns>
	matrix<T> operator*(const T &value) const {
		matrix<T> result(cols(), rows());
		for (size_t i = 0; i < result.rows(); i++)
			for (size_t j = 0; j < result.cols(); j++)
				result[i][j] = data_[i][j] * value;
		return result;
	}

	/// <summary>��������ָ��������С�������������</summary>
	/// <param name="mat">����Ӿ���</param>
	/// <returns>��������������</returns>
	matrix<T>& operator+=(const matrix<T> &mat) {
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				data_[i][j] += mat.data_[i][j];
		return *this;
	}

	/// <summary>��������ָ��������С��Լ���������</summary>
	/// <param name="mat">���������</param>
	/// <returns>��������������</returns>
	matrix<T>& operator-=(const matrix<T> &mat) {
		if (rows() != mat.rows() || cols() != mat.cols())
			throw std::invalid_argument("Non-homogeneous matrix.");
		for (size_t i = 0; i < mat.rows(); i++)
			for (size_t j = 0; j < mat.cols(); j++)
				data_[i][j] -= mat.data_[i][j];
		return *this;
	}

	/// <summary>��������ָ��������С��Գˡ�������</summary>
	/// <param name="mat">����˾���</param>
	/// <returns>��������������</returns>
	matrix<T>& operator*=(const matrix<T> &mat) {
		const matrix<T> result = *this * mat;
		*this = result;
		return *this;
	}

	/// <summary>��������ָ�������С��Գˡ�������</summary>
	/// <param name="mat">����˵�����</param>
	/// <returns>��������������</returns>
	matrix<T>& operator*=(const T &value) {
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				data_[i][j] *= value;
		return *this;
	}

	/// <summary>������ת�á�</summary>
	/// <returns>ת�ú�ľ���</returns>
	matrix<T> transpose() const {
		matrix<T> result(rows(), cols());
		for (size_t i = 0; i < rows(); i++)
			for (size_t j = 0; j < cols(); j++)
				result[j][i] = data_[i][j];
		return result;
	}
	
	/// <summary>�����������</summary>
	/// <returns>����������������</returns>
	matrix<T> inverse() const {
		// TODO
		throw std::logic_error("Unimplemented.");
	}

	/// <summary>���ؾ�����ı���ʾ����֮��ʹ�ÿո�ָ�����֮��ʹ�ûس��ָ���</summary>
	/// <returns>������ı���ʾ�������֡��ո�ͻس���ɵĶ����ı���</returns>
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

	/// <summary>����� to_string() ���ɵ��ı���ָ�����������</summary>
	/// <param name="os">ָ���ı�׼�������</param>
	/// <param name="mat">������ľ���</param>
	friend std::ostream& operator<<(std::ostream &os, matrix<T> &mat) {
		const std::ostream::sentry s(os);
		if (s)
			os.write(mat.to_string());
		return os;
	}

	/// <summary>��ָ���������������ı����ɾ��������ʽͬ to_string ���������ɵ��ı���ʽ��</summary>
	/// <param name="os">ָ���ı�׼��������</param>
	/// <param name="mat">���������ľ������</param>
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
	/// <summary>���¾����ı���</summary>
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
