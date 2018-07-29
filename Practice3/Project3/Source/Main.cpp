#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include "../Headers/Renderer.h"
#include "../Headers/Shader.h"
#include "../Headers/stb_image.h"
#include "../Headers/Camera.h"
#include "../Headers/TextureController.h"
#include "../Headers/VertexBuffer.h"
#include "../Headers/VertexArray.h"
#include "../Headers/VertexBufferLayout.h"
#include "../Headers/Framebuffer.h"
#include "../Headers/Renderbuffer.h"
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
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		//GLCall(glEnable(GL_CULL_FACE));


		float cubeVertices[] = {
			// Back face
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
			// Front face
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
			// Left face
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
			// Right face
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
			// Bottom face
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right      
		};
		float planeVertices[] = {
			// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
			5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

			5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};
		float quadVertices[] = {
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

			-0.75f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
		};

		TextureController  textureController;
		Texture cubeTexture("Resources/container.jpg", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE,
			GL_NEAREST, GL_NEAREST);
		Texture planeTexture("Resources/metal.png", GL_REPEAT, GL_REPEAT,
			GL_NEAREST, GL_NEAREST);
		Texture fbTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

		Shader shader("Resources/Shaders/ShaderTexture/vTexture.glsl",
			"Resources/Shaders/ShaderTexture/fTexture.glsl");
		Shader framebufferShader("Resources/Shaders/Framebuffer/vFramebuffer.glsl",
			"Resources/Shaders/Framebuffer/fFramebuffer.glsl");

		VertexArray cubeVA;
		VertexBuffer cubeVB(cubeVertices, sizeof(cubeVertices));
		VertexBufferLayout cubeLayout;
		cubeVA.Bind();
		cubeLayout.Push<float>(3);
		cubeLayout.Push<float>(2);
		cubeVA.AddBuffer(cubeVB, cubeLayout);
		cubeVA.Unbind();

		VertexArray planeVA;
		VertexBuffer planeVB(planeVertices, sizeof(planeVertices));
		VertexBufferLayout planeLayout;
		planeVA.Bind();
		planeLayout.Push<float>(3);
		planeLayout.Push<float>(2);
		planeVA.AddBuffer(planeVB, planeLayout);
		planeVA.Unbind();

		VertexArray quadVA;
		quadVA.Bind();
		VertexBuffer quadVB(quadVertices, sizeof(quadVertices));
		VertexBufferLayout quadLayout;
		quadVA.Bind();
		quadLayout.Push<float>(2);
		quadLayout.Push<float>(2);
		quadVA.AddBuffer(quadVB, quadLayout);
		quadVA.Unbind();

		Framebuffer fb;
		fb.Bind();
		fb.AttachTexture(fbTexture.GetID());
		Renderbuffer rb = Renderbuffer(GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
		fb.AttachRenderbuffer(rb.GetID(), GL_DEPTH_STENCIL_ATTACHMENT);
		fb.CheckStatus();
	
		shader.Bind();
		shader.SetInt("texture1", 0);
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

		while (!glfwWindowShouldClose(window)) {
			processInput(window);

			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			
			fb.Bind();
			renderer.Clear();
			GLCall(glEnable(GL_DEPTH_TEST));

#pragma region DRAW


			renderer.Clear();
			shader.Bind();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
				(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
			shader.SetMat4("projection", projection);
			glm::mat4 view = camera.GetViewMatrix();
			shader.SetMat4("view", view);
			glm::mat4 model(1.f);

			// floor
			textureController.Reset();
			planeVA.Bind();
			shader.Bind();
			textureController.AddTexture(planeTexture);
			shader.SetMat4("model", glm::mat4(1.f));
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
			planeVA.Unbind();

			textureController.Reset();
			textureController.AddTexture(cubeTexture);

			cubeVA.Bind();
			shader.Bind();
			textureController.AddTexture(cubeTexture);
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
			shader.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
			shader.SetMat4("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
			cubeVA.Unbind();
#pragma endregion

			fb.Unbind();
			GLCall(glClearColor(1.f, 1.f, 1.f, 1.f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			framebufferShader.Bind();
			quadVA.Bind();
			GLCall(glDisable(GL_DEPTH_TEST));
			textureController.Reset();
			textureController.AddTexture(fbTexture);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

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