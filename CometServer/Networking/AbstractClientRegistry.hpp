#pragma once

#include "Address.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


namespace net
{

	//Every implementation must be thread-safe, since this is used by both parts of the Protocol.
	class AbstractClientRegistry
	{
	public:

		AbstractClientRegistry() = default;
		virtual ~AbstractClientRegistry() = default;
		virtual bool Touch(def::entity_id, const Address&) = 0; //The return value indicates if the operation was successful.
		virtual bool Contains(def::entity_id) const = 0;
		virtual Address GetAddress(def::entity_id) const = 0;

	};

}
