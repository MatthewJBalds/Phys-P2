#pragma once
#include "MyVector.h"

namespace P6 {
	class PhysicsParticle {
	public:
		float mass = 0;
		float damping = 0.9f;
		float lifespan = 1.f;
		float lifespanLeft = 0.f;

		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;

	protected:
		bool isDestroyed = false;

	public:
		PhysicsParticle();
		void AddForce(MyVector force);
		void ResetForce();
		void Destroy();
		bool IsDestroyed() { return isDestroyed; }

	protected:
		MyVector accumulatedForce = MyVector(0, 0, 0);
		void UpdatePosition(float time);
		void UpdateVelocity(float time);
		void UpdateLifespan(float time);

	public:
		void Update(float time);
	};
}