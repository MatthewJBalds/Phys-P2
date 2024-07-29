#pragma once
#include "Force.h"

namespace P6 {
    class GravityForce : public Force {
    private:
        MyVector gravity;

    public:
        GravityForce(const MyVector& gravity) : gravity(gravity) {}
        void UpdateForce(PhysicsParticle* particle, float time) override;
    };
}
