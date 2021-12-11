#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "Demo.h"

void processInput(GLFWwindow *window);

int main()
{
	Demo::TestDemo_3();
	/*
    // glfw: initialize and configure
	Demo::InitGlfw();

	// create window
	GLFWwindow* window = Demo::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
	if (!window)
	{
		return -1;
	}

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	unsigned int vertexShader = Demo::CreateVertexShader();
	unsigned int fragmentShader = Demo::CreateFragmentShader();
	unsigned int shaderProgram = Demo::LinkShaders(vertexShader, fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// glBindVertexArray(0);  // unbind

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, 0);  // unbind
	// glBufferData() : copy user-defined data to the current binding buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//	Tell OpenGL how to parse the vertex data
	//  need bind Vertex Array(bind VAO) before this function
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  // 6 is the same as "layout (location = 6)" in vertexShader

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);  // 6 is the same as "layout (location = 6)" in vertexShader

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// cull face
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue = float(glfwGetTime());
		//float red = 0.0f;
		//float green = sin(timeValue) / 2.0f + 0.5f;
		//float blue = 0.0f;
		//float alpha = 1.0f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		//glUniform4f(vertexColorLocation, red, green, blue, alpha);

		// draw triangle
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();*/
    return 0;
}

