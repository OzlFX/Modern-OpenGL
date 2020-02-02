#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>
#include <string>
#include <string_view>
#include <glm/ext.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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

	const char* glsl_version = "#version 330";

	int width = 960;
	int height = 540;

	//Initialize the library
	if (!glfwInit())
		throw std::exception();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window in window mode with an OpenGL context
	m_Window = glfwCreateWindow(width, height, "Modern OpenGL Learning", NULL, NULL);

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
		100.0f, 100.0f, 0.0f, 0.0f,
		400.0f, 100.0f, 1.0f, 0.0f,
		400.0f, 400.0f, 1.0f, 1.0f,
		100.0f, 400.0f, 0.0f, 1.0f
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

	glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f); //Aspec ratio for the 2D images
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 0.0f)); //Create view


	std::shared_ptr<cShaderProgram> shader = std::make_shared<cShaderProgram>("../assets/shaders/Shader.glsl");
	shader->Bind();
	//shader->setUniform("u_Colour", 0.8, 0.4f, 0.7f, 1.0f);

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

	ImGui::CreateContext(); //Create ImGui context for usage
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true); //Init ImGui for OpenGL
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	ImGui::StyleColorsDark(); //Setup Dear ImGui style

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	glm::vec3 translation(200.0f, 200.0f, 0.0f);

	//Main Loop
	while (!glfwWindowShouldClose(m_Window))
	{
		renderer->Clear();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation); //Model matrix

		glm::mat4 MVP = projection * view * model; //The model, view projection matrix

		//Testing if OpenGL is linked and working
		shader->Bind();
		shader->setUniform("u_Projection", MVP); //Projection view for the window

		renderer->Draw(vertArray, index, shader);

		if (r > 1.0f)
			inc = -0.005f;
		else if (r < 0.0f)
			inc = 0.005f;

		r += inc;

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat3("Translation", &translation.x, 0.0f, width); // Edit 1 float using a slider from 0.0f to max screen width
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Swap front and back buffers
		glfwSwapBuffers(m_Window);

		//Poll for input events
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}