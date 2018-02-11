#pragma once

#include "Entities.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

namespace entity
{

	struct EntityHandle
	{
		def::owner_id owner;
		bool is_dynamic;
		bool is_visible;
		bool is_collidable;
		union
		{
			StaticEntity* se_pointer;
			DynamicEntity* de_pointer;
		};
	};

}
