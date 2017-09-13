#ifndef _LAB309_OPENGL_VERTICE_H_
#define _LAB309_OPENGL_VERTICE_H_

#include <stdlib.h>
#include <initializer_list>
#include <stdio.h>
#include <iostream>

#define COORDINATE_X 0
#define COORDINATE_Y 1
#define COORDINATE_Z 2
#define COORDINATE_W 3

#define Vertex_3d Vertex<3>
#define Vertex_2d Vertex<2>

#define Vector Vertex
#define Vector_3d Vertex_3d
#define Vector_2d Vertex_2d

namespace lab309 {

	template <size_t numberOfDimensions>
	class Vertex {
		static_assert(numberOfDimensions != 0, "Cannot have vertex with 0 dimensions");

		template<size_t any> friend class Vertex;

		/*ATTRIBUTES*/
		private:
			float coordinate[numberOfDimensions];

		public:
			/*CONSTRUCTORS*/
			Vertex (void) = default;
			Vertex (const float (&coordinate)[numberOfDimensions]);
			template <typename... Coordinates> Vertex (Coordinates... coordinates);
			Vertex (const Vertex<numberOfDimensions> &vertex);
			Vertex (const std::initializer_list<float> &coordinates);

			/*GETTERS*/
			size_t getNumberOfDimensions (void) const;
			float getCoordinate (size_t coordinate) const;
			
			float& operator[] (size_t index);
			const float& operator[] (size_t index) const;

			/*SETTERS*/
			Vertex& setCoordinate (size_t coordinate, float value);

			/*OPERATORS*/
			//SUM
			Vertex& operator+= (const Vertex<numberOfDimensions> &b);
			Vertex operator+ (const Vertex<numberOfDimensions> &b) const;

			Vertex& operator-= (const Vertex<numberOfDimensions> &b);
			Vertex operator- (const Vertex<numberOfDimensions> &b) const;

			//MULTIPLICATION
			Vertex& operator*= (const Vertex<numberOfDimensions> &b);
			Vertex operator* (const Vertex<numberOfDimensions> &b) const;

			Vertex& operator/= (const Vertex<numberOfDimensions> &b);
			Vertex operator/ (const Vertex<numberOfDimensions> &b) const;
			
			Vertex operator- (void) const;

			//COMPARISON
			bool operator== (const Vertex<numberOfDimensions> &b) const;
			bool operator!= (const Vertex<numberOfDimensions> &b) const;
			
			//CASTS
			template<size_t otherNumberOfDimensions> operator Vertex<otherNumberOfDimensions>(void) const	{	return Vertex<otherNumberOfDimensions>();	}

	};
	
	//SCALAR MULTIPLICATION
	template<size_t numberOfDimensions>
	Vertex<numberOfDimensions> operator* (float scalar, const Vertex<numberOfDimensions>& vertex);
	
	//IOSTREAM
	template<size_t numberOfDimensions>
	std::ostream& operator<< (std::ostream &stream, const Vertex<numberOfDimensions> &vertex);
	
	/*FORWARD DECLARATIONS*/
	/*VERTEX_2D*/
	template<> template<>
	Vertex_2d::operator Vertex_3d (void) const;
	/*VERTEX_3D*/
	template<> template<>
	Vertex_3d::operator Vertex_2d (void) const;

}

/*IMPLEMENTATION*/
/*VERTICE*/
/*CONSTRUCTORS*/
template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>::Vertex (const float (&coordinate)[numberOfDimensions]) {
	size_t i;
	for (i=0; i < numberOfDimensions; i++) {
		this->coordinate[i] = coordinate[i];
	}
}

template <size_t numberOfDimensions> template <typename... Coordinates>
lab309::Vertex<numberOfDimensions>::Vertex (Coordinates... coordinates) {
	static_assert (sizeof...(coordinates) == numberOfDimensions, "Number of coordinates passed differ from number of coordinates required");

	std::initializer_list<float> list = {coordinates...};
	const float *listIterator = list.begin();
	const float *end = list.end();
	float *channelIterator = this->coordinate;

	while (listIterator < end) {
		*channelIterator = *listIterator;
		listIterator++;
		channelIterator++;
	}
}

template<size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>::Vertex (const Vertex<numberOfDimensions> &vertex) : Vertex<numberOfDimensions>(vertex.coordinate) {}

