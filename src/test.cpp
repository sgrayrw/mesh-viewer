#include <glm/gtx/string_cast.hpp>
#include "mesh.h"

using namespace agl;
using namespace std;

int main() {
    Mesh mesh;
    mesh.loadPLY("../models/saratoga.ply");
    cout << glm::to_string(mesh.getMinBounds()) << endl;
    cout << glm::to_string(mesh.getMaxBounds()) << endl;
}