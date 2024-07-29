#include "ForceRegistry.h"

void P6::ForceRegistry::Add(PhysicsParticle* particle, Force* generator) {
    Registry.push_back({ particle, generator });
}

void P6::ForceRegistry::Remove(PhysicsParticle* particle, Force* generator) {
    Registry.remove_if(
        [particle, generator](const ParticleForceRegistry& reg) {
            return reg.particle == particle && reg.generator == generator;
        }
    );
}

void P6::ForceRegistry::Clear() {
    Registry.clear();
}

void P6::ForceRegistry::UpdateForces(float time) {
    for (auto& reg : Registry) {
        reg.generator->UpdateForce(reg.particle, time);
    }
}