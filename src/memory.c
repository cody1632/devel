#include <stdio.h>

#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "devel.h"
#include "camera.h"
#include "render.h"
#include "shader.h"

GLuint memory_vao, memory_vbo;
GLint memory_uniProj, memory_uniView, memory_uniModel, memory_uniRotation;
glm::mat4 memory_proj, memory_view, memory_model, memory_rotation;
GLfloat memory_vertices[] = {
0.0f, 0.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f,
0.0f, 5.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f,
1.0f, 5.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f,
1.0f, 5.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f,
1.0f, 0.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f,
0.0f, 0.0f, 0.0f,   0.3f, 0.4f, 0.5f, 1.0f
};

void MemoryInit (void) {
	glUseProgram (memory_shader_program);
    glGenVertexArrays (1, &memory_vao);
    glBindVertexArray (memory_vao);
    glGenBuffers (1, &memory_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, memory_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof(memory_vertices), memory_vertices, GL_DYNAMIC_DRAW);
    GLint pos_attrib = glGetAttribLocation (memory_shader_program, "position");
    glEnableVertexAttribArray (pos_attrib);
    glVertexAttribPointer (pos_attrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    GLint col_attrib = glGetAttribLocation (memory_shader_program, "color");
	glEnableVertexAttribArray (col_attrib);
	glVertexAttribPointer (col_attrib, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	memory_uniProj = glGetUniformLocation (memory_shader_program, "proj");
    memory_uniView = glGetUniformLocation (memory_shader_program, "view");
    memory_uniModel = glGetUniformLocation (memory_shader_program, "model");
    memory_model = glm::translate (glm::mat4(1.0), glm::vec3(0.0f));
    glUniformMatrix4fv (memory_uniProj, 1, GL_FALSE, glm::value_ptr(matrix_projection));
    glUniformMatrix4fv (memory_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
    glUniformMatrix4fv (memory_uniModel, 1, GL_FALSE, glm::value_ptr(memory_model));
    
    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
    glBindTexture (GL_TEXTURE_2D, 0);
}

void MemoryDraw (void) {
	glUseProgram (memory_shader_program);
    glUniformMatrix4fv (memory_uniView, 1, GL_FALSE, glm::value_ptr(matrix_view));
	glBindBuffer (GL_ARRAY_BUFFER, memory_vbo);
	glBindVertexArray (memory_vao);
	glDrawArrays (GL_TRIANGLES, 0, 6);
}

