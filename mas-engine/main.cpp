#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <iostream>

unsigned int shaderProgram{};

constexpr auto vertexShaderSource = R"()";

constexpr auto fragmentShaderSource = R"()";

constexpr auto squareVertices = std::array{
	-0.5f, 0.5f, 0.0f, // Top-left
	0.5f, 0.5f, 0.0f, // Top-right
	0.5f, 0.5f, 0.0f, // Top-right
	0.5f, -0.5f, 0.0f, // Bottom-right
	0.5f, -0.5f, 0.0f, // Bottom-right
	-0.5f, -0.5f, 0.0f, // Bottom-left
	-0.5f, -0.5f, 0.0f, // Bottom-left
	-0.5f, 0.5f, 0.0f, // Top-left
};

void framebufferSizeChanged(GLFWwindow* window, int width, int height);
void render(GLFWwindow* window);

int main()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* VideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	const auto ScreenHeight = VideoMode->height;

	GLFWwindow* window = glfwCreateWindow(ScreenHeight / 2, ScreenHeight / 2, "OpenGL + GLFW", NULL, NULL);

	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}




}


