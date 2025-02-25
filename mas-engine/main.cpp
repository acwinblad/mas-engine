// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include glew. Always include it before gl.h and glfw3.h, since it's a bit of magic.
#include <GL/glew.h>

// Include glfw
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm; // This allows us to use vec3 instead of glm::vec3 etc. true for everything glm now.

// Include the shader and texture
#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "objloader.hpp"
#include "vboindexer.hpp"

int main() {
	// Initialize glfw first
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize  GLFW\n");
		return -1;
	}

	// Create first OpenGL window
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3+
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // We don't want the old OpenGL

	// Open a window and create its OpenGL context
	//GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3+ compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to nitialize GLEW\n");
		return -1;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// hide the mouse and enable unlimited moevement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024.0f / 2.f, 768.0f / 2.f);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	// After window is created we can create a vertex array object (VAO). There are tutorials for VAO but not important atm
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	//GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	GLuint programID = LoadShaders("StandardShading.vert", "StandardShading.frag");

	// We need to create the MVPmatrix somewhere before the do/while loop
	// Get a handle for our "MVP" uniform
	// Only during initialization
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Load the texture using loadCustom
	//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
	GLuint Texture = loadDDS("uvmap-suzanne.DDS");

	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// read our .obj file
	std::vector<vec3 > vertices;
	std::vector<vec2 > uvs;
	std::vector<vec3 > normals;
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

	//vbo indices
	std::vector<unsigned short> indices;
	std::vector<vec3> indexed_vertices;
	std::vector<vec2> indexed_uvs;
	std::vector<vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
	
	// load it into a VBO

	// Give this triangle to OpenGL. Create a buffer!
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(vec3), &indexed_vertices[0], GL_STATIC_DRAW);
	// Now we can go to the do/while loop below, draw after glClear

	// for tutorial 04
	/*
	// colorbuffer is created in exact same way as the vertexbuffer
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	*/

	// for tutorial 05
	// colorbuffer is created in exact same way as the vertexbuffer
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	// normalbuffer is created in exact same way as the vertexbuffer
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// fill indices as needed
	// generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);


	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// this appears to be constant so remove it from do/while loop
	mat4 ModelMatrix = mat4(1.0f);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// for tutorial 06 we want to move the camera with keyboard and mouse so update the MVP inside the do/while loop
		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		mat4 ProjectionMatrix = getProjectionMatrix();
		mat4 ViewMatrix = getViewMatrix();
		mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		vec3 lightPos = vec3(4, 4, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set out 'myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// First attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,		// atrtribute 0. No particular reason for 0, but must matche the Layout in the shader
			3,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,		// stride
			(void*)0		// array buffer offset
		);

		// for tutorial 04
		/*
		// Second attribute buffer : color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,		// atrtribute 0. No particular reason for 0, but must matche the Layout in the shader
			3,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,		// stride
			(void*)0		// array buffer offset
		);
		*/

		// Second attribute buffer : uv
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,		// atrtribute 0. No particular reason for 0, but must matche the Layout in the shader
			2,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,		// stride
			(void*)0		// array buffer offset
		);

		// Third attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,		// atrtribute 0. No particular reason for 0, but must matche the Layout in the shader
			3,		// size
			GL_FLOAT,		// type
			GL_FALSE,		// normalized?
			0,		// stride
			(void*)0		// array buffer offset
		);

		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		// Draw the cube
		//glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0->12 triangles -> 6 squares
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		// index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		// draw the triangles !
		glDrawElements(
			GL_TRIANGLES, // mode
			indices.size(), // count 
			GL_UNSIGNED_SHORT, // type
			(void*)0					// element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;

}
