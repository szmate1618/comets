using System;


namespace net
{

	//In C# the effect of 'using' aliases is limited to file scope.
	using uint8_t = Byte;
	using uint16_t = UInt16;
	using uint32_t = UInt32;
	using entity_id = UInt32; //TODO: Find some way to emulate global typedefs.

	enum packet_type { client_input, server_state, shape_request, shape_description };

	interface BinarySerializable
	{
		int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index);
	}

	class Header : BinarySerializable
	{
		public uint8_t protocol_id;
		public uint32_t sequence_number;
		public uint8_t packet_type;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref protocol_id);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref sequence_number);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref packet_type);
			return current_index - start_index;
		}
	};

	class ServerHeader : BinarySerializable
	{
		public Header common_header;
		public uint32_t ack;
		public uint32_t ack_bitfield;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += common_header.Process(io_mode, packet_data, current_index);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref ack);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref ack_bitfield);
			return current_index - start_index;
		}
	};

	class ClientInputPayload : BinarySerializable
	{
		public entity_id entity_id;
		public uint8_t duration;
		public uint16_t count; //count=0 will be used as client heartbeat.
		public uint8_t[] inputs;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref entity_id);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref duration);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref count);
			for (int i = 0; i < count; i++)
			{
				current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref inputs[i]);
			}
			return current_index - start_index;
		}
	};

	class ServerObject : BinarySerializable
	{
		public entity_id entity_id; //TODO: Originally this was called 'type'. Find out why.
		public double phi;
		public double x;
		public double y;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref entity_id);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref phi);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref x);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref y);
			return current_index - start_index;
		}
	};

	class ServerStatePayload : BinarySerializable
	{
		public uint16_t count;
		public ServerObject[] objects;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref count);
			for (int i = 0; i < count; i++)
			{
				current_index += objects[i].Process(io_mode, packet_data, current_index);
			}
			return current_index - start_index;
		}
	};

	class ShapeRequest : BinarySerializable
	{
		public entity_id entity_id;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref entity_id);
			return current_index - start_index;
		}
	};

	class ShapeDescription : BinarySerializable
	{
		public uint16_t vertex_count;
		public uint16_t triangle_count;
		public float[] vertices;
		public float[] uvs;
		public uint16_t[] triangles;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref vertex_count);
			current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref triangle_count);
			for (int i = 0; i < vertex_count * 2; i++)
			{
				current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref vertices[i]);
			}
			for (int i = 0; i < vertex_count * 2; i++)
			{
				current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref uvs[i]);
			}
			for (int i = 0; i < triangle_count * 3; i++)
			{
				current_index += net.BinarySerializer.Process(io_mode, packet_data, current_index, ref triangles[i]);
			}
			return current_index - start_index;
		}
	};

	class Packet<H, P> where H : BinarySerializable where P : BinarySerializable
	{
		public H header;
		public P payload;

		public int Process(net.BinarySerializer.IOMode io_mode, Byte[] packet_data, int start_index)
		{
			int current_index = start_index;
			current_index += header.Process(io_mode, packet_data, current_index);
			current_index += payload.Process(io_mode, packet_data, current_index);
			return current_index - start_index;
		}
	};

}
