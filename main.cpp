#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <ios>
#include <sstream>  
#include <string>  
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>	
#include "loadShader.hpp"
#include "triangulo.h"
#include "poligono.h"

/*
//inicio opengl glad

	X in on your right
	Y is up
	Z is towards your back (yes, behind, not in front of you)


void user_redimensiona_janela_callback(GLFWwindow* window, int width, int height)
{
	//alterar a janela de renderizacao quando o utilizador redimensiona a janela de modo a ficar sempre justo
	glViewport(0, 0, width, height);
}
int main() {
	//inicializar glfw e configurar
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// configuracao da janela e da versao do opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//criar janela
	int winW = 1280, winH = 720;
	GLFWwindow* janela = glfwCreateWindow(winW, winH, "Primeiro Prog OpenGL", NULL, NULL);
	if (janela == NULL) {
		std::cout << "falha a criar a janela, vou abortar" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(janela);

	//inicializar glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, winW, winH);
	glfwSetFramebufferSizeCallback(janela, user_redimensiona_janela_callback);//mudar o tamanho da janela e tamanho de onde e renderizado

	//loop janela
	while (!glfwWindowShouldClose(janela))
	{
		glfwSwapBuffers(janela);
		glfwPollEvents();
	}

}

*/



//void user_redimensiona_janela_callback(GLFWwindow* window, int width, int height)
//{
//	//alterar a janela de renderizacao quando o utilizador redimensiona a janela de modo a ficar sempre justo
//	glViewport(0, 0, width, height);
//}
//bool r = true, g=false, b = false;
//void processarInputTeclado(GLFWwindow* janela) {
//	if (glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(janela, GLFW_KEY_SPACE) == GLFW_PRESS) { //glfwGetKey() se nao for carregada devolve GLFW_RELEASE
//		glfwSetWindowShouldClose(janela, true); //fechar a janela ao carregar no esc
//	}
//	if (glfwGetKey(janela, GLFW_KEY_Q) == GLFW_PRESS) {
//	
//	}
//}
//
//
//int main() {
//	std::cout << "ola" << std::endl;
//	int winW = 1280, winH = 720;
//	glfwInit(); // inicializar a biblioteca glfw
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // configuracao da janela e da versao do opengl
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We also tell GLFW we want to explicitly use the core-profile. Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need. 
//
//	GLFWwindow* janela = glfwCreateWindow(winW, winH, "Primeiro Prog OpenGL", NULL, NULL);
//	if (janela == NULL) {
//		std::cout << "falha a criar a janela, vou abortar" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(janela);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //inicializar GLAD
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//	glViewport(0, 0, winW, winH); //dizer ao opengl o tamanho da janela de renderizacao para que o opengl saiba como e que queremos renderizar as informacoes e coordenadas de acordo com a janela
//	//os dois 0,0 referem se ao canto inferior esquerdo e os outros dois definem o comprimento e largura da janela de renderizacao em pixeis (igual ao tamanho da janela)
//	glfwSetFramebufferSizeCallback(janela, user_redimensiona_janela_callback);
//
//
//	/*
//		LER O QUE ESTA NESTES COMENTARIOS SE TIVER DUVIDAS, MAS A ORDEM DO CODIGO ESTA MUITO CONFUSA POR ISSO DECIDI COPIAR E COLAR DO SITE
//	
//	*/
//	
//	//float verticesTriangulo[] = { //OpenGL é em 3D por isso tem que se dar as tres coords,xyz
////								//para renderizar o triangulo em 2D metemos as coords de Z a 0
////	-0.5f,-0.5f,0.0f,
////	0.5f,-0.5f,0.0f,
////	0.0f,0.5f,0.0f
////};
////
////unsigned int VBO, VAO;
////glGenBuffers(1, &VBO);
////
////// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//////Initialization code(done once(unless your object frequently changes)) :: ..
////glBindVertexArray(VAO);
////
////glBindBuffer(GL_ARRAY_BUFFER, VBO); //ligar o buffer criado (VBO) ao array de buffer
////									//From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer, which is VBO. 
////glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangulo), verticesTriangulo, GL_STATIC_DRAW);//copiar os dados dos vertices para o buffer
//////o primeiro arg é o tipo de buffer para onde queremos copiar a info, o segundo arg determina o tamanho da info,
//////o terceiro é a info que queremos enviar em si, o ultimo arg especifica de que modo a grafica vai gerir os dados
////									/*
////									GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
////									GL_STATIC_DRAW : the data is set only once and used many times.
////									GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
////						//a posicao do triangulo nao muda, é usada bastante
////									*/
////const char* vertexShaderSource = "#version 460 core\n"
////	"layout (location = 0) in vec3 aPos;\n"
////	"void main()\n"
////	"{\n"
////	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
////	"}\0";
////const char* fragmentShaderSource = "#version 460 core\n"
////	"out vec4 FragColor;\n"
////	"void main()\n"
////	"{\n"
////	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
////	"}\n\0";
////unsigned int vertexShader; //criar objeto de shader para depois ser compilado em runtime
////vertexShader = glCreateShader(GL_VERTEX_SHADER);
////
////
////int  success; //verificar se a compilacao teve sucesso, se tiver sucesso o vertex shader está compilado
////char infoLog[512];
////glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
////if (!success) {
////	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
////	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
////}
////
////
////
////unsigned int fragmentShader; //mesmo processo para o shader vertex
////fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //a unica diferenca
////glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
////glCompileShader(fragmentShader);
////glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
////if (!success) {
////	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
////	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
////}
////
////unsigned int shaderProgram; //shader programs são um objeto que contem a versao final linkada de varios shaders combinados
////shaderProgram = glCreateProgram();//criar o programa, retorna o ID do programa
////								  //depois é preciso pegar nos shaders compilados e ligá-los ao programa
////glAttachShader(shaderProgram, vertexShader);
////glAttachShader(shaderProgram, fragmentShader);
////glLinkProgram(shaderProgram);
////glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
////if (!success) {
////	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
////	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
////}
////
////
////glDeleteShader(vertexShader);//como ja estam todos linkados podemos simplesmente dar delete
////glDeleteShader(fragmentShader);
////
////// 0. copy our vertices array in a buffer for OpenGL to use
////glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
////glCompileShader(vertexShader);
////// 1. then set the vertex attributes pointers
////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//////o primeiro arg refere qual o vertice que queremos configurar "Remember that we specified the location of the position vertex attribute in the vertex shader with layout (location = 0). This sets the location of the vertex attribute to 0 and since we want to pass data to this vertex attribute, we pass in 0."
//////o segundo arg especifica o tamanho do atributo do vertice, como é um vec3 metemos 3
//////o terceiro especifica o tipo de dados que estamos a usar (a vec* in GLSL consists of floating point values)
//////o quarto pergunta se queremos que os dados sejam normalizados (se estivessemos a usar ints e bytes, colocariamos GL_TRUE (the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float.) 
//////o quinto arg é uma 'stride' e diz-nos o espaço entre os atributos dos vertices consecutivos, Since the next set of position data is located exactly 3 times the size of a float away we specify that value
////		//podiamos deixar a 0 pois sabemos que os valores estao tightly packed
//////o ultimo é o offset de onde os dados comecam no buffer, como comeca em 0 colocamos 0, necessita do void porcausa do parametro
////glEnableVertexAttribArray(0);
////// 2. use our shader program when we want to render an object
////glUseProgram(shaderProgram);
////// 3. now draw the object 
//
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"   FragColor = vec4(1.0f, 5.0f, 5.0f, 1.0f);\n"
//		"}\n\0";
//
//
//	// build and compile our shader program
//	// ------------------------------------
//	// vertex shader
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	// check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	// fragment shader
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//	// check for shader compile errors
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	// link shaders
//	unsigned int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	// check for linking errors
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		// 0.5f,  0.5f, 0.0f,  // top right
//		// 0.5f, -0.5f, 0.0f,  // bottom right
//		//-0.5f, -0.5f, 0.0f,  // bottom left
//		//-0.5f,  0.5f, 0.0f,   // top left 
//		//-0.1f,0.0f,0.1f, //a-0
//		//0.0f,0.0f,0.2f,	 //b-1
//		//0.3f,0.0f,0.3f,	 //c-2
//		//0.3f,-0.1f,0.4f,	 //d-3
//		//-0.0f,-0.1f,0.5f,//e-4
//		//0.0f,-0.5f,0.6f, //f-5
//		//-0.1f,-0.5f,0.7f //g-6
//		-0.1f,0.20f
//		
//	};
//	unsigned int indices[] = {  // note that we start from 0!
//		0,1,5,
//		0,5,6,
//		1,2,4,
//		2,3,4
//	};
//	unsigned int VBO, VAO, EBO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//
//
//	// uncomment this call to draw in wireframe polygons.
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	while (!glfwWindowShouldClose(janela))//loop para renderizar enquanto a janela estiver aberta
//	{ //Uma frame é cada iteração deste loop!!
//		processarInputTeclado(janela);
//		glfwSwapBuffers(janela);//nao percebi muito bem o que faz mas é o que esta aqui em baixo 
//								//ou em "seccao Ready your engines" https://learnopengl.com/Getting-started/Hello-Window 
//								//will swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen. 
//		glClearColor(0.0f, 0.5f, 1.0f, 1.0f); //cor de fundo
//		glClear(GL_COLOR_BUFFER_BIT);
//
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//
//		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //6 é o numero de vertices a desenhar
//		glBindVertexArray(0);
//
//		glfwPollEvents(); //verifica se algum evento foi "triggered" (tipo interrupts de teclado ou rato)
//						  //faz update ao state da janela e chama as funcoes callback definidas por nós
//	}
//
//
//
//	glDeleteProgram(shaderProgram);
//	glfwTerminate(); //terminar corretamente e deletes e essas cenas
//	return 0;
//}
//
//



