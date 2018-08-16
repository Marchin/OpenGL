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
#include "../Headers/Model.h"
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

		/*float vertices[] = {
			-0.5f, -0.5f,
			-0.5f,  0.5f,
			0.5f, -0.5f,
			0.5f,  0.5f
		};*/
		TextureController  textureController;
		/*Texture texture1("Resources/container.jpg", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE,
			GL_NEAREST, GL_NEAREST);

		Shader shader("Resources/Shaders/Shader1/vShader.glsl",
			"Resources/Shaders/Shader1/fShader.glsl");*/
		Shader sTexture("Resources/Shaders/Explosion/vExplosion.glsl",
			"Resources/Shaders/Explosion/fExplosion.glsl",
			"Resources/Shaders/Explosion/gExplosion.glsl");
		Shader sNormal("Resources/Shaders/NormalShader/vNormal.glsl",
			"Resources/Shaders/NormalShader/fNormal.glsl",
			"Resources/Shaders/NormalShader/gNormal.glsl");
		model::Model soldier("Resources/nanosuit/nanosuit.obj");
		

		/*VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		unsigned int indices[] = {
			0, 1, 3,
			3, 2, 0
		};

		ElementBuffer eb(indices,6);

		sTexture.Bind();
		sTexture.SetInt("texture_diffuse1", 0);*/

		while (!glfwWindowShouldClose(window)) {
			processInput(window);

			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			renderer.Clear();

			sTexture.Bind();
			sTexture.SetFloat("time", 3.14f*3.f/2.f);

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
				(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
			sTexture.SetMat4("projection", projection);

			glm::mat4 view = camera.GetViewMatrix();
			sTexture.SetMat4("view", view);

			//textureController.AddTexture(texture1);
			//va.Bind();
			glm::mat4 model(1.f);  
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
			sTexture.SetMat4("model", model);
			soldier.Draw(sTexture, textureController);
			sNormal.Bind();
			sNormal.SetMat4("projection", projection);
			sNormal.SetMat4("view", view);
			sNormal.SetMat4("model", model);
			soldier.Draw(sNormal, textureController);
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

			textureController.Reset();
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