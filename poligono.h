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
#include <glm/gtc/type_ptr.hpp>
#define DIR_CIM 1
#define DIR_BAI 2
#define DIR_ESQ 3
#define DIR_DIR 4
#define DIR_CIMAESQ 5
#define DIR_CIMADIR 6
#define DIR_BAIXOESQ 7
#define DIR_BAIXODIR 8

class poligono { 
protected:
	GLfloat *vertices = NULL;
	GLuint vertexbuffer;
	int nVertices;
	GLfloat valorMov = 0.05f;
	GLfloat* verticesIniciais = NULL;
	
public:
	GLfloat comprimento, largura, centro[3];
	int getNVertices() {
		return nVertices;
	}
	void alterarValorDeMovimento(GLfloat a) {
		valorMov = a;
	}


	poligono(GLfloat* vertices_, std::size_t sizeofVertices, GLfloat larg, GLfloat comp, GLfloat centX, GLfloat centY, GLfloat centZ) {
		largura = larg;
		comprimento = comp;
		centro[0] = centX;
		centro[1] = centY;
		centro[2] = centZ;
		int nVertices_ = sizeofVertices / sizeof(GLfloat);
		nVertices = nVertices_;
		vertices = (GLfloat*)malloc(sizeof(GLfloat) * nVertices_);
		for (int i = 0; i < nVertices_; i++) {
			vertices[i] = vertices_[i];

		}
		verticesIniciais = (GLfloat*)malloc(sizeof(GLfloat) * nVertices_);
		for (int i = 0; i < nVertices_; i++) {
			verticesIniciais[i] = vertices_[i];

		}

		glGenBuffers(1, &vertexbuffer);//gerar 1 buffer e guardar na variavel
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //ligarg o buffer ao array de buffers do opengl
		glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices)*nVertices, vertices, GL_STATIC_DRAW);

	};
	
	void draw() {
	
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

		glDrawArrays(GL_TRIANGLES, 0, sizeof(*vertices) / sizeof(GLfloat) * nVertices); // Starting from vertex 0; 12*3 vertices total -> 12 triangle
		glDisableVertexAttribArray(0);
		
	}
	
	~poligono() {
		free(vertices);
		free(verticesIniciais);
	}
	
	bool podeAndarCima(){
		bool resultado = true;
		for (int i = 0; i < nVertices; i++) {
			if(i%3 == 1)
				if (vertices[i] >= 1.0f)
				{
					resultado = false;
					vertices[i] = 1.0f;
				}
		}

		return resultado;
	}
	bool podeAndarBaixo() {
		bool resultado = true;
		for (int i = 0; i < nVertices; i++) {
			if (i % 3 == 1)
				if (vertices[i] <= -1.0f)
				{
					resultado = false;
					vertices[i] = -1.0f;
				}
		}

		return resultado;
	}
	void mover(int direcao) {
		bool podeMover = true;
		switch (direcao) {
			case 1: //cima
				//Matriztranslacao = glm::translate(glm::mat4(1.0f), glm::vec3(0.10f, 0.0f, 0.0f));
				podeMover = podeAndarCima();
				if (!podeMover)
					return;
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 1)
						vertices[i] = vertices[i] + valorMov;

				}
				centro[2] = centro[2]+ valorMov;
				break;
			case 2: //baixo
				podeMover = podeAndarBaixo();
				if (!podeMover)
					return;
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 1)
						vertices[i] = vertices[i] - valorMov;
				}
				centro[2] = centro[2] - valorMov;
				break;
			case 3: //esquerda
				break;
			case 4: //direita
				break;
			default:
				break;
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices, vertices, GL_STATIC_DRAW);
	}

	void colocarNaPosicaoInicial() {
		for (int i = 0; i < nVertices; i++) {
			vertices[i] = verticesIniciais[i];
		}
	}

	void printarCoords() {
		std::cout << "------------------------------------" << std::endl;
		for (int i = 0; i < nVertices; i++) {
			std::cout << vertices[i];
			if (i % 3 == 0 and i>0) {
				std::cout << std::endl;
			}
		}
		std::cout << "------------------------------------" << std::endl;
	}
};

