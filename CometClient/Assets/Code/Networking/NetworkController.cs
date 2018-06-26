using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;

public class NetworkController : MonoBehaviour
{

	private net.Packet<net.Header, net.ClientInputPayload> client_input;
	byte[] buffer = new byte[def.Network.max_packet_size];
	UdpClient udp_client;

	void Start()
	{
		client_input =
			new net.Packet<net.Header, net.ClientInputPayload>()
			{
				header = new net.Header
				{
					protocol_id = def.Network.protocol_id,
					sequence_number = 0,
					packet_type = (byte)net.packet_type.client_input
				},
				payload = new net.ClientInputPayload
				{
					entity_id = 0, //TODO: Actually implement this behaviour.
					duration = 2, //TODO: This should be calculated as the ratio of the server and the client simulation rate.
					count = 0,
					inputs = new byte[def.Network.max_packet_size]
				}
			};
		udp_client = new UdpClient(def.Network.client_port);
		udp_client.Connect(new IPAddress(def.Network.server_ip), def.Network.server_port);
	}
	
	private void AddCommand(def.Network.user_input command)
	{
		client_input.payload.inputs[client_input.payload.count] = (byte)command;
		client_input.payload.count++;
	}

	private void FixedUpdate()
	{
		client_input.payload.count = 0;
		foreach (def.Network.user_input command in Enum.GetValues(typeof(def.Network.user_input)))
		{
			//This direct use of ToString() assumes that the names defined in the enum
			//and the names of the virtual buttons exactly match.
			if (Input.GetButton(command.ToString()))
			{
				AddCommand(command);
			}
		}
		udp_client.Send(buffer, client_input.Process(net.BinarySerializer.IOMode.Write, buffer, 0));
		client_input.header.sequence_number++;
	}

}
