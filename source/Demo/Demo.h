#pragma  once

struct GLFWwindow;
struct GLFWmonitor;

class Demo
{
public:
	static unsigned int CreateVertexShader(const char* vertexShaderSource);
	static unsigned int CreateFragmentShader(const char* fragmentShaderSource);
	static unsigned int LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);

	static void TestDemo_1();
	static void TestDemo_2();
	static void TestDemo_3();
	static void TestDemo_4();

	static void TestDemo2_1();

	static void TestDemo3_1();
};
