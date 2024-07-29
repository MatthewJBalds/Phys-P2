#include "Gravity.h"

namespace P6 {
    void GravityForce::UpdateForce(PhysicsParticle* particle, float time) {
        if (particle->mass <= 0) return;
        MyVector force = gravity * particle->mass;
        particle->AddForce(force);
    }
}