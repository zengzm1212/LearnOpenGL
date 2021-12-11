#pragma  once

struct GLFWwindow;
struct GLFWmonitor;

class Demo
{
public:
	static void InitGlfw();

	static GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

	static unsigned int CreateVertexShader(const char* vertexShaderSource);
	static unsigned int CreateFragmentShader(const char* fragmentShaderSource);
	static unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);

	static void TestDemo_1();
	static void TestDemo_2();
	static void TestDemo_3();
};
