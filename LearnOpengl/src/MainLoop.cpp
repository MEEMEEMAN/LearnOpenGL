#include "perhapsPch.h"

#include "rendering/Context.h"
#include "rendering/Shader.h"
#include "utils/Time.h"
#include "rendering/VertexContainers.h"
#include "utils/Input.h"
#include "rendering/Camera.h"

const int WIDTH = 800;
const int HEIGHT= 600;

float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;


int main()
{
	OpenGLContext context(WIDTH, HEIGHT, "Hello perhaps!");


	{
		float vertices[] = 
		{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};


		VertexArray va;
		va.Bind();
		GLVertexBuffer vb(vertices, sizeof(vertices)/sizeof(float));
		GLVertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		va.AddBuffer(vb, layout);

		Shader litVS(GL_VERTEX_SHADER, Shader::ParseShader("src/shaders/BasicLit.vert"));
		Shader litFS(GL_FRAGMENT_SHADER, Shader::ParseShader("src/shaders/BasicLit.frag"));

		ShaderProgram litProgram;
		litProgram.AttachShader(litVS);
		litProgram.AttachShader(litFS);
		litProgram.LinkProgram();
		litProgram.UseProgram();
		litProgram.SetUniform3f("ObjectColor", glm::vec3(1.0, 1.0,1.0));
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		litProgram.SetUniform3f("LightPos", lightPos);
		
		Shader unlitVS(GL_VERTEX_SHADER, Shader::ParseShader("src/shaders/UnlitShader.vert"));
		Shader unlitFS(GL_FRAGMENT_SHADER, Shader::ParseShader("src/shaders/UnlitShader.frag"));
		ShaderProgram unlitProgram;
		unlitProgram.AttachShader(unlitVS);
		unlitProgram.AttachShader(unlitFS);
		unlitProgram.LinkProgram();
		unlitProgram.UseProgram();
		unlitProgram.SetUniform3f("ObjectColor", glm::vec3(1.0, 1.0, 1.0));

		//GLCall(glClearColor(0.5f, 0.5f, 1.0f, 1.0f));
		float timer = 0.0f;

		GLCall(glEnable(GL_DEPTH_TEST));

		//projection * view * model * position <- multiplication order
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)(800 / 600), 0.1f, 100.0f);
		glfwSwapInterval(1);
		GLFWwindow* window = context.GetWindow();
		Input::SetWindow(window);

		OpenGLCamera cam;

		Loopable::StartLoop();
		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			Time::SwitchPrevious();
			Time::SetNow();
			timer += Time::GetTimeDelta();

			Loopable::UpdateLoop();

			unlitProgram.UseProgram();
			glm::mat4 unlitCube(1.0);
			unlitCube = glm::rotate(unlitCube, timer, glm::vec3(0, 1, 0));
			unlitCube = glm::translate(unlitCube, glm::vec3(0, 0, 1));
			unlitCube = glm::scale(unlitCube, glm::vec3(0.3, 0.3, 0.3));

			unlitProgram.SetMat4f("model", unlitCube);
			unlitProgram.SetMat4f("view", cam.GetView());
			unlitProgram.SetMat4f("projection", cam.GetProjection());

			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			va.Bind();

			litProgram.UseProgram();
			glm::mat4 litCube = glm::mat4(1.0f);

			litProgram.SetMat4f("model", litCube);
			litProgram.SetMat4f("view", cam.GetView());
			litProgram.SetMat4f("projection", cam.GetProjection());
			
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

			GLCall(glfwSwapBuffers(window));
			Input::Update();
		}
	}

	return 0;
}
