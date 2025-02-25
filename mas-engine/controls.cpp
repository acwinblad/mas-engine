// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // the "extern" keyword here is to access the variable "window" declared in main.cpp. Keeps tutorial simple (avoid in future scenarios!)

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <controls.hpp>

mat4 ViewMatrix;
mat4 ProjectionMatrix;

mat4 getViewMatrix() {
	return ViewMatrix;
}

mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}


// position
vec3 position = vec3(0, 0, 5);
// horizontal angle : toward -z
float horizontalAngle = pi<float>();
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// initial field of view
float initialFoV = 45.0f;

float speed = 0.1f; // 3 units / second
float mouseSpeed = 0.001f;

void computeMatricesFromInputs() {

	// glfwgettime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// compute time difference between current and last frame (useful for when there are lag spikes)
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// get mouse position
	double xpos, ypos;
	float height, width;
	height = 768;
	width = 1024;
	glfwGetCursorPos(window, &xpos, &ypos);
	// reset cursor position for next frame
	glfwSetCursorPos(window, width / 2, height / 2);

	// compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(width / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(height / 2 - ypos);
	constexpr float vertMax = half_pi<float>() - 1.f;
	// restrict the verticalAngle so you can't go upside down
	if (verticalAngle > vertMax) { verticalAngle = vertMax; }
	else if (verticalAngle < -vertMax) { verticalAngle = -vertMax; }

	// direction : spherical coordinates to cartesian coordinates conversion
	vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	// right vector
	vec3 right = vec3(sin(horizontalAngle - half_pi<float>()), 0, cos(horizontalAngle - half_pi<float>()));
	vec3 up = cross(right, direction);

	// move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}

	// use mouse wheel for zoom
	float FoV = initialFoV; // - 5 * glfwGetMouseWheel(); // now glfw3 requires setting up a callback for this. (bit complicated for this tutorial)

	// projection matrix : 45&deg; field of view, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// camera matrix
	ViewMatrix = lookAt(
		position,							// camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up										// head is up (set to 0, -1, 0 to look upside-down)
	);




}
