#version 400

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

in vec3 ePos;
in vec3 eNormal;

uniform LightInfo uLight;
uniform Material uMaterial;

out vec4 FragColor;

vec3 phongModel() {
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
    FragColor = vec4(phongModel(), 1.0);
}