#pragma once

#include "AbstractClientRegistry.hpp"

#include <unordered_map>
#include <vector>

namespace net
{

	class ClientRegistry : public AbstractClientRegistry
	{
	public:

		ClientRegistry();
		virtual ~ClientRegistry() override = default;
		virtual void Tick(def::time) override;
		virtual bool Touch(def::time, def::entity_id, Address&) override;

	private:

		struct session
		{ 
			session() = default;
			session(Address address, def::time timeout_at) : address{ address }, timeout_at{ timeout_at } {}
			Address address;
			def::time timeout_at;
		};

		def::time internal_clock;
		std::unordered_map<def::entity_id, session> registry;

	};

}