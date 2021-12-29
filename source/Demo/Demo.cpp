#include "Demo.h"
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // 这个头文件需要放到 STB_IMAGE_IMPLEMENTATION 宏定义后面
#include "GLFWWindowUtils.h"

namespace
{
	// 相机位置 (0, 0.0f, 3.0f)， pitch 0度，yaw 180.0度，相当于时向后看，即向z轴负方向看
	Camera camera(glm::vec3(0, 0.0f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));


	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width / 2, height / 2);
	}

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::FORWARD);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::BACKWARD);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::LEFT);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::RIGHT);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::UP);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveOption::DOWN);
	}

	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	double lastX;
	double lastY;
	bool firstMouse = true;


	void MouseMoveCallBack(GLFWwindow* pWindow, double xPos, double yPos)
	{
		if (firstMouse)
		{
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
			return;
		}

		float xoffset = float(xPos - lastX);
		float yoffset = float(lastY - yPos); // reversed since y-coordinates go from bottom to top

		lastX = xPos;
		lastY = yPos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}

	void ScrollCallBack(GLFWwindow* pWindow, double xOffset, double yOffset)
	{
		camera.ProcessMouseScroll(float(yOffset));
	}
}

unsigned int Demo::CreateVertexShader(const char* vertexShaderSource)
{
	// build and compile
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);  // create a vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // attach the source code to the shader
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);  // check if the compilation is successful
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error info: " << infoLog << std::endl;
	}

	return vertexShader;
}

unsigned int Demo::CreateFragmentShader(const char* fragmentShaderSource)
{
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);  // create a fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);  // check for shader compile error
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error info: " << infoLog << std::endl;
	}

	return fragmentShader;
}

unsigned int Demo::LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking erroes
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error info: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Demo::TestDemo_1()
{
	// source code
	const char *vertexShaderSource1 =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;  \n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";

	const char *fragmentShaderSource1 =
		"#version 330 core\n"
		"in vec3 ourColor;  \n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0f);\n"
		"}\0";

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top   
	};

	// create window
	GLFWwindow* window = GLFWWindowUtils::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return;
	}

	unsigned int vertexShader = CreateVertexShader(vertexShaderSource1);
	unsigned int fragmentShader = CreateFragmentShader(fragmentShaderSource1);
	unsigned int shaderProgram = LinkShaders(vertexShader, fragmentShader);


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 
	glUseProgram(shaderProgram);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	
}

