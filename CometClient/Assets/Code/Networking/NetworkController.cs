using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NetworkController : MonoBehaviour
{

	private net.Packet<net.Header, net.ClientInputPayload> client_input =
		new net.Packet<net.Header, net.ClientInputPayload>()
		{
			header = new net.Header
			{
				protocol_id = def.Network.ProtocolId,
				sequence_number = 0,
				packet_type = (byte)net.packet_type.client_input
			},
			payload = new net.ClientInputPayload
			{
				entity_id = 0, //TODO: Actually implement this behaviour.
				duration = 2, //TODO: This should be calculated as the ratio of the server and client simulation rate.
				count = 0,
				inputs = new byte[def.Network.MaxPacketSize]
			}
		};

	private void Start()
	{
		
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
			/*
			 * Send packet.
			 */
			client_input.header.sequence_number++;
		}
	}

}
