#pragma once

#include"../Force/ForceGenerator.h"


/*
	Chains apply an instantaneous force to the object at the chain's end, directing it toward the anchor point when the chain reaches its maximum length.
*/
namespace physics {
	class Chain : public ForceGenerator
	{
	public:
		//point in the world where the other end of the spring is
		MyVector anchorPoint;

		float springConstant;

		//rest length of the spring
		float restLength;


	public:
		Chain(MyVector pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(PhysicsParticle* particle, float time) override;

	};
}

