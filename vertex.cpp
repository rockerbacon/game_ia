#include "vertex.h"
#include <stdlib.h>

/*VERTEX_3D*/
template<> template<>
lab309::Vertex_3d::operator Vertex_2d (void) const {
	return Vertex<2>(this->coordinate[0], this->coordinate[1]);
}

/*VERTEX_2D*/
template<> template<>
lab309::Vertex_2d::operator Vertex_3d (void) const {
	return (Vertex_3d)Vertex<3>(this->coordinate[0], this->coordinate[1], 0.0f);
}
