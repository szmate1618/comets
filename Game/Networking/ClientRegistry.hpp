#pragma once

#include "AbstractClientRegistry.hpp"

#include <unordered_map>
#include <shared_mutex>
#define _ENABLE_ATOMIC_ALIGNMENT_FIX //I don't fully understand this, but see here: https://lists.boost.org/Archives/boost/2016/05/229464.php
#include <atomic>

namespace net
{

	//TODO: This should handle authorization too, i.e.: is the client allowed to command the specified entity?
	class ClientRegistry : public AbstractClientRegistry
	{
	public:

		ClientRegistry();
		virtual ~ClientRegistry() override = default;
		virtual bool Touch(def::entity_id, Address&) override;
		virtual bool Contains(def::entity_id) const = 0;
		virtual Address GetAddress(def::entity_id) const override;

	private:

		mutable std::shared_mutex map_potential_rehash_lock; //Rehashes should not happen if we reserve a high enough value, but that's not known in advance.
		//This map is accessed by a writer and a reader thread, insertions, removals, etc. must be mutexed.
		std::unordered_map<def::entity_id, std::atomic<Address>> registry; //This registry is never cleaned up, because KISS.

	};

}