//X in on your right
//Y is up
//Z is towards your back(yes, behind, not in front of you)





void processarInputKeyboard(GLFWwindow* janela, poligono *r1) {
	if (glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwGetKey(janela, GLFW_KEY_KP_ENTER) == GLFW_PRESS or glfwGetKey(janela, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(janela, true);
	}
	else if (glfwGetKey(janela, GLFW_KEY_UP) == GLFW_PRESS) {
		r1->mover(1); r1->printarCoords();
	}
	else if (glfwGetKey(janela, GLFW_KEY_DOWN) == GLFW_PRESS) {
		r1->mover(2);
		r1->printarCoords();
	}
	
}
int winW = 1280, winH = 720;
void user_redimensiona_janela_callback(GLFWwindow* window, int width, int height)
{
	winW = width;
	winH = height;
	//alterar a janela de renderizacao quando o utilizador redimensiona a janela de modo a ficar sempre justo
	glViewport(0, 0, width, height);
}


/*
int main() {
	//inicializar glfw e configurar
	if (!glfwInit()) {
		std::cout << "failed to initialize glfw";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// configuracao da janela e da versao do opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//criar janela
	int winW = 1280, winH = 720;
	GLFWwindow* janela = glfwCreateWindow(winW, winH, "Primeiro Prog OpenGL", NULL, NULL);
	if (janela == NULL) {
		std::cout << "falha a criar a janela, vou abortar" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(janela);

	//inicializar glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	


	glViewport(0, 0, winW, winH);
	glfwSetFramebufferSizeCallback(janela, user_redimensiona_janela_callback);//mudar o tamanho da janela e tamanho de onde e renderizado

	static GLfloat cores[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
	};

	GLfloat vertices[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,//
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};
	
	triangulo t;

	GLuint VertexArrayID; //VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);//gerar 1 buffer e guardar na variavel
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //ligarg o buffer ao array de buffers do opengl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);//gerar 1 buffer e guardar na variavel
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); //ligarg o buffer ao array de buffers do opengl
	glBufferData(GL_ARRAY_BUFFER, sizeof(cores), cores, GL_STATIC_DRAW);

	GLuint programID = CarregarShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
	

	//matriz projeção: arg1 - FOV DE 45º, arg2 - aspect ratio, arg3 e 4 - display range 
	glm::mat4 Projection = glm::perspective(glm::radians(90.0f), (float)winW / (float)winH, 
		0.1f,  // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f);  // Far clipping plane. Keep as little as possible.
	
	//matriz da camara
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//matriz modelo (model matrix): matriz identidade, modelo (model), vai estar na origem
	glm::mat4 Model = glm::mat4(1.0f); //criacao de matriz identidade
	
	//ModelViewProjection (MVP): multiplicacao das 3 matrizes anteriores
	glm::mat4 mvp = Projection * View * Model;
	
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	

	//"organizar" a renderizacao de modo a nao haver sobreposicao de triangulos que deviam estar atras
	// 	   pode se fazer isto manualmente tambem
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	GLfloat variavelParaAlterarCoresDoCubo = 0.0f;
	//loop janela
	while (!glfwWindowShouldClose(janela))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID); //usar o shader criado
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		
		//alterar cores do cubo
		//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer); //ligarg o buffer ao array de buffers do opengl
		//glBufferData(GL_ARRAY_BUFFER, sizeof(cores), cores, GL_STATIC_DRAW);
		//for (int v = 0; v < 12 * 3 * 3; v++) {
		//	variavelParaAlterarCoresDoCubo = variavelParaAlterarCoresDoCubo + 0.01f;
		//	if (variavelParaAlterarCoresDoCubo >= 1.0f)
		//		variavelParaAlterarCoresDoCubo = 0.0f;
		//	cores[v] = variavelParaAlterarCoresDoCubo;
		//}


		
		//attribute buffer: vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		//attribute buffer: cores
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		
		// Draw the cube !

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(GLfloat)); // Starting from vertex 0; 12*3 vertices total -> 12 triangle
		glDisableVertexAttribArray(0);
		

		t.desenhar();
		//glDisableVertexAttribArray(1);

		
		
		// Draw the cube !
		
		
		



		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


		processarInputKeyboard(janela);
		glfwSwapBuffers(janela);
		glfwPollEvents();
	}
}
*/

int quadranteCentro(GLfloat* centro) {
	if (centro[0] <= 0)//esta no 1 ou 3 quadrante
	{
		if (centro[1] >= 0) //esta no 1 quadrante
		{
			return 1;
		}
		return 3;
	}
	else { //esta no 2 ou 4 quadrante
		if (centro[1] >= 0) //esta no 2 quadrante
		{
			return 2;
		}
		return 4;
	}
}

void verificarColisao(poligono* r1, poligono* r2, bolaPong* bola) {
	
	//ver direcao da bola, se for para a esquerd vai colidir com r1, se for direita colide com r2
	int direcaoBola = bola->getDirecao();
	
	if (direcaoBola == 3 or direcaoBola == 5 or direcaoBola == 7) //esquerda
	{//vai colidir com r1
		auto centroR = r1->centro;
		auto centroBola = bola->centro;
		auto posB = centroBola[0] 
			, posR = centroR[0] ;
		int quadrante = quadranteCentro(centroR);
		if (posB <= posR) {		
			bola->mudarDirecao(6);
		}
		else {

		}
		//bola->mudarDirecao(4);
	}
	else { //vai colidir com r2
		auto centroR = r2->centro;
		auto centroBola = bola->centro;
		auto posB = centroBola[0]
			, posR = centroR[0];

		if (posB >= posR) {
			bola->mudarDirecao(3);
		}
		else {

		}
		//bola->mudarDirecao(4);
	}




	
}

int main() {
	//inicializar glfw e configurar
	if (!glfwInit()) {
		std::cout << "failed to initialize glfw";
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// configuracao da janela e da versao do opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//criar janela
	
	GLFWwindow* janela = glfwCreateWindow(winW, winH, "Primeiro Prog OpenGL", NULL, NULL);
	if (janela == NULL) {
		std::cout << "falha a criar a janela, vou abortar" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(janela);

	//inicializar glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	glViewport(0, 0, winW, winH);
	glfwSetFramebufferSizeCallback(janela, user_redimensiona_janela_callback);//mudar o tamanho da janela e tamanho de onde e renderizado

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	GLuint programID = CarregarShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
	
	GLfloat r1Vertices[6*3] = {
		-0.9f,0.35f,0.0f,
		-0.9f,-0.35f,0.0f,
		-0.8f,-0.35f,0.0f,
		-0.9f,0.35f,0.0f,
		-0.8f,0.35f,0.0f,
		-0.8f,-0.35f,0.0f
	};
	GLfloat largura, comprimento;
	largura = 0.9f - 0.8f; comprimento = 0.35f + 0.35f;
	poligono*r1 = new poligono(r1Vertices,sizeof(r1Vertices),largura, comprimento, -0.7f,0.0f,0.0f);

	GLfloat r2Vertices[6 * 3] = {
		0.9f,0.35f,0.0f,
		0.9f,-0.35f,0.0f,
		0.8f,-0.35f,0.0f,
		0.9f,0.35f,0.0f,
		0.8f,0.35f,0.0f,
		0.8f,-0.35f,0.0f
	};

	InimigoIA* r2 = new InimigoIA(r2Vertices, sizeof(r2Vertices), largura, comprimento, 0.7f, 0.0f, 0.0f);

	GLfloat bolaVertices[6*3] = {
		   0.1f,0.1f,0.0f,
		   -0.1f,0.1f,0.0f,
		   0.1f,-0.1f,0.0f,
		   0.1f,-0.1f,0.0f,
		   -0.1f,0.1f,0.0f,
		   -0.1f,-0.1f,0.0f

	};
	largura = 0.1f; comprimento = 0.1f;
	bolaPong* bola = new bolaPong(bolaVertices, sizeof(bolaVertices), largura, comprimento, 0.0f, 0.0f, 0.0f);
	//bola->mudarDirecao(4);


	
	
	while (!glfwWindowShouldClose(janela))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID); //usar o shader criado
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		
		r1->draw();
		r2->andarAutomatico();
		bola->andarBola();
		r2->draw();
		bola->draw();
		
		verificarColisao(r1, r2, bola);

		processarInputKeyboard(janela,r1);
		glfwSwapBuffers(janela);
		glfwPollEvents();
	}
	delete r1;
	delete r2;
	delete bola;
}