template<size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>::Vertex (const std::initializer_list<float> &list) {
	const float *listIterator = list.begin();
	const float *end = list.end();
	float *channelIterator = this->coordinate;

	while (listIterator < end) {
		*channelIterator = *listIterator;
		listIterator++;
		channelIterator++;
	}
}

/*GETTERS*/
template <size_t numberOfDimensions>
size_t lab309::Vertex<numberOfDimensions>::getNumberOfDimensions (void) const {
	return numberOfDimensions;
}

template <size_t numberOfDimensions>
float lab309::Vertex<numberOfDimensions>::getCoordinate (size_t coordinate) const {
	return this->coordinate[coordinate];
}

template <size_t numberOfDimensions>
float& lab309::Vertex<numberOfDimensions>::operator[] (size_t index) {
	//printf("%f\n", this->vertex[index]);	//debug
	return this->coordinate[index];
}

template <size_t numberOfDimensions>
const float& lab309::Vertex<numberOfDimensions>::operator[] (size_t index) const {
	return this->coordinate[index];
}

/*SETTERS*/
template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>& lab309::Vertex<numberOfDimensions>::setCoordinate (size_t coordinate, float value) {
	this->coordinate[coordinate] = value;
	return *this;
}

/*OPERATORS*/
//SUM
template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>& lab309::Vertex<numberOfDimensions>::operator+= (const Vertex<numberOfDimensions> &b) {
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		this->coordinate[i] += b.coordinate[i];
	}
	return *this;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::Vertex<numberOfDimensions>::operator+ (const Vertex<numberOfDimensions> &b) const {
	Vertex<numberOfDimensions> result;
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		result[i] = this->coordinate[i] + b.coordinate[i];
	}
	return result;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>& lab309::Vertex<numberOfDimensions>::operator-= (const Vertex<numberOfDimensions> &b) {
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		this->coordinate[i] -= b.coordinate[i];
	}
	return *this;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::Vertex<numberOfDimensions>::operator- (const Vertex<numberOfDimensions> &b) const {
	Vertex<numberOfDimensions> result;
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		result[i] = this->coordinate[i] - b.coordinate[i];
	}
	return result;
}

//MULTIPLICATION
template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>& lab309::Vertex<numberOfDimensions>::operator*= (const Vertex<numberOfDimensions> &b) {
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		this->coordinate[i] *= b.coordinate[i];
	}
	return *this;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::Vertex<numberOfDimensions>::operator* (const Vertex<numberOfDimensions> &b) const {
	Vertex<numberOfDimensions> result;
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		result[i] = this->coordinate[i] * b.coordinate[i];
	}
	return result;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions>& lab309::Vertex<numberOfDimensions>::operator/= (const Vertex<numberOfDimensions> &b) {
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		this->coordinate[i] /= b.coordinate[i];
	}
	return *this;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::Vertex<numberOfDimensions>::operator/ (const Vertex<numberOfDimensions> &b) const {
	Vertex<numberOfDimensions> result;
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		result[i] = this->coordinate[i] / b.coordinate[i];
	}
	return result;
}

template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::Vertex<numberOfDimensions>::operator- (void) const {
	Vertex<numberOfDimensions> result;
	for (size_t i = 0; i < numberOfDimensions; i++) {
		result.coordinate[i] = -this->coordinate[i];
	}
	return result;
}

//COMPARISON
template <size_t numberOfDimensions>
bool lab309::Vertex<numberOfDimensions>::operator== (const Vertex<numberOfDimensions> &b) const {
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		if (this->coordinate[i] != b.coordinate[i]) {
			return false;
		}
	}
	return true;
}

template <size_t numberOfDimensions>
bool lab309::Vertex<numberOfDimensions>::operator!= (const Vertex<numberOfDimensions> &b) const {
	return !(*this == b);
}

//SCALAR MULTIPLICATION
template <size_t numberOfDimensions>
lab309::Vertex<numberOfDimensions> lab309::operator* (float scalar, const Vertex<numberOfDimensions> &vertex) {
	Vertex<numberOfDimensions> result = vertex;
	size_t i;
	for (i = 0; i < numberOfDimensions; i++) {
		result[i] = (float)(vertex[i]*scalar);
	}
	return result;
}

//IOSTREAM
template<size_t numberOfDimensions>
std::ostream& lab309::operator<< (std::ostream &stream, const Vertex<numberOfDimensions> &vertex) {
	size_t i;
	stream << '(' << vertex[0];
	for (i = 1; i < numberOfDimensions; i++) {
		stream << ", " << vertex[i];
	}
	stream << ')';
	return stream;
}

#endif
