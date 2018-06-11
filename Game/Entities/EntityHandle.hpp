#pragma once

#include "Entities.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


namespace entity
{

	enum engine_type { inertial, anti_intertial, para_inertial, pre_programmed };
	enum dynamics_class { static_, dynamic };
	enum visibility_class { visible, invisible };
	enum collidability_class { collidable, uncollidable };

	struct EntityHandle //TODO: Maybe merge this whole thing into StaticEntity?
	{
		def::owner_id owner;
		engine_type engine;
		dynamics_class dynamics;
		visibility_class visibility;
		collidability_class collidability;
		union
		{
			StaticEntity* se_pointer;
			DynamicEntity* de_pointer;
		};
	};

}
