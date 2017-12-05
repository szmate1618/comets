#pragma once

#include "ClientRegistry.hpp"


namespace net
{

	ClientRegistry::ClientRegistry()
	{
		registry.reserve(def::max_sessions);
	}

	bool ClientRegistry::Touch(def::entity_id entity_id, const Address& address)
	{
		if (registry.count(entity_id) == 1)
		{
			registry[entity_id].store(address); //Should be unnecessary most of the time.
		}
		else
		{
			std::unique_lock<std::shared_mutex> lock{ map_potential_rehash_lock };
			registry.emplace(entity_id, address);
		}
		return true;
	}

	bool ClientRegistry::Contains(def::entity_id entity_id) const
	{
		std::shared_lock<std::shared_mutex> lock{ map_potential_rehash_lock };
		return registry.count(entity_id) == 1;
	}

	Address ClientRegistry::GetAddress(def::entity_id entity_id) const
	{
		std::shared_lock<std::shared_mutex> lock{ map_potential_rehash_lock };
		return registry.at(entity_id).load();
	}

}