class bolaPong : public poligono {
	int direcao; //1 cima, 2 baixo, //realisticamente nunca vai andar diretamente para cima ou para baixo
					//3 esq, 4 dir, 5 cima esq, 6 cima dir, 7 baixo esq, 8 baixo dir
	bool Anda = true;
public:
	void andaOuNao(bool a) {
		Anda = a;
	}
	int getDirecao() {
		return direcao;
	}
	void mudarDirecao(int dir) {
		direcao = dir;
	}
	bolaPong(GLfloat* vertices_, std::size_t sizeofVertices,  GLfloat larg, GLfloat comp, GLfloat centX, GLfloat centY, GLfloat centZ, GLfloat valorMovimento = 0.01f, int dire = 3)
		: poligono(vertices_, sizeofVertices, larg, comp,centX, centY, centZ) {
		valorMov = valorMovimento;
		direcao = dire;
	}
	
	int andarBola() { //0 se nao acontecer nada, 1 se P1 marcou, -1 se P2 marcou
		if (podeAndarCima() == false) {
			
			if (direcao == DIR_CIMADIR) {
				direcao = DIR_BAIXODIR;
				return 0;
			}

			if (direcao == DIR_CIMAESQ) {
				direcao = DIR_BAIXOESQ;
				return 0;
			}

		}
		else if (podeAndarBaixo() == false) {

			if (direcao == DIR_BAIXODIR) {
				direcao = DIR_CIMADIR;
				return 0;
			}
			if (direcao == DIR_BAIXOESQ) {
				direcao = DIR_CIMAESQ;
				return 0;
			}
		}
		
		for (int i = 0; i < nVertices; i++) {
			if (i % 3 == 0)
			{
				if (vertices[i] <= -1.0f)
				{
					vertices[i] = -1.0f;
					return -1;
				}
				else if (vertices[i] >= 1.0f)
				{

					vertices[i] = 1.0f;
					return 1;				
				}
			}
		}

		switch (direcao) {
		case 1://cima 
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 1)
					vertices[i] = vertices[i] + valorMov;
			}

			centro[1] = centro[1] + valorMov;
			break;
		case 2://baixo
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 1)
					vertices[i] = vertices[i] - valorMov;
			}

			centro[1] = centro[1] - valorMov;
			break;
		case 3://esquerda
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] - valorMov;
			}
			centro[0] = centro[0] - valorMov;
			break;
		case 4://direita
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] + valorMov;
			}
			
			centro[0] = centro[0] + valorMov;
			break;
		case 5://cima esquerda
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] - valorMov;
				if (i % 3 == 1)
					vertices[i] = vertices[i] + valorMov;
			}
			centro[0] = centro[0] - valorMov;
			centro[1] = centro[1] + valorMov;
			break;
		case 6://cima direita
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] + valorMov;
				if (i % 3 == 1)
					vertices[i] = vertices[i] + valorMov;
			}
			centro[0] = centro[0] + valorMov;
			centro[1] = centro[1] + valorMov;
			break;
		case 7://baixo esquerda 
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] - valorMov;
				if (i % 3 == 1)
					vertices[i] = vertices[i] - valorMov;
			}
			centro[0] = centro[0] - valorMov;
			centro[1] = centro[1] - valorMov;
			break;
		case 8://baixo direita

			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 0)
					vertices[i] = vertices[i] + valorMov;
				if (i % 3 == 1)
					vertices[i] = vertices[i] - valorMov;
			}
			centro[0] = centro[0] + valorMov;
			centro[1] = centro[1] - valorMov;
			break;

		}
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices, vertices, GL_STATIC_DRAW);
		return 0;
	}
};

class InimigoIA : public poligono {
	int direcao = 1;//1 cima, 2 baixo
public:
	
	InimigoIA(GLfloat* vertices_, std::size_t sizeofVertices, GLfloat larg, GLfloat comp, GLfloat centX, GLfloat centY, GLfloat centZ)
		: poligono(vertices_, sizeofVertices, larg, comp, centX, centY, centZ) {

	}
	void andarAutomatico() {
		if (direcao == 1){ //subir
			if (podeAndarCima() == false)
			{
				direcao = 2;
				goto skiparAndamento;
			}
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 1)
					vertices[i] = vertices[i] + valorMov;
			}
		}
		else if(direcao == 2){ //descer
			if (podeAndarBaixo() == false)
			{
				direcao = 1;
				goto skiparAndamento;
			}
			for (int i = 0; i < nVertices; i++) {
				if (i % 3 == 1)
					vertices[i] = vertices[i] - valorMov;
			}
		}
	skiparAndamento:
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices, vertices, GL_STATIC_DRAW);
	}
};