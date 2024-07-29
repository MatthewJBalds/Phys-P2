#pragma once
#include "../Force/ForceGenerator.h"

/*
	bungees adds  instant force to the anchor point making it have the effect of moving like a bungee line
*/
namespace physics {
	class bungee : public ForceGenerator
	{
	public:
		MyVector anchorPoint;

		float springConstant;

		float restLength;

		float dampingConst = 0.5f;

	public:
		bungee(MyVector pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(PhysicsParticle* particle, float time) override;

	};
}


