//TODO: Unify this with the C++ version, as much as possible.
using System;

namespace def
{

	static class Network
	{

		//Socket parameters
		public const ushort client_port = 7700;
		public const int max_packet_size = 1000; //TODO: Check recommended max MTU.

		//Protocol parameters
		public const byte protocol_id = 77;
		public enum user_input { turn_left, turn_right, thrust, brake, fire };

		//Server address
		public static readonly byte[] server_ip = { 127, 0, 0, 1 }; //Fine for testing, but this must be configurable.
		public const ushort server_port = 7700; //TODO: This should be specified in a config file. Maybe the others, too.

	}

}
