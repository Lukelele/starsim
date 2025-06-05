#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferAttribute.h"


using namespace std;


class Shape
{
public:
    Shape();
    Shape(const char* filepath);
    Shape(float radius, int subdivisions); // Constructor for icosphere
    ~Shape();

    void BindVertices();
    void Free();

    void LoadOBJ(const char* filepath);
    void GenerateIcosphere(float radius = 1.0f, int subdivisions = 2);
    vector<float>& GetVertices() { return m_vertices; }
    vector<float>& GetNormals() { return m_normals; }
    size_t GetVerticesCount() { return m_vertices.size(); }
    size_t GetNormalsCount() { return m_normals.size(); }
    VertexBuffer& GetPositionBuffer() { return m_positionBuffer; }
    VertexBuffer& GetNormalBuffer() { return m_normalBuffer; }
    VertexArray& GetVertexArray() { return m_vertexArray; }
private:
    vector<float> m_vertices;
    vector<float> m_normals;

    VertexBuffer m_positionBuffer = VertexBuffer();
    VertexBuffer m_normalBuffer = VertexBuffer();
    VertexArray m_vertexArray = VertexArray();
};
