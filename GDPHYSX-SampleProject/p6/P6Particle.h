#pragma once
#include "MyVector.h"

namespace physics{

	class PhysicsParticle
	{
		protected:
			bool isDestroyed = false;

			bool affectedByForce = true;
			MyVector accumulatedForce = MyVector(0, 0, 0);
		public:
			float mass = 0;
			MyVector Velocity;
			MyVector Position;
			MyVector Acceleration;

			float damping = 0.9f;

			float lifespan;

			float radius;
			float restitution = 0.9f;

		protected:
			void UpdatePosition(float time);
			void UpdateVelocity(float time);

		public:
			PhysicsParticle();
			void update(float time);

			//Forces
			void AddForce(MyVector force);

			void ResetForce();

		public:
			void Destroy();
			bool IsDestroyed() { return isDestroyed; }

		public:

			MyVector GetPosition() { return Position; }
			
			void SetAffectedByForce(bool force) { this->affectedByForce = force; };
	};
}

