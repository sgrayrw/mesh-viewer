#version 400

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNor;

struct LightInfo {
    vec3 position;
    vec3 color;
};

struct Material {
    vec3 Kd;
    vec3 Ka;
    vec3 Ks;
    float shininess;
};

uniform LightInfo uLight;
uniform Material uMaterial;

uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat3 uNMV;
out vec3 color;

vec3 phongModel(in vec3 ePos, in vec3 eNormal) {
    vec3 Ia = uMaterial.Ka;

    vec3 s = normalize(uLight.position - ePos);
    vec3 v = normalize(-ePos);
    vec3 r = reflect(-s, eNormal);
    float angle = max(dot(s, eNormal), 0.0);
    vec3 Id = uLight.color * uMaterial.Kd * angle;

    vec3 Is = vec3(0.0);
    if (angle > 0.0) {
        Is = uMaterial.Ks * pow(max(dot(r, v), 0.0), uMaterial.shininess);
    }
    return Ia + Id + Is;
}

void main() {
    gl_Position = uMVP * vec4(vPos, 1.0);

    vec4 ePos = uMV * vec4(vPos, 1.0);
    vec3 eNormal = normalize(uNMV * vNor);
    color = phongModel(ePos.xyz, eNormal);
}
