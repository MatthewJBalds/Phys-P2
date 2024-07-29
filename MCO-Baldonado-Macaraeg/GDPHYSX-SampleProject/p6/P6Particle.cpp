#include "P6Particle.h"

using namespace P6;

P6::PhysicsParticle::PhysicsParticle() {
	this->Acceleration = MyVector();
	this->Velocity = MyVector();
	this->Position = MyVector();
	this->mass = 0;
	this->lifespan = 1.f;
	this->lifespanLeft = 0.f;
}

void P6::PhysicsParticle::AddForce(MyVector force) {
	this->accumulatedForce += force;
}

void P6::PhysicsParticle::ResetForce() {
	this->accumulatedForce = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
}

void P6::PhysicsParticle::Destroy() {
	this->isDestroyed = true;
}

void P6::PhysicsParticle::UpdatePosition(float time) {
	this->Position = (this->Velocity * time) + ((this->Acceleration * time * time) * (1.f / 2.f)) + this->Position;
}

void P6::PhysicsParticle::UpdateVelocity(float time) {
	this->Acceleration += accumulatedForce * (1 / mass);
	this->Velocity = (this->Acceleration * time) + this->Velocity;
	this->Velocity = this->Velocity * powf(damping, time);
}

void P6::PhysicsParticle::UpdateLifespan(float time) {
	this->lifespan -= time;
	if (lifespanLeft > 0) return;
	this->Destroy();
}

void P6::PhysicsParticle::Update(float time) {
	this->UpdateLifespan(time);
	this->UpdatePosition(time);
	this->UpdateVelocity(time);
	this->ResetForce();
}