#ifndef SZM_ENGINE
#define SZM_ENGINE

#include "..\Geometry\Geometry.hpp"


namespace entity
{

	class Engine
	{
	public:

		Engine();
		virtual ~Engine();
		virtual void Rotate(double);
		virtual void Accelerate(geo::vector_2d);

	protected:
	
		//TessellatedObject& ship;
		geo::real max_speed;
	};

	class InertialEngine: public Engine
	{
	public:

		~InertialEngine();
		void Accelerate(geo::vector_2d);
	};

	class AntiInertialEngine: public Engine
	{
	public:

		~AntiInertialEngine();
		void Accelerate(geo::vector_2d);
	};

	class ParaInertialEngine: public Engine
	{
	public:

		~ParaInertialEngine();
		void Rotate(double);
		void Accelerate(geo::vector_2d);
	};

}

#endif
