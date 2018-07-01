using System;
using System.Runtime.InteropServices;


namespace net
{

	class BinarySerializer
	{

		[StructLayout(LayoutKind.Explicit)]
		private struct DissectableUInt16
		{
			[FieldOffset(0)]
			public ushort value;
			[FieldOffset(0)]
			public byte lowest;
			[FieldOffset(1)]
			public byte highest;
		};

		static DissectableUInt16 _2bytes;

		[StructLayout(LayoutKind.Explicit)]
		private struct DissectableUInt32
		{
			[FieldOffset(0)]
			public uint value;
			[FieldOffset(0)]
			public byte lowest;
			[FieldOffset(1)]
			public byte lower;
			[FieldOffset(2)]
			public byte higher;
			[FieldOffset(3)]
			public byte highest;
		};

		static DissectableUInt32 _4bytes;

		private static object HtoN(object t) { throw new InvalidOperationException(); }
		private static float HtoN(float t) { return t; } //TODO: Handle floating point endianness.
		private static double HtoN(double t) { return t; } //TODO: Handle floating point endianness.
		private static Byte HtoN(Byte t) { return t; }
		private static UInt16 HtoN(UInt16 t)
		{
			_2bytes.lowest = (byte)(t >> 8);
			_2bytes.highest = (byte)(t & 0xFF);
			return _2bytes.value;
		}
		private static UInt32 HtoN(UInt32 t)
		{
			_4bytes.lowest = (byte)(t >> 24);
			_4bytes.lower = (byte)((t >> 16) & 0xFF);
			_4bytes.higher = (byte)((t >> 8) & 0xFF);
			_4bytes.highest = (byte)(t & 0xFF);
			return _4bytes.value;
		}

		private static object NtoH(object t) { throw new InvalidOperationException(); }
		private static float NtoH(float t) { return t; }
		private static double NtoH(double t) { return t; }
		private static Byte NtoH(Byte t) { return t; }
		private static UInt16 NtoH(UInt16 t)
		{
			_2bytes.value = t;
			return (ushort)(_2bytes.lowest << 8 | _2bytes.highest);
		}
		private static UInt32 NtoH(UInt32 t)
		{
			_4bytes.value = t;
			return (uint)(_4bytes.lowest << 24 | _4bytes.lower << 16 | _4bytes.higher << 8 | _4bytes.highest);
		}

		public enum IOMode { Read, Write };

		//I can't believe C# templates can't do this.
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref object t)
		{ throw new InvalidOperationException(); }
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref float t)
		{
			int size = sizeof(float);
			if (io_mode == IOMode.Read)
			{
				t = NtoH(BitConverter.ToSingle(packet_data, index));
			}
			else if (io_mode == IOMode.Write)
			{
				Byte[] temp = BitConverter.GetBytes(HtoN(t));
				for (int i = 0; i < size; i++)
				{
					packet_data[index + i] = temp[i];
				}
			}
			return size;
		}
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref double t)
		{
			int size = sizeof(double);
			if (io_mode == IOMode.Read)
			{
				t = NtoH(BitConverter.ToDouble(packet_data, index));
			}
			else if (io_mode == IOMode.Write)
			{
				Byte[] temp = BitConverter.GetBytes(HtoN(t));
				for (int i = 0; i < size; i++)
				{
					packet_data[index + i] = temp[i];
				}
			}
			return size;
		}
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref Byte t)
		{
			int size = sizeof(Byte);
			if (io_mode == IOMode.Read)
			{
				t = packet_data[index]; //Special case.
			}
			else if (io_mode == IOMode.Write)
			{
				packet_data[index] = t; //Special case.
			}
			return size;
		}
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref UInt16 t)
		{
			int size = sizeof(UInt16);
			if (io_mode == IOMode.Read)
			{
				t = NtoH(BitConverter.ToUInt16(packet_data, index));
			}
			else if (io_mode == IOMode.Write)
			{
				Byte[] temp = BitConverter.GetBytes(HtoN(t));
				for (int i = 0; i < size; i++)
				{
					packet_data[index + i] = temp[i];
				}
			}
			return size;
		}
		public static int Process(IOMode io_mode, Byte[] packet_data, int index, ref UInt32 t)
		{
			int size = sizeof(UInt32);
			if (io_mode == IOMode.Read)
			{
				t = NtoH(BitConverter.ToUInt32(packet_data, index));
			}
			else if (io_mode == IOMode.Write)
			{
				Byte[] temp = BitConverter.GetBytes(HtoN(t));
				for (int i = 0; i < size; i++)
				{
					packet_data[index + i] = temp[i];
				}
			}
			return size;
		}

	};

}
