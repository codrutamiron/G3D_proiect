#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

// New uniform for rotating light source
uniform float rotationAngle;

void main()
{
    // Rotate the light source
    mat4 rotationMatrix = mat4(
        vec4(cos(rotationAngle), 0.0, -sin(rotationAngle), 0.0),
        vec4(0.0, 1.0, 0.0, 0.0),
        vec4(sin(rotationAngle), 0.0, cos(rotationAngle), 0.0),
        vec4(0.0, 0.0, 0.0, 1.0)
    );

    // Update the light space matrix with rotation
    mat4 rotatedLightSpaceMatrix = lightSpaceMatrix * rotationMatrix;

    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = rotatedLightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}
