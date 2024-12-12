#ifndef FACE_H
#define FACE_H

#include <QColor>
#include <cstddef>

class Face
{
public:
    Face() = default;
    Face(size_t first, size_t second, size_t third, QColor color);

    explicit Face(const Face &face) = default;
    Face &operator=(const Face &face) = default;

    Face(Face &&face) = default;
    Face &operator=(Face &&face) = default;

    void setFirstVertex(size_t first);
    void setSecondVertex(size_t second);
    void setThirdVertex(size_t third);
    void setColor(QColor color);
    void setFace(size_t first, size_t second, size_t third, QColor color);
    void setFace(const Face &face);

    size_t getFirstVertex() const;
    size_t getSecondVertex() const;
    size_t getThirdVertex() const;
    QColor getColor() const;

    bool operator==(const Face &face) const;
    bool operator!=(const Face &face) const;

private:
    size_t _first_vertex;
    size_t _second_vertex;
    size_t _third_vertex;
    QColor _color;
};

#endif // FACE_H
