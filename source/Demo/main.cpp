#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include "Demo.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



int main()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	// ��ע��������Ǿ����ʼ����һ�����ӣ����ʹ�õ���0.9.9�����ϰ汾
	// �������д������Ҫ��Ϊ:
	// glm::mat4 trans = glm::mat4(1.0f)
	// ֮�󽫲��ٽ�����ʾ
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;


	Demo::TestDemo_3();
	
	system("pause");
    return 0;
}

