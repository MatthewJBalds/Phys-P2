#include "PhysicsWorld.h"

void P6::PhysicsWorld::AddParticle(PhysicsParticle* toAdd) {
	Particles.push_back(toAdd);
	forceRegistry.Add(toAdd, &Gravity);
}

void P6::PhysicsWorld::Update(float time) {
	this->UpdateParticleList();
	forceRegistry.UpdateForces(time);

	for (std::list<PhysicsParticle*>::iterator i = Particles.begin(); i != Particles.end(); i++) {
		(*i)->Update(time);
	}
}

void P6::PhysicsWorld::UpdateParticleList() {
	Particles.remove_if([](PhysicsParticle* p) {
		return p->IsDestroyed();
		}
	);
}
