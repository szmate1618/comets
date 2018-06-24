//TODO: Unify this with the C++ version, as much as possible.
using System;

namespace def
{

	static class Network
	{

		//Socket parameters
		public const int MaxPacketSize = 1000; //TODO: Check recommended max MTU.

		//Protocol parameters
		public const byte ProtocolId = 77;
		public enum user_input { turn_left, turn_right, thrust, brake, fire };

	}

}
