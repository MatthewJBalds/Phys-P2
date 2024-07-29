#pragma once
#include "Force.h"

namespace P6 {
	class DragForce : public Force {
	private:
		float k1 = 0.74f;
		float k2 = 0.57f;

	public:
		DragForce() {}
		DragForce(float _k1, float _k2) : k1(_k1), k2(_k2) {}
		void UpdateForce(PhysicsParticle* p, float time) override;
	};
}
