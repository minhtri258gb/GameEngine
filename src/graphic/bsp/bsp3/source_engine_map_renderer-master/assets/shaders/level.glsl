#ifdef VERTEX_SHADER
// Attributes that the engine Shader class will pass to this shader.  Do NOT
// change the location numbers; they are expected by the engine Shader class.
layout (location = 0) in vec3 point_position;

// Primary matrix transforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(point_position, 1.0);
}
#endif


#ifdef FRAGMENT_SHADER

// Color that will be assigned to the fragment this shader is processing
uniform vec3 face_color;
out vec4 final_color;

void main() {
    final_color = vec4(face_color, 1.0);
}
#endif
