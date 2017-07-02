#include "Engine.hpp"


void Engine::Rotate(double radian)
{
/*	for(geo::point_2d& p: ship.vertices)
	{
		p = geo::point_2d_rotated(p, radian);
	}*/
}

void AntiInertialEngine::Accelerate(geo::vector_2d direction)
{
	//ship.velocity = geo::mul(direction, max_speed);
}

void ParaInertialEngine::Rotate(double radian)
{
	Engine::Rotate(radian);
	//ship.velocity = geo::point_2d_rotated(ship.velocity, radian);
}
