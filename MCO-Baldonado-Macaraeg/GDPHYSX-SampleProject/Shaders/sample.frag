#version 330 core

uniform vec3 color;
out vec4 FragColor; // Returns a color

//Simple shader that colors the model 
void main()
{
	//				  R   G   B  a  Ranges from 0->1
	//FragColor = vec4(1.0f,1.0f,1.0f,1.0f); //Sets the color of the fragment

	FragColor = vec4(color, 1.f);
}