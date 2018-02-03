#version 410

in vec4 vertex_position;
uniform mat4 local_transform;
uniform mat4 world_transform;

void main() {
    gl_Position = world_transform * local_transform * vertex_position;
}
