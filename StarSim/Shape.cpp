#include "Shape.h"
#include <map>
#include <cmath>


Shape::Shape()
{
    
}


Shape::Shape(const char* filepath) {
    LoadOBJ(filepath);
}

Shape::Shape(float radius, int subdivisions) {
    GenerateIcosphere(radius, subdivisions);
}


Shape::~Shape() {
    Free();
}


void Shape::BindVertices() {
    m_vertexArray.Bind();

    m_positionBuffer.AddData(&m_vertices[0], m_vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

    m_normalBuffer.AddData(&m_normals[0], m_normals.size() * sizeof(float), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);

    m_vertexArray.UnBind();
}


void Shape::Free() {
    m_vertexArray.UnBind();
    m_vertices.clear();
    m_normals.clear();
}


void Shape::LoadOBJ(const char* filepath) {
    vector<float> vertices;
    vector<float> normals;
    vector<int> vertexIndices;
    vector<int> normalIndices;

    ifstream file;
    file.open(filepath);
    if (!file.is_open()) {
        cout << "File: " << filepath << " Not Found" << endl;
        return;
    }

    string mode;
    while (file >> mode) {
        if (mode == "v") {
            for (int i = 0; i < 3; i++) {
                float f;
                file >> f;
                vertices.push_back(f);
            }
        }
        else if (mode == "vn") {
            for (int i = 0; i < 3; i++) {
                float f;
                file >> f;
                normals.push_back(f);
            }
        }
        else if (mode == "f") {
            for (int i = 0; i < 3; i++) {
                string s;
                string indexString = "";
                file >> s;

                for (char c : s) {
                    if (c == '/') {
                        if (indexString != "") {
                            vertexIndices.push_back(atoi(indexString.c_str()));
                            indexString.clear();
                        }
                    }
                    else {
                        indexString += c;
                    }
                }
                if (indexString != "") {
                    normalIndices.push_back(atoi(indexString.c_str()));
                    indexString.clear();
                }
            }
        }
    }

    if (normalIndices.size() == 0 || vertexIndices.size() == 0) {
        cout << "No vertex data were loaded from file" << endl;
        return;
    }
    for (int i : vertexIndices) {
        m_vertices.push_back(vertices[(i - 1) * 3]);
        m_vertices.push_back(vertices[(i - 1) * 3 + 1]);
        m_vertices.push_back(vertices[(i - 1) * 3 + 2]);
    }

    for (int i : normalIndices) {
        m_normals.push_back(normals[(i - 1) * 3]);
        m_normals.push_back(normals[(i - 1) * 3 + 1]);
        m_normals.push_back(normals[(i - 1) * 3 + 2]);
    }

    BindVertices();

    file.close();
}

void Shape::GenerateIcosphere(float radius, int subdivisions) {
    // Clear existing data
    m_vertices.clear();
    m_normals.clear();

    // Golden ratio
    const float t = (1.0f + sqrt(5.0f)) / 2.0f;

    // Create initial icosahedron vertices
    vector<glm::vec3> vertices = {
        glm::normalize(glm::vec3(-1,  t,  0)) * radius,
        glm::normalize(glm::vec3( 1,  t,  0)) * radius,
        glm::normalize(glm::vec3(-1, -t,  0)) * radius,
        glm::normalize(glm::vec3( 1, -t,  0)) * radius,
        glm::normalize(glm::vec3( 0, -1,  t)) * radius,
        glm::normalize(glm::vec3( 0,  1,  t)) * radius,
        glm::normalize(glm::vec3( 0, -1, -t)) * radius,
        glm::normalize(glm::vec3( 0,  1, -t)) * radius,
        glm::normalize(glm::vec3( t,  0, -1)) * radius,
        glm::normalize(glm::vec3( t,  0,  1)) * radius,
        glm::normalize(glm::vec3(-t,  0, -1)) * radius,
        glm::normalize(glm::vec3(-t,  0,  1)) * radius
    };

    // Create initial icosahedron faces (triangles)
    vector<glm::ivec3> faces = {
        // 5 faces around point 0
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        // 5 adjacent faces
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        // 5 faces around point 3
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        // 5 adjacent faces
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    // Subdivide faces
    for (int i = 0; i < subdivisions; i++) {
        vector<glm::ivec3> newFaces;
        map<pair<int, int>, int> midpointCache;

        auto getMidpoint = [&](int i1, int i2) -> int {
            // Ensure consistent ordering for cache key
            if (i1 > i2) swap(i1, i2);
            pair<int, int> key = {i1, i2};
            
            if (midpointCache.find(key) != midpointCache.end()) {
                return midpointCache[key];
            }

            // Calculate midpoint and normalize to sphere surface
            glm::vec3 midpoint = (vertices[i1] + vertices[i2]) * 0.5f;
            midpoint = glm::normalize(midpoint) * radius;
            
            int newIndex = vertices.size();
            vertices.push_back(midpoint);
            midpointCache[key] = newIndex;
            return newIndex;
        };

        // Subdivide each triangle into 4 triangles
        for (const auto& face : faces) {
            int a = getMidpoint(face.x, face.y);
            int b = getMidpoint(face.y, face.z);
            int c = getMidpoint(face.z, face.x);

            newFaces.push_back({face.x, a, c});
            newFaces.push_back({face.y, b, a});
            newFaces.push_back({face.z, c, b});
            newFaces.push_back({a, b, c});
        }

        faces = newFaces;
    }

    // Convert to vertex arrays for rendering
    for (const auto& face : faces) {
        for (int i = 0; i < 3; i++) {
            glm::vec3 vertex = vertices[face[i]];
            glm::vec3 normal = glm::normalize(vertex); // For a sphere, normal = normalized position

            // Add vertex
            m_vertices.push_back(vertex.x);
            m_vertices.push_back(vertex.y);
            m_vertices.push_back(vertex.z);

            // Add normal
            m_normals.push_back(normal.x);
            m_normals.push_back(normal.y);
            m_normals.push_back(normal.z);
        }
    }

    // Bind the generated vertices
    BindVertices();
}
