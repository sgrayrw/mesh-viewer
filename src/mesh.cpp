
#include "mesh.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;
using namespace agl;

Mesh::Mesh() {
}

Mesh::~Mesh() {
    cleanup();
}

bool Mesh::loadPLY(const std::string &filename) {
    try {
        cleanup();
        ifstream file(filename);

        string fileFormat;
        file >> fileFormat;
        if (fileFormat != "ply") {
            cout << "file not starting with \"ply\"" << endl;
            return false;
        }

        string line;
        // format, comment
        for (int i = 0; i < 3; ++i) {
            getline(file, line);
        }

        // element vertex #
        file >> line >> line >> _numVertices;

        // properties
        vector<string> v = {"sphere", "cube", "pyramid"};
        bool extra_properties = false;
        for (auto& name : v) {
            if (filename.find(name) != std::string::npos) {
                extra_properties = true;
            }
        }

        for (int i = 0; i < (extra_properties ? 9 : 7); ++i) {
            getline(file, line);
        }

        // face #
        file >> line >> line >> _numFaces;

        // some other header info
        for (int i = 0; i < 3; ++i) {
            getline(file, line);
        }

        // vertices
        _positions = new float[3 * _numVertices];
        _normals = new float[3 * _numVertices];
        for (int i = 0; i < _numVertices; ++i) {
            file >> _positions[i * 3] >> _positions[i * 3 + 1] >> _positions[i * 3 + 2]
            >> _normals[i * 3] >> _normals[i * 3 + 1] >> _normals[i * 3 + 2];

            if (extra_properties) {
                file >> line >> line;
            }

            _maxx = glm::max(_maxx, _positions[i * 3]);
            _maxy = glm::max(_maxy, _positions[i * 3 + 1]);
            _maxz = glm::max(_maxz, _positions[i * 3 + 2]);
            _minx = glm::min(_minx, _positions[i * 3]);
            _miny = glm::min(_miny, _positions[i * 3 + 1]);
            _minz = glm::min(_minz, _positions[i * 3 + 2]);
        }

        // faces
        _indices = new unsigned int[3 * _numFaces];
        for (int i = 0; i < _numFaces; ++i) {
            file >> line >> _indices[i * 3] >> _indices[i * 3 + 1] >> _indices[i * 3 + 2];
        }

        file.close();
        return true;
    } catch (const ifstream::failure& e) {
        cout << "Exception opening/reading file" << e.what() << endl;
        return false;
    }
}

void Mesh::cleanup() {
    if (_numVertices > 0) {
        delete[] _positions;
        delete[] _normals;
        delete[] _indices;
        _minx = _miny = _minz = FLT_MAX;
        _maxx = _maxy = _maxz = -FLT_MAX;
    }
}

glm::vec3 Mesh::getMinBounds() const {
    return vec3(_minx, _miny, _minz);
}

glm::vec3 Mesh::getMaxBounds() const {
    return vec3(_maxx, _maxy, _maxz);
}

int Mesh::numVertices() const {
    return _numVertices;
}

int Mesh::numTriangles() const {
    return _numFaces;
}

float *Mesh::positions() const {
    return _positions;
}

float *Mesh::normals() const {
    return _normals;
}

unsigned int *Mesh::indices() const {
    return _indices;
}

