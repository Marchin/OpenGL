#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../Headers/Renderer.h"
#include "../Headers/Shader.h"
#include "../Headers/stb_image.h"
#include "../Headers/Camera.h"
#include "../Headers/TextureController.h"
#include "../Headers/VertexBuffer.h"
#include "../Headers/VertexArray.h"
#include "../Headers/VertexBufferLayout.h"
#include "../Headers/UniformController.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	using namespace marchinGL;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpengGL", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	{
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		Renderer renderer;
		float cubeVertices[] = {
			// positions         
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		Shader sRed("Resources/Shaders/ColorShader/vColor.glsl",
			"Resources/Shaders/ColorShader/fRed.glsl");
		Shader sBlue("Resources/Shaders/ColorShader/vColor.glsl",
			"Resources/Shaders/ColorShader/fBlue.glsl");
		Shader sGreen("Resources/Shaders/ColorShader/vColor.glsl",
			"Resources/Shaders/ColorShader/fGreen.glsl");
		Shader sYellow("Resources/Shaders/ColorShader/vColor.glsl",
			"Resources/Shaders/ColorShader/fYellow.glsl");

		VertexArray va;
		VertexBuffer vb(cubeVertices, sizeof(cubeVertices));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		UniformController uc;
		uc.BindBlock(sRed, "Matrices");
		uc.BindBlock(sBlue, "Matrices");
		uc.BindBlock(sGreen, "Matrices");
		uc.BindBlock(sYellow, "Matrices");
		uc.CreateUniformBuffer("Matrices", 2 * sizeof(glm::mat4));

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		uc.SetUBSubData("Matrices", glm::value_ptr(projection), sizeof(glm::mat4), 0);

		while (!glfwWindowShouldClose(window)) {
			processInput(window);

			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			renderer.Clear();

			glm::mat4 view = camera.GetViewMatrix();
			uc.SetUBSubData("Matrices", glm::value_ptr(view), 
				sizeof(glm::mat4), sizeof(glm::mat4));

			va.Bind();

			sRed.Bind();
			glm::mat4 model(1.f);
			model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); 
			sRed.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			sBlue.Bind();
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f));
			sBlue.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			sGreen.Bind();
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); 
			sGreen.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			sYellow.Bind();
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); 
			sYellow.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCall(glViewport(0, 0, width, height));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll((float)yoffset);
}