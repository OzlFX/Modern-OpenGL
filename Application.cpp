#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <string>
#include <string_view>
#include <glm/ext.hpp>

#include "cUtil.h"
#include "VertexArray.h"
#include "cVertexBuffer.h"
#include "cIndexBuffer.h"
#include "VertexBufferLayout.h"
#include "ShaderProgram.h"
#include "cRenderer.h"
#include "Texture.h"

int main(void)
{
	GLFWwindow* m_Window;

	//Initialize the library
	if (!glfwInit())
		throw std::exception();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window in window mode with an OpenGL context
	m_Window = glfwCreateWindow(1120, 700, "Modern OpenGL Learning", NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate(); //Terminate glfw
		throw std::exception();
	}

	//Make the window's context current
	glfwMakeContextCurrent(m_Window);

	glfwSwapInterval(1);

	//Initialise glew
	if (glewInit() != GLEW_OK)
	{
		//if glew fails to initialises, an error is returned to the console and throws an exception
#if _DEBUG
		std::cout << "ERROR: unable to initialize glew!" << std::endl;
#endif
		throw std::exception();
	}

#if _DEBUG
	std::cout << glGetString(GL_VERSION) << std::endl;
#endif

	float pos[]
	{
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::shared_ptr<cVertexArray> vertArray = std::make_shared<cVertexArray>();
	std::shared_ptr<cVertexBuffer> buffer = std::make_shared<cVertexBuffer>(pos, sizeof(pos));
	std::shared_ptr<cVertexBufferLayout> layoutBuffer = std::make_shared<cVertexBufferLayout>();

	layoutBuffer->Push<float>(2);
	layoutBuffer->Push<float>(2);
	vertArray->AddBuffer(buffer, layoutBuffer);
	
	std::shared_ptr<cIndexBuffer> index = std::make_shared<cIndexBuffer>(indices, sizeof(indices));

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); //Aspec ratio for the 2D images

	std::shared_ptr<cShaderProgram> shader = std::make_shared<cShaderProgram>("../assets/shaders/Shader.glsl");
	shader->Bind();
	//shader->setUniform("u_Colour", 0.8, 0.4f, 0.7f, 1.0f);
	shader->setUniform("u_Projection", projection);

	std::shared_ptr<cTexture> texture = std::make_shared<cTexture>("../assets/textures/RDmeme.jpg");
	texture->Bind();

	shader->setUniform("u_Texture", 0);

	float r = 0.2f;
	float inc = 0.005f;

	vertArray->Unbind();
	shader->Unbind();
	buffer->Unbind();
	index->Unbind();

	std::shared_ptr<cRenderer> renderer = std::make_shared<cRenderer>();

	//Main Loop
	while (!glfwWindowShouldClose(m_Window))
	{
		renderer->Clear();

		//Testing if OpenGL is linked and working
		shader->Bind();
		//shader->setUniform("u_Colour", r, 0.4f, 0.7f, 1.0f);

		renderer->Draw(vertArray, index, shader);

		if (r > 1.0f)
			inc = -0.005f;
		else if (r < 0.0f)
			inc = 0.005f;

		r += inc;

		//Swap front and back buffers
		glfwSwapBuffers(m_Window);

		//Poll for input events
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwTerminate();
	return 0;
}