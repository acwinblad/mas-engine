#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

int main()
{
	    // Define a vector
    glm::vec3 myVector(1.0f, 2.0f, 3.0f);
    std::cout << "Original Vector: (" << myVector.x << ", " << myVector.y << ", " << myVector.z << ")" << std::endl;

    // Define a 4x4 identity matrix
    glm::mat4 myMatrix = glm::mat4(1.0f);

    // Translate the matrix
    myMatrix = glm::translate(myMatrix, glm::vec3(1.0f, 1.0f, 1.0f));

    // Rotate the matrix around the Z-axis
    myMatrix = glm::rotate(myMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Scale the matrix
    myMatrix = glm::scale(myMatrix, glm::vec3(2.0f, 2.0f, 2.0f));

    // Multiply the matrix by the vector
    glm::vec4 tempVector = glm::vec4(myVector, 1.0f);
    glm::vec4 resultVector = myMatrix * tempVector;

    // Print the result
    std::cout << "Transformed Vector: (" << resultVector.x << ", " << resultVector.y << ", " << resultVector.z << ")" << std::endl;

    return 0;
}