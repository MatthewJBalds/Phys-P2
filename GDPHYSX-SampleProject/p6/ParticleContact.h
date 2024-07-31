#pragma once
#include "P6Particle.h"

namespace physics 
{
	class ParticleContact
	{
	public:
		float depth;

	public:
		//The particles in contact
		PhysicsParticle* particles[2];
		//coefficient of restitution
		float restitution;
		//Contact normal of collision
		MyVector contactNormal;
		//Resolve this contact
		void Resolve(float time);

	protected:
		void ResolveInterpenetration(float time);

	public:
		//Get the seperating speed of collision
		float GetSeparatingSpeed();
		//Calculates the nnew velocities of the objects
		void ResolveVelocity(float time);
	};
}



