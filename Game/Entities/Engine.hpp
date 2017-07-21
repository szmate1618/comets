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
	
		//AbstractTriangulatedPoly& ship;
		geo::real max_speed;
	};

	class InertialEngine: public Engine
	{
	public:

		virtual ~InertialEngine() override;
		virtual void Accelerate(geo::vector_2d) override;
	};

	class AntiInertialEngine: public Engine
	{
	public:

		virtual ~AntiInertialEngine() override;
		virtual void Accelerate(geo::vector_2d) override;
	};

	class ParaInertialEngine: public Engine
	{
	public:

		virtual ~ParaInertialEngine() override;
		virtual void Rotate(double) override;
		virtual void Accelerate(geo::vector_2d) override;
	};

}

#endif
