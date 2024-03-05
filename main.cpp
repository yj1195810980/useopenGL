#include <iostream>
#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
//�ص��������ڴ�С��������ʱ�򱻵���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//������Ӧ
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//������ɫ��Դ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";


//Ƭ����ɫ��Դ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{"
"FragColor = ourColor;\n"
"}\n";



int main() {
	//��ʼ��
	int nRet = glfwInit();
	if (nRet != 1)
	{
		return 0;//ʧ�ܷ��ط�1
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//���ڷ�Ӧ�ص�


	//��������
    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // ���Ͻ�
            0.5f, -0.5f, 0.0f,  // ���½�
            -0.5f, -0.5f, 0.0f, // ���½�
            -0.5f, 0.5f, 0.0f   // ���Ͻ�
    };

    unsigned int indices[] = {
            // ע��������0��ʼ!
            // ����������(0,1,2,3)���Ƕ�������vertices���±꣬
            // �����������±��������ϳɾ���

            0, 1, 3, // ��һ��������
            1, 2, 3  // �ڶ���������
    };


	unsigned int VBO;
	glGenBuffers(1, &VBO);//�������㻺����󡣸ö�����Թ��������ݣ�ע�⣺�����Ƕ�����ɫ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨶��㻺�����GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//�����������뵽���㻺�����󶨵Ļ�������ȥ
	//����Ļ������������Դ�

	//����������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//��ɫ��Դ�븽�Ӷ�����ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//��ɫ��Դ�����
	glCompileShader(vertexShader);

	//������ɫ��Դ���Ƿ����ɹ�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



	//����Ƭ����ɫ������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Ƭ����ɫ��������Ƭ����ɫ����
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Ƭ����ɫ������
	glCompileShader(fragmentShader);



	//��ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//���������ɫ�����ӵ���ɫ������
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//���ӵ���ɫ���Ƿ����
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::shaderProgram\n" << infoLog << std::endl;
	}

	//������ɫ��
	glUseProgram(shaderProgram);


	//ɾ����ɫ������
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	////���Ӷ�������
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//���������������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //������������
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 3. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//��ȡ��������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//���������Ļ����ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����ɫ

		//������ɫ��
		glUseProgram(shaderProgram);

		// ����uniform��ɫ
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


		glfwSwapBuffers(window);//����Ƿ�Ҫ���˳�

		glfwPollEvents();//����¼�
	}


	//�ͷ�
	glfwTerminate();
	return 0;
}
