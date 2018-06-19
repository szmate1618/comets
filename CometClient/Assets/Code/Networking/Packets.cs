using System;

namespace net
{

    //In C# the effect of 'using' aliases is limited to file scope.
    using uint8_t = Byte;
    using uint16_t = UInt16;
    using uint32_t = UInt32;
    using entity_id = UInt32;

    using ClientInputPacket = Packet<Header, ClientInputPayload>;
    using ServerStatePacket = Packet<ServerHeader, ServerStatePayload>;

    enum packet_type { client_input, server_state };

    class Header
    {
        public uint8_t protocol_id;
        public uint32_t sequence_number;
        public uint8_t packet_type;
    };

    class ServerHeader
    {
		public Header common_header;
        public uint32_t ack;
        public uint32_t ack_bitfield;
    };

    class ClientInputPayload
    {
		public entity_id entity_id;
        public uint8_t duration;
        public uint16_t count; //count=0 will be used as client heartbeat.
        public uint8_t[] inputs;
    };

    class ServerObject
    {
		public entity_id entity_id; //TODO: Originally this was called 'type'. Find out why.
        public double phi;
        public double x;
        public double y;
    };

    class ServerStatePayload
    {
		public uint16_t count;
        public ServerObject[] objects;
    };
    
    class Packet<H, P>
    {
		public H header;
        public P payload;
    };

}
