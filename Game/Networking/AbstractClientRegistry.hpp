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
		virtual void Tick(def::time) = 0;
		virtual bool Touch(def::time, def::entity_id, Address&) = 0; //The return value indicates if the operation was successful.

	};

}
