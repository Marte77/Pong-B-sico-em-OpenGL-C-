#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vertexPosition_modelspace;

// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;

//    “vec3” is a vector of 3 components in GLSL. It is similar (but different) to the glm::vec3 we used to declare our triangle. The important thing is that if we use 3 components in C++, we use 3 components in GLSL too.
//    “layout(location = 0)” refers to the buffer we use to feed the vertexPosition_modelspace attribute. Each vertex can have numerous attributes : A position, one or several colours, one or several texture coordinates, lots of other things. OpenGL doesn’t know what a colour is : it just sees a vec3. So we have to tell him which buffer corresponds to which input. We do that by setting the layout to the same value as the first parameter to glVertexAttribPointer. The value “0” is not important, it could be 12 (but no more than glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &v) ), the important thing is that it’s the same number on both sides.
//    “vertexPosition_modelspace” could have any other name. It will contain the position of the vertex for each run of the vertex shader.
//    “in” means that this is some input data. Soon we’ll see the “out” keyword.

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

uniform mat4 matriztranslacao;

void main(){
	//gl_Position = MVP * vec4(vertexPosition_modelspace,1);
	gl_Position =  vec4(vertexPosition_modelspace,1) ;
	 // The color of each vertex will be interpolated
    // to produce the color of each fragment
	fragmentColor = vertexColor;
}