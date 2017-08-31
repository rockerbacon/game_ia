#ifndef _LAB309_ADT_MATRIX_H_
#define _LAB309_ADT_MATRIX_H_

#include <stdlib.h>
#include <iostream>
#include <stdexcept>

namespace lab309 {

	template<typename dataType>
	class Matrix {
		private:
			dataType *data;
			size_t lines;
			size_t colums;
			bool selfAllocated;

		public:
			//constructors and destructor
			Matrix (void);
			explicit Matrix (size_t lines, size_t colums) throw (std::invalid_argument, std::bad_alloc);
			explicit Matrix (size_t n) throw (std::invalid_argument, std::bad_alloc) : Matrix(n, n) {}
			explicit Matrix (dataType *pointer, size_t lines, size_t colums) throw (std::invalid_argument);
			explicit Matrix (dataType *pointer, size_t n) throw (std::invalid_argument) : Matrix(pointer, n, n) {}
			Matrix (const std::initializer_list<std::initializer_list<dataType>> &matrix) throw (std::invalid_argument, std::bad_alloc);
			Matrix (const Matrix<dataType> &matrix) throw (std::bad_alloc);
			Matrix (Matrix<dataType> &&matrix);
			~Matrix(void);

			//getters
			inline size_t getLines (void) const {
				return this->lines;
			}

			inline size_t getColums (void) const {
				return this->colums;
			}

			inline const dataType& getDataAt (size_t line, size_t colum) const {
				return this->data[line*this->colums + colum];
			}

			inline dataType& referenceDataAt (size_t line, size_t colum) {
				return this->data[line*this->colums + colum];
			}

			//methods
			Matrix<dataType> transpose (void) const throw (std::bad_alloc);

			std::ostream& toStream (std::ostream &stream) const;

			Matrix<dataType>& setIdentity (void);

			inline Matrix<dataType> copy (void) const throw (std::bad_alloc) {
				try {
					return Matrix<dataType>(*this);	//possible std::bad_alloc throw
				} catch (std::bad_alloc &error) {
					throw error;
				}
			}

			Matrix<dataType>& map (size_t istart, size_t iend, size_t jstart, size_t jend, void (*function)(dataType*, std::initializer_list<void*>), const std::initializer_list<void*> &args);
			inline Matrix<dataType>& map (void (*function)(dataType*, std::initializer_list<void*>), const std::initializer_list<void*> &args) {
				return this->map(0, this->lines, 0, this->colums, function, args);
			} 

			//operators
			//array subscripting
			inline dataType* operator[] (size_t line) {
				return this->data + line*this->colums;
			}
			inline const dataType* operator[] (size_t line) const {
				return this->data + line*this->colums;
			}

			//assignment
			Matrix<dataType>& operator= (const Matrix<dataType> &matrix) throw (std::bad_alloc);
			Matrix<dataType>& operator= (Matrix<dataType> &&matrix);

			//comparison
			bool operator== (const Matrix<dataType> &matrix) const;
			inline bool operator!= (const Matrix<dataType> &matrix) const {
				return !(*this == matrix);
			}

			//multiplication
			Matrix<dataType> operator* (dataType scalar) const throw (std::bad_alloc);
			Matrix<dataType> operator* (const Matrix<dataType> &matrix) const throw (std::invalid_argument, std::bad_alloc);

			//sum
			Matrix<dataType> operator+ (const Matrix<dataType> &matrix) const throw (std::invalid_argument, std::bad_alloc);

	};

	template<typename dataType>
	class Array : public Matrix<dataType> {
		public:
			//constructors and destructor
			Array (void) = default;
			explicit Array (size_t n) throw (std::invalid_argument, std::bad_alloc) : Matrix<dataType>(n, 1) {}
			explicit Array (dataType *pointer, size_t n) throw (std::invalid_argument, std::bad_alloc) : Matrix<dataType>(pointer, n, 1) {}
			Array (const std::initializer_list<dataType> &array) throw (std::bad_alloc);
			Array (const Array<dataType> &array) throw (std::bad_alloc) : Matrix<dataType>(array) {}
			Array (Array<dataType> &&array) : Matrix<dataType>(array) {}
			~Array (void) = default;

			//operators
			//array subscripting
			inline dataType& operator[] (size_t index) {
				return this->referenceDataAt(index, 0);
			}
			inline const dataType& operator[] (size_t index) const {
				return this->getDataAt(index, 0);
			}

			//assignment
			inline Array<dataType>& operator= (const Array<dataType> &array) throw (std::bad_alloc) {
				try {
					return Matrix<dataType>::operator=(array);	//possible std::bad_alloc throw
				} catch (std::bad_alloc &error) {
					throw error;
				}
			}

			inline Array<dataType>& operator= (Array<dataType> &&array) {
				try {
					return Matrix<dataType>::operator=(array);
				} catch (std::bad_alloc &error) {
					throw error;
				}
			}
	};

}

template<typename dataType>
inline std::ostream& operator<< (std::ostream &stream, const lab309::Matrix<dataType> &matrix) {
	return matrix.toStream(stream);
}

