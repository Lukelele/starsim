#include "Shape.h"


Shape::Shape()
{
	
}


Shape::Shape(const char* filepath) {
	LoadOBJ(filepath);
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
		cout << "file not open" << endl;
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

