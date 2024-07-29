#pragma once
#include <list>
#include "P6Particle.h"
#include "ForceRegistry.h"
#include "Gravity.h"

namespace P6 {
	class PhysicsWorld {
	public:
		ForceRegistry forceRegistry;
		std::list<PhysicsParticle*> Particles;
		void AddParticle(PhysicsParticle* toAdd);
		void Update(float time);

	private:
		GravityForce Gravity = GravityForce(MyVector(0, -9.8, 0));
		void UpdateParticleList();
		
	};
}