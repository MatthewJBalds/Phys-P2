#pragma once
#include "P6Particle.h"
#include "../Renderer/Model3D.h"
#include "../Renderer/Shader.h"

class RenderParticle {
public:
	P6::PhysicsParticle* PhysicsParticle;
	P6::MyVector Color;
	P6::MyVector Scale;
	Model3D* RenderObject;

public:
	RenderParticle(P6::PhysicsParticle* p, Model3D* obj, P6::MyVector color, P6::MyVector scale) : PhysicsParticle(p), RenderObject(obj), Color(color), Scale(scale) {}
	void Draw();
};