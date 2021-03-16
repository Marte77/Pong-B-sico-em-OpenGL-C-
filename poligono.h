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


class poligono { 
protected:
	GLfloat *vertices = NULL;
	GLuint vertexbuffer;
	int nVertices;
	GLfloat valorMov = 0.05f;
public:
	

	void alterarValorDeMovimento(GLfloat a) {
		valorMov = a;
	}

	poligono(GLfloat* vertices_, std::size_t sizeofVertices) {
		int nVertices_ = sizeofVertices / sizeof(GLfloat);
		nVertices = nVertices_;
		vertices = (GLfloat*)malloc(sizeof(GLfloat) * nVertices_);
		for (int i = 0; i < nVertices_; i++) {
			vertices[i] = vertices_[i];

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
	}
	
	bool podeAndarCima(){
		bool resultado = true;
		for (int i = 0; i < nVertices; i++) {
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
				break;
			case 2: //baixo
				podeMover = podeAndarBaixo();
				if (!podeMover)
					return;
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 1)
						vertices[i] = vertices[i] - valorMov;
				}
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

public:
	bolaPong(GLfloat* vertices_, std::size_t sizeofVertices,GLfloat valorMovimento = 0.01f)
		: poligono(vertices_, sizeofVertices) {
		valorMov = valorMovimento;
	}
	int direcao =3; //1 cima, 2 baixo, 3 esq, 4 dir, 5 cima esq, 6 cima dir, 7 baixo esq, 8 baixo dir
	void andarBola(){
		if (podeAndarCima() == false) {
			//TODO: alterar a direcao
		}
		else if (podeAndarBaixo() == false) {
			//TODO: alterar a direcao
		}
		//todo: verificar se tocou num dos retangulos
		switch (direcao) {
			case 1://cima 
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 1)
						vertices[i] = vertices[i] + valorMov;
				}
				break;
			case 2://baixo
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 1)
						vertices[i] = vertices[i] - valorMov;
				}
				break;
			case 3://esquerda
				for (int i = 0; i < nVertices; i++) {
					if (i % 3 == 0)
						vertices[i] = vertices[i] - valorMov;
				}
				break;
			case 4://direita
				break;
			case 5://cima esquerda
				break;
			case 6://cima direita
				break;
			case 7://baixo esquerda 
				break;
			case 8://baixo direita
				break;
				
		}
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * nVertices, vertices, GL_STATIC_DRAW);
	}
};

class InimigoIA : public poligono {
	int direcao = 1;//1 cima, 2 baixo
public:
	
	InimigoIA(GLfloat* vertices_, std::size_t sizeofVertices)
		: poligono(vertices_, sizeofVertices) {

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