void Demo::TestDemo_2()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0f);\n"
		"}\n\0";

	GLFWwindow* window = GLFWWindowUtils::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("../../../source/Demo/GLSL/Demo_2/shader.vs", "../../../source/Demo/GLSL/Demo_2/shader.fs");

	unsigned int vertexShader = CreateVertexShader(ourShader.GetVertexString().c_str() /*vertexShaderSource*/);
	unsigned int fragmentShader = CreateFragmentShader(ourShader.GetFragmentString().c_str() /*fragmentShaderSource*/);
	unsigned int shaderProgram = LinkShaders(vertexShader, fragmentShader);

	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 
	glUseProgram(shaderProgram);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void Demo::TestDemo_3()
{
	// create window
	GLFWwindow* window = GLFWWindowUtils::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return;
	}

	Shader ourShader("../../../source/Demo/GLSL/Demo_4/shader.vs", "../../../source/Demo/GLSL/Demo_4/shader.fs");  // 此处如果是相对路径，是相对Demo工程的相对路径

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// load and create texture
	// ---------------------------------
	unsigned int textureBuffer1 = GLFWWindowUtils::LoadTexture("../../../source/Demo/images/container.jpg");

	unsigned int textureBuffer2 = GLFWWindowUtils::LoadTexture("../../../source/Demo/images/awesomeface.jpg");

	ourShader.useProgram(); // 设置uniform变量之前需要先激活着色器程序！
	ourShader.setInt("inputBoxTexture", 0);
	ourShader.setInt("inputFaceTexture", 1);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		modelMatrix = glm::rotate(modelMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
		projectionMatrix = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

		ourShader.setMat4("modelMatrix", modelMatrix);
		ourShader.setMat4("viewMatrix", viewMatrix);
		ourShader.setMat4("projectionMatrix", projectionMatrix);

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureBuffer1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureBuffer2);

		// render the triangle
		ourShader.useProgram();

		// 对 shader 代码中uniform 值的修改，需要再程序启动之后，才能去制定的程序中去找到对应的值
		// float offset = 0.5f;
		// ourShader.setFloat("xOffset", offset);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void Demo::TestDemo_4()
{
	GLFWwindow* window = GLFWWindowUtils::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return;
	}

	// 关掉鼠标标志
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 设置回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, &MouseMoveCallBack);
	glfwSetScrollCallback(window, &ScrollCallBack);

	Shader ourShader("../../../source/Demo/GLSL/Demo_4/shader.vs", "../../../source/Demo/GLSL/Demo_4/shader.fs");  // 此处如果是相对路径，是相对Demo工程的相对路径

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	unsigned int VBO, VAO/*, EBO*/;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 加载材质图片
	unsigned int textureBuffer1 = GLFWWindowUtils::LoadTexture("../../../source/Demo/images/container.jpg");
	unsigned int textureBuffer2 = GLFWWindowUtils::LoadTexture("../../../source/Demo/images/awesomeface.jpg");

	ourShader.useProgram(); // 设置uniform变量之前需要先激活着色器程序！
	ourShader.setInt("inputBoxTexture", 0);
	ourShader.setInt("inputFaceTexture", 1);

	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	// 声明一个相机放在 （0,0,3) 观察 (0,0,0)
	//Camera camera(glm::vec3(0, -10.0f, 10.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// 相机位置 (0, 0.0f, 3.0f)， pitch 0度，yaw 180.0度，相当于时向后看，即向z轴负方向看
	//Camera camera(glm::vec3(0, 0.0f, 3.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1, 0));

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // glEnable(GL_DEPTH_TEST);  // 添加了深度缓冲后，需要同时清理深度缓冲，否则前一帧的深度信息仍然保存在缓冲中

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureBuffer1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureBuffer2);

		ourShader.useProgram();
		glBindVertexArray(VAO);

		// 由于相机的一些参数会因为鼠标键盘事件而发生改变，所以不同的时间获取的相机参数是不一样的
		// 需要把获取参数的动作放在循环中，这样才能实时刷新参数
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		viewMatrix = camera.GetViewMatrix();
		projectionMatrix = glm::perspective(glm::radians(camera.GetZoom()), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		for (unsigned int i = 0; i < 10; i++)
		{
			//glm::mat4 model;
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
			float angle = 20.0f * i;
			//if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
			//	angle = float(glfwGetTime() * 25.0f);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			ourShader.setMat4("modelMatrix", modelMatrix);
			ourShader.setMat4("viewMatrix", viewMatrix);
			ourShader.setMat4("projectionMatrix", projectionMatrix);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

void Demo::TestDemo2_1()
{
	GLFWwindow* window = GLFWWindowUtils::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return;
	}

	// 设置回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, &MouseMoveCallBack);
	glfwSetScrollCallback(window, &ScrollCallBack);

	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	Shader lightShader("../../../source/Demo/GLSL/Demo2_1/lightShader.vs", "../../../source/Demo/GLSL/Demo2_1/lightShader.fs");  // 此处如果是相对路径，是相对Demo工程的相对路径
	Shader cubeShader("../../../source/Demo/GLSL/Demo2_1/cubeShader.vs", "../../../source/Demo/GLSL/Demo2_1/cubeShader.fs");

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

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

	unsigned int VBO, lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	// timing ？？ 干嘛用？
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// lighting
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // glEnable(GL_DEPTH_TEST);  // 添加了深度缓冲后，需要同时清理深度缓冲，否则前一帧的深度信息仍然保存在缓冲中

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		glm::mat4 projectionMatrix = glm::mat4(1.0f);

		{
			lightShader.useProgram();
			lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
			lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			lightShader.setVec3("lightPos", lightPos);
			lightShader.setVec3("viewPos", camera.m_position);

			// 由于相机的一些参数会因为鼠标键盘事件而发生改变，所以不同的时间获取的相机参数是不一样的
			// 需要把获取参数的动作放在循环中，这样才能实时刷新参数
			viewMatrix = camera.GetViewMatrix();
			projectionMatrix = glm::perspective(glm::radians(camera.GetZoom()), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

			lightShader.setMat4("model", modelMatrix);
			lightShader.setMat4("view", viewMatrix);
			lightShader.setMat4("projection", projectionMatrix);

			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		{
			lightPos.x = float(1.0f + sin(glfwGetTime()) * 2.0f);
			lightPos.y = float(sin(glfwGetTime() / 2.0f) * 1.0f);
			// also draw the lamp object
			cubeShader.useProgram();
			cubeShader.setMat4("projection", projectionMatrix);
			cubeShader.setMat4("view", viewMatrix);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			cubeShader.setMat4("model", model);

			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}