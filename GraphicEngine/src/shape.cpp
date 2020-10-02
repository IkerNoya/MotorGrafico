#include "GL/glew.h"
#include "shape.h"

#include <stdlib.h>

#include "GLFW/glfw3.h"


Shape::Shape(unsigned int shape, Renderer* renderer):Entity(Entity::_renderer) {
	_shape = shape;
	_renderer = renderer;
	_material = new Material();
}
Shape::~Shape() {
	if (_material != NULL)
		delete _material;
}
unsigned int Shape::getType() {
	return _shape;
}
void Shape::init() {
	if (_shape == GL_TRIANGLES) {
		initTriangleVertex();
	}
	else if (_shape == GL_QUADS) {
		initRectangleVertex();
	}
}
void Shape::initTriangleVertex() {
	float vertex[15] = {
	   -0.5f, 0.0f, _material->GetR(),_material->GetG(),_material->GetB(),
	   0.0f, 0.5f, _material->GetR(),_material->GetG(),_material->GetB(),
	   0.5f, 0.0f, _material->GetR(),_material->GetG(),_material->GetB()
	};
	_renderer->bindVBO(vertex, 15);
}
void Shape::initRectangleVertex() {
	float vertex[20] = {
	-0.5f, -0.5f, _material->GetR(),_material->GetG(),_material->GetB(),
	-0.5f, 0.5f, _material->GetR(),_material->GetG(),_material->GetB(),
	0.5f, 0.5f, _material->GetR(),_material->GetG(),_material->GetB(),
	0.5f, -0.5f, _material->GetR(),_material->GetG(),_material->GetB()
	};
	_renderer->bindVBO(vertex, 20);
}
void Shape::setColor(float r, float g, float b) {
	_material->SetColor(r, g, b);
}