/*IMPLEMENTATION*/
/*MATRIX*/
/*CONSTRUCTORS AND DESTRUCTOR*/
template<typename dataType>
lab309::Matrix<dataType>::Matrix (void) {
	this->data = NULL;
	this->lines = 0;
	this->colums = 0;
}

template<typename dataType>
lab309::Matrix<dataType>::Matrix (size_t lines, size_t colums) throw (std::invalid_argument, std::bad_alloc) {
	try {
		if (lines != 0 && colums == 0 || lines == 0 && colums != 0) {
			throw std::invalid_argument("Error on: Matrix::Matrix (size_t lines, size_t colums): cannot have lines without colums and vice-versa");
		}
		this->lines = lines;
		this->colums = colums;
		this->data = (dataType*)malloc(lines*colums*sizeof(dataType));
		if (this->data == NULL) {
			throw std::bad_alloc();
		}
		this->selfAllocated = true;
	} catch (std::invalid_argument &error) {
		throw error;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

template<typename dataType>
lab309::Matrix<dataType>::Matrix (dataType *pointer, size_t lines, size_t colums) throw (std::invalid_argument) {
	try {
		if (pointer == NULL && lines != 0 && colums != 0) {
			throw std::invalid_argument("Error on: Matrix::Matrix(dataType *pointer, size_t lines, size_t colums): pointer cannot be NULL");
		} else if (lines != 0 && colums == 0 || lines == 0 && colums != 0) {
			throw std::invalid_argument("Error on: Matrix::Matrix(dataType *pointer, size_t lines, size_t colums): cannot have lines without colums and vice-versa");
		}
		this->lines = lines;
		this->colums = colums;
		this->data = pointer;
		this->selfAllocated = false;
	} catch (std::invalid_argument &error) {
		throw error;
	}
}

template<typename dataType>
lab309::Matrix<dataType>::Matrix (const std::initializer_list<std::initializer_list<dataType>> &matrix) throw (std::invalid_argument, std::bad_alloc) : Matrix(matrix.size(), matrix.begin()->size()) {
	const std::initializer_list<dataType> *i;
	const dataType *j;
	size_t k;

	try {
		k = 0;
		for (i = matrix.begin(); i != matrix.end(); i++) {
			if (i->size() != this->colums) {
				throw std::invalid_argument("Error on: Matrix::Matrix(const std::initializer_list<std::initializer_list<dataType>> &matrix): invalid size on initializer list");
			}
			for (j = i->begin(); j != i->end(); j++) {
				this->data[k] = *j;
				k++;
			}
		}
	} catch (std::invalid_argument &error) {
		throw error;
	}
}

template<typename dataType>
lab309::Matrix<dataType>::Matrix (const Matrix<dataType> &matrix) throw (std::bad_alloc) : Matrix(matrix.lines, matrix.colums) {
	size_t i;
	const size_t range = matrix.lines*matrix.colums;
	for (i = 0; i < range; i++) {
		this->data[i] = matrix.data[i];
	}
}

template<typename dataType>
lab309::Matrix<dataType>::Matrix (Matrix<dataType> &&matrix) {

	this->lines = matrix.lines;
	this->colums = matrix.colums;

	this->data = matrix.data;
	this->selfAllocated = matrix.selfAllocated;

	matrix.data = NULL;

}

template<typename dataType>
lab309::Matrix<dataType>::~Matrix (void) {
	if (this->selfAllocated) {
		free(this->data);
	}
}

/*METHODS*/
template<typename dataType>
lab309::Matrix<dataType> lab309::Matrix<dataType>::transpose (void) const throw (std::bad_alloc) {
	size_t i, j;
	dataType *transposeLine, *thisLine;
	try {
		Matrix<dataType> transpose(this->colums, this->lines);	//possible std::bad_alloc throw

		for (i = 0; i < this->lines; i++) {
			thisLine = this->data + i*this->colums;
			transposeLine = transpose.data + i;
			for (j = 0; j < this->colums; j++) {
				transposeLine[j*this->lines] = thisLine[j];
			}
		}

		return transpose;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

template<typename dataType>
std::ostream& lab309::Matrix<dataType>::toStream (std::ostream &stream) const {
	size_t i, j;
	dataType *thisLine;

	stream << '[';
	for (i = 0; i < this->lines; i++) {
		thisLine = this->data + i*this->colums;
		stream << '[';
		for (j = 0; j < this->colums-1; j++) {
			stream << thisLine[j] << ", ";
		}
		stream << thisLine[j] << ']';
		if (i != this->lines-1) {
			stream << "\n ";
		}
	}
	stream << ']';

	return stream;
}

template<typename dataType>
lab309::Matrix<dataType>& lab309::Matrix<dataType>::setIdentity (void) {
	size_t i, j;
	dataType *thisLine;

	for (i = 0; i < this->lines; i++) {
		thisLine = this->data + i*this->colums;
		for (j = 0; j < this->colums; j++) {
			if (i != j) {
				thisLine[j] = 0;
			} else {
				thisLine[j] = 1;
			}
		}
	}

	return *this;
}

template<typename dataType>
lab309::Matrix<dataType>& lab309::Matrix<dataType>::map (size_t istart, size_t iend, size_t jstart, size_t jend, void (*function)(dataType*, std::initializer_list<void*>), const std::initializer_list<void*> &args) {

	dataType *thisLine;
	size_t i, j;

	for (i = istart; i < iend; i++) {
		thisLine = this->data + i*this->colums;
		for (j = jstart; j < jend; j++) {
			function(thisLine+j, args);
		}
	}

	return *this;
}

/*OPERATORS*/
//ASSIGNMENT
template<typename dataType>
lab309::Matrix<dataType>& lab309::Matrix<dataType>::operator= (const Matrix<dataType> &matrix) throw (std::bad_alloc) {
	dataType *aux;
	try {
		Matrix<dataType> copy(matrix);	//possible std::bad_alloc throws

		this->lines = copy.lines;
		this->colums = copy.colums;

		if (this->data != matrix.data) {
			aux = this->data;
			this->data = copy.data;
			copy.data = aux;

			copy.selfAllocated = this->selfAllocated;
			this->selfAllocated = true;
		}

		return *this;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

template<typename dataType>
lab309::Matrix<dataType>& lab309::Matrix<dataType>::operator= (Matrix<dataType> &&matrix) {
	dataType *aux;

	this->lines = matrix.lines;
	this->colums = matrix.colums;

	if (this->selfAllocated && this->data != matrix.data) {
		aux = this->data;
		this->data = matrix.data;
		matrix.data = aux;
		matrix.selfAllocated = true;
	} else {
		this->data = matrix.data;
		matrix.data = NULL;
	}

	return *this;
}

//COMPARISON
template<typename dataType>
bool lab309::Matrix<dataType>::operator== (const Matrix<dataType> &matrix) const {
	const size_t range = this->lines*this->colums;
	size_t i;

	if (this->lines != matrix.lines || this->colums != matrix.colums) {
		return false;
	}
	for (i = 0; i < range; i++) {
		if (this->data[i] != matrix.data[i]) {
			return false;
		}
	}
	return true;
}

//MULTIPLICATION
template<typename dataType>
lab309::Matrix<dataType> lab309::Matrix<dataType>::operator* (dataType scalar) const throw (std::bad_alloc) {
	const size_t range = this->lines*this->colums;
	size_t i;
	try {
		Matrix<dataType> result(this->lines, this->colums);	//possible std::bad_alloc throw

		for (i = 0; i < range; i++) {
			result.data[i] = scalar*this->data[i];
		}

		return result;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

template<typename dataType>
lab309::Matrix<dataType> lab309::Matrix<dataType>::operator* (const Matrix<dataType> &matrix) const throw (std::invalid_argument, std::bad_alloc) {
	size_t i, j, k;
	dataType *resultAddress, *thisLine, *transposeLine;
	try {
		if (this->lines != matrix.colums) {
			throw std::invalid_argument("Error on: Matrix::operator*(const Matrix<dataType> &matrix): matrix's colums must match this matrix's lines");
		}

		Matrix<dataType> transpose = matrix.transpose();		//possible std::bad_alloc throw
		Matrix<dataType> result(this->lines, transpose.lines);	//possible std::bad_alloc throw

		for (i = 0; i < this->lines; i++) {
			for (j = 0; j < transpose.lines; j++) {

				resultAddress = result.data + i*result.colums + j;
				thisLine = this->data + i*this->colums;
				transposeLine = transpose.data + j*transpose.colums;

				*resultAddress = 0;
				for (k = 0; k < this->colums; k++) {
					*resultAddress += thisLine[k]*transposeLine[k];
				}

			}
		}

		return result;
	} catch (std::invalid_argument &error) {
		throw error;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

//SUM
template<typename dataType>
lab309::Matrix<dataType> lab309::Matrix<dataType>::operator+ (const Matrix<dataType> &matrix) const throw (std::invalid_argument, std::bad_alloc) {
	const size_t range = this->lines*this->colums;
	size_t i;
	try {
		if (this->lines != matrix.lines || this->colums != matrix.colums) {
			throw std::invalid_argument("Error on: Matrix::operator+(const Matrix<dataType> &matrix): matrix's lines and colums must match with this matrix's lines and colums");
		}
		Matrix<dataType> result(this->lines, this->colums);	//possible std::bad_alloc throw

		for (i = 0; i < range; i++) {
			result.data[i] = this->data[i]+matrix.data[i];
		}
		
		return result;
	} catch (std::invalid_argument &error) {
		throw error;
	} catch (std::bad_alloc &error) {
		throw error;
	}
}

/*ARRAY*/
/*CONSTRUCTORS*/
template<typename dataType>
lab309::Array<dataType>::Array (const std::initializer_list<dataType> &array) throw (std::bad_alloc) : Matrix<dataType>(array.size(), 1) {
	const dataType *i;
	size_t j;

	j = 0;
	for (i = array.begin(); i != array.end(); i++) {
		this->referenceDataAt(j, 0) = *i;
		j++;
	}
}

#endif
