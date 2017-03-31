//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include "../soil/src/SOIL.h"
#include "glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "../Shader.h"
using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
GLsizei numBuffers = 3;
float switcher = 0.0;
float angle = 0.0;
bool rotateLeft, rotateRight; 
float aspectRatio = WIDTH / HEIGHT;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	//initGLFW
	glEnable(GL_DEPTH_TEST);
	if (!glfwInit())
		::exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Trasform.", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		::exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);


	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}
	
	//viewPort
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//set function when callback
	glfwSetKeyCallback(window, key_callback);


	//fondo
	glClearColor(0.5, 0, 0.5, 1.0);
	
	//cargamos los shader
	Shader squareShader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader textureShader("./src/textureVertex.vertexshader", "./src/textureFragment.fragmentshader");
	Shader cubeShader("./src/cubeVertex.v", "./src/cubeFragment.f");

	// Definir el buffer de vertices

	//cuadrado
	GLfloat vertexBufferObject[] = { 
				
		0.5f, 0.5f, 0.f, //  0. top right
		0.5f, -0.5f, 0.f,//   1. bot right
		-0.5f, -0.5f, 0.f,//    2. bot left
		-0.5f, 0.5f, 0.f, //  3. top left
		
	};

	//textura
	GLfloat vertices[] = {
		//  Position      Color             Texcoords
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
		0.5f,  0.5f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	GLfloat textureBufferObject[] = {

		0.5f, 0.5f, 0.f, //  0. top right
		0.5f, -0.5f, 0.f,//   1. bot right
		-0.5f, -0.5f, 0.f,//    2. bot left
		-0.5f, 0.5f, 0.f, //  3. top left

	};

	//cube

	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 CubesPositionBuffer[] = {
		glm::vec3(0.0f ,  0.0f,  0.0f),
		glm::vec3(2.0f ,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f , -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f , -2.0f, -2.5f),
		glm::vec3(1.5f ,  2.0f, -2.5f),
		glm::vec3(1.5f ,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// load textures
	int width, height;
	unsigned char *img;
	
	GLint texAttrib = glGetAttribLocation(textureShader.Program, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		8 * sizeof(float), (void*)(6 * sizeof(float)));

	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	img = SOIL_load_image("gr8.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	
	
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	img = SOIL_load_image("fire.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	SOIL_free_image_data(img);
	
	//ordre dels vertex dels triangles del quadrat
	GLuint indexBufferObject[] = {
		0, 1, 3, 
		1, 2, 3
	};

	
	// Crear los VBO, VAO y EBO y reservar memoria para el VAO, VBO y EBO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//delete[] vertexBufferObject;

	//GLuint VBO2;
	//glGenBuffers(1, &VBO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(CubesPositionBuffer), CubesPositionBuffer, GL_STATIC_DRAW);
	
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBufferObject), indexBufferObject, GL_STATIC_DRAW); // 1 = SIZEOF INDEXBUFFEROBJECT  0 = INDEXBUFFEROBJECT

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0); 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0); 
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	GLint variableShader =  glGetUniformLocation(squareShader.Program, "Sion"); //enllaçar amb variable dins els " "
	GLint imgSwitcher = glGetUniformLocation(textureShader.Program, "alternador");
	GLint uniTrans = glGetUniformLocation(textureShader.Program, "trans");
	GLint uniView = glGetUniformLocation(textureShader.Program, "view");
	GLint uniProj = glGetUniformLocation(textureShader.Program, "proj");

	GLint uniModel = glGetUniformLocation(cubeShader.Program, "model");
	GLint uniView2 = glGetUniformLocation(cubeShader.Program, "view");
	GLint uniProj2 = glGetUniformLocation(cubeShader.Program, "proj");

	//Matrius

	glm::mat4 trans;
	glm::mat4 view = glm::lookAt(
		glm::vec3(1.2f, 1.2f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 proj = glm::perspective(glm::radians(60.0f), aspectRatio, 1.0f, 10.0f);

	

	//bucle de dibujado
	while (!glfwWindowShouldClose(window)) {
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borrar buffer de colors i de profunditat

		//Establecer el color de fondo
		glClearColor(0.5, 0.2, 1.0, 1.0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//establecer el shader
		//squareShader.USE(); //descomentar aixo si volem veure es quadrat
	    //textureShader.USE();
		cubeShader.USE();

		// passar valors a les variables dels shaders
		glUniform1f(variableShader, abs(sin(glfwGetTime())/2)); 
		glUniform1f(imgSwitcher, switcher);

		trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
		//comprovar si rotar foto
		if (rotateLeft)
			angle = 0.1;
		if (rotateRight)
			angle = -0.1;
		
		// mesclar foto
		if (switcher > 1) 
			switcher = 1;
		
		if (switcher < 0.1)
			switcher = 0;

		//activar textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(textureShader.Program, "tex1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(textureShader.Program, "tex2"), 1);

		glBindVertexArray(VAO);

		//pintar el VAO
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
		glDrawArrays(GL_TRIANGLES, 0, 1);
		// cuadrat que s'estira
		if (WIDEFRAME) {
			
			//pintar amb linies
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glDrawElements(GL_LINE_STRIP, 7, GL_UNSIGNED_INT, (GLvoid*)0);
			glBindVertexArray(0);

		}

		else {
			//pintar amb triangles
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
			glBindVertexArray(0);

		}
		// Swap the screen buffers. !!!!!!!!Molt important!!!!!
		glfwSwapBuffers(window);
		//comprueba que algun disparador se haya activado (tales como el teclado, raton, etc)
		glfwSetKeyCallback(window, key_callback);
		glfwPollEvents();
	}

	//rentar sa memoria
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	::exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
		glfwSetWindowShouldClose(window, GL_TRUE);

		else if (key == GLFW_KEY_W && action == GLFW_PRESS && WIDEFRAME == false) {
			WIDEFRAME = true;

		}
		else if (key == GLFW_KEY_W && action == GLFW_PRESS && WIDEFRAME == true) {
			WIDEFRAME = false;
		}
		else if ((key == GLFW_KEY_UP && action == GLFW_PRESS)) {
			switcher += 0.1;
		}
		else if ((key == GLFW_KEY_DOWN && action == GLFW_PRESS)) {
			switcher -= 0.1;
		}
		else if ((key == GLFW_KEY_RIGHT && action == GLFW_PRESS)) {
			rotateRight = true;
		}
		else if ((key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)) {
			rotateRight = false;
			angle = 0;
		}
		else if ((key == GLFW_KEY_LEFT && action == GLFW_PRESS)) {
			rotateLeft = true;
		}
		else if ((key == GLFW_KEY_LEFT && action == GLFW_RELEASE)) {
			rotateLeft = false;
			angle = 0;
		}
		
}