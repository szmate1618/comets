﻿using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;


public class NetworkController : MonoBehaviour
{

	public GameObject mainCamera;
	public GameObject placeHolder;

	private net.Packet<net.Header, net.ClientInputPayload> client_input;
	private net.Packet<net.Header, net.ShapeRequest> shape_request;
	private net.ServerHeader server_header;
	private net.ServerStatePayload server_state;
	private net.ShapeDescription shape_description;
	private byte[] receive_buffer;
	private byte[] send_buffer;
	private IPEndPoint server;
	private UdpClient udp_client;
	private Dictionary<UInt32, GameObject> entities = new Dictionary<UInt32, GameObject>();
	private EntityFactory entityFactory;

	private void Start()
	{
		entityFactory = new EntityFactory();
		client_input =
			new net.Packet<net.Header, net.ClientInputPayload>
			{
				header = new net.Header
				{
					protocol_id = def.Network.protocol_id,
					sequence_number = 0,
					packet_type = (byte)net.packet_type.client_input
				},
				payload = new net.ClientInputPayload
				{
					entity_id = def.Network.my_entity_id, //TODO: Actually implement this behaviour.
					duration = 2, //TODO: This should be calculated as the ratio of the server and the client simulation rate.
					count = 0,
					inputs = new byte[def.Network.max_packet_size]
				}
			};
		shape_request =
			new net.Packet<net.Header, net.ShapeRequest>
			{
				header = new net.Header
				{
					protocol_id = def.Network.protocol_id,
					sequence_number = 0,
					packet_type = (byte)net.packet_type.shape_request
				},
				payload = new net.ShapeRequest { entity_id = def.Network.my_entity_id }
			};
		server_header = new net.ServerHeader() { common_header = new net.Header() };
		server_state = //TODO: Write constructors for these.
			new net.ServerStatePayload
			{
				objects = new net.ServerObject[def.Network.max_packet_size]
			};
		for (int i = 0; i < server_state.objects.Length; i++)
		{
			server_state.objects[i] = new net.ServerObject { };
		}
		shape_description =
			new net.ShapeDescription
			{
				vertices = new float[def.Network.max_packet_size],
				uvs = new float[def.Network.max_packet_size],
				triangles = new UInt16[def.Network.max_packet_size]
			};

		receive_buffer = new byte[def.Network.max_packet_size];
		send_buffer = new byte[def.Network.max_packet_size];
		server = new IPEndPoint(new IPAddress(def.Network.server_ip), def.Network.server_port);
		udp_client = new UdpClient(def.Network.client_port);
		udp_client.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 1);
		udp_client.Connect(server);
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
		udp_client.Send(send_buffer, client_input.Process(net.BinarySerializer.IOMode.Write, send_buffer, 0));
		client_input.header.sequence_number++;

		while (udp_client.Available > 0)
		{
			receive_buffer = udp_client.Receive(ref server); //TODO: Do I really need to specify this explicitly but not for Send?
			int bytes_read = server_header.Process(net.BinarySerializer.IOMode.Read, receive_buffer, 0);
			switch ((net.packet_type)server_header.common_header.packet_type)
			{
				case net.packet_type.server_state:
					server_state.Process(net.BinarySerializer.IOMode.Read, receive_buffer, bytes_read);
					for (int i = 0; i < server_state.count; i++)
					{
						net.ServerObject entity = server_state.objects[i];
						if (!entities.ContainsKey(entity.entity_id)) //TODO: Check for shape, instead of the entity itself.
						{
							shape_request.payload.entity_id = entity.entity_id;
							//TODO: Send this redundantly, multiple times.
							//It would be easy with Graphics.DrawMesh, but for some mysterious reason, that doesn't work,
							//nor does it throw any exceptions.
							udp_client.Send(send_buffer, shape_request.Process(net.BinarySerializer.IOMode.Write, send_buffer, 0));
							entities.Add(entity.entity_id, Instantiate(placeHolder));
							entities[entity.entity_id].AddComponent<entity.EntityController>();
						}
						entities[entity.entity_id].GetComponent<entity.EntityController>().UpdateState((float)entity.x, (float)entity.y, (float)entity.phi);
					}
					break;
				case net.packet_type.shape_description:
					shape_description.Process(net.BinarySerializer.IOMode.Read, receive_buffer, bytes_read);
					if (entities.ContainsKey(shape_description.entity_id)) Destroy(entities[shape_description.entity_id]);
					entities[shape_description.entity_id] = entityFactory.Create(shape_description);

					break;
			}
		}

		if (entities.ContainsKey(def.Network.my_entity_id))
		{
			mainCamera.transform.position =
				new Vector3
				(
					entities[def.Network.my_entity_id].transform.position.x,
					entities[def.Network.my_entity_id].transform.position.y,
					mainCamera.transform.position.z
				);

		}
	}

}
