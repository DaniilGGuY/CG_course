#include "face.h"

Face::Face(size_t first, size_t second, size_t third, QColor color)
    : _first_vertex(first), _second_vertex(second), _third_vertex(third), _color(color) {}

void Face::setFirstVertex(size_t first) { _first_vertex = first; }

void Face::setSecondVertex(size_t second) { _second_vertex = second; }

void Face::setThirdVertex(size_t third) { _third_vertex = third; }

void Face::setColor(QColor color) { _color = color; }

void Face::setFace(size_t first, size_t second, size_t third, QColor color) {
    _first_vertex = first;
    _second_vertex = second;
    _third_vertex = third;
    _color = color;
}

void Face::setFace(const Face &face) {
    _first_vertex = face._first_vertex;
    _second_vertex = face._second_vertex;
    _third_vertex = face._third_vertex;
    _color = face._color;
}

size_t Face::getFirstVertex() const { return _first_vertex; }

size_t Face::getSecondVertex() const { return _second_vertex; }

size_t Face::getThirdVertex() const { return _third_vertex; }

QColor Face::getColor() const { return _color; }

bool Face::operator==(const Face &face) const {
    return _first_vertex == face._first_vertex &&
           _second_vertex == face._second_vertex &&
           _third_vertex == face._third_vertex;
}
bool Face::operator!=(const Face &face) const {
    return _first_vertex != face._first_vertex ||
           _second_vertex != face._second_vertex ||
           _third_vertex != face._third_vertex;
}
