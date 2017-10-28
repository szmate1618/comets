#pragma once

#include "ClientRegistry.hpp"

#include <algorithm>


namespace net
{

	ClientRegistry::ClientRegistry()
	{
		registry.reserve(def::max_sessions);
	}

	void ClientRegistry::Tick(def::time elapsed_time)
	{
		internal_clock += elapsed_time;
	};

	bool ClientRegistry::Touch(def::time elapsed_time, def::entity_id entity_id, Address& address)
	{
		if (registry.count(entity_id) == 1)
		{
			registry[entity_id].address = address; //Should be unnecessary most of the time.
			registry[entity_id].timeout_at += elapsed_time;
			return true;
		}
		else
		{
			auto& unused_slot = std::find_if
			(
				registry.begin(),
				registry.end(),
				[this](auto entry)->bool { return entry.second.timeout_at <= internal_clock; }
			);
			if (unused_slot != registry.end()) //TODO: Do some logging here.
			{
				registry[entity_id].address = address; //Should be unnecessary most of the time.
				registry[entity_id].timeout_at = internal_clock + def::session_timeout;
				return true;
			}
			else
			{
				return false; //Server limit for max simultanous sessions reached.
			}
		}
	};

}