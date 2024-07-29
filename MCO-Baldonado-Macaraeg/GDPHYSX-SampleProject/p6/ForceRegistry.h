#pragma once
#include "P6Particle.h"
#include "Force.h"
#include "list"

namespace P6 {
    struct ParticleForceRegistry {
        PhysicsParticle* particle;
        Force* generator;
    };

    class ForceRegistry {
    private:
        std::list<ParticleForceRegistry> Registry;
    public:
        void Add(PhysicsParticle* particle, Force* generator);
        void Remove(PhysicsParticle* particle, Force* generator);
        void Clear();
        void UpdateForces(float time);
    };
}

