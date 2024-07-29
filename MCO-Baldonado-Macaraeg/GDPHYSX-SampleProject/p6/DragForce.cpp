#include "DragForce.h"

void P6::DragForce::UpdateForce(PhysicsParticle* p, float time) {
	MyVector force = MyVector(0, 0, 0);
	MyVector currV = p->Velocity;

	float mag = currV.Magnitude();
	if (mag <= 0) return;
	float dragF = (k1 * mag) + (k2 * mag);

	MyVector dir = currV.normalize();
	p->AddForce(dir * -dragF);
}