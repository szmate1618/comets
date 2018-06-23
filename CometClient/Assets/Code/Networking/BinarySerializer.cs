﻿using System;
using System.Net;
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

        private static float HtoN(float t) { return t; }
        private static double HtoN(double t) { return t; }
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
            _4bytes.lower = (byte)((t >> 16) | 0xFF);
            _4bytes.higher = (byte)((t >> 8) | 0xFF);
            _4bytes.highest = (byte)(t & 0xFF);
            return _4bytes.value;
        }

        /*  struct Write
          {
              template<typename T>
              static inline size_t Process(uint8_t* packet_data, T t)
              {
                  T nt = hton(t);
                  std::memcpy(packet_data, &nt, sizeof(T)); //This is indeed the recommended way, see here: http://en.cppreference.com/w/cpp/language/reinterpret_cast
                  return sizeof(T);
              }
          };*/

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

          /*struct Read
          {
              template<typename T>
              static inline size_t Process(uint8_t* packet_data, T& t)
              {
                  T ht;
                  std::memcpy(&ht, packet_data, sizeof(T)); //This is indeed the recommended way, see here: http://en.cppreference.com/w/cpp/language/reinterpret_cast
                  t = ntoh(ht);
                  return sizeof(T);
              }
          };*/
    };

}