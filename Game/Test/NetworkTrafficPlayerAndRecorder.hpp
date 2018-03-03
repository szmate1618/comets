#pragma once

#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>


namespace Test
{

	class NetworkTrafficPlayerAndRecorder
	{

		struct Packet
		{
			char Case[10];

			char IPAddr[30];
			int ProtID;
			int SeqNum;
			int PacketType;
			int EntityID;
			int Period;
			int InputSize;
			int Input[100];
			int Time;

			Packet* NextPacket;
		};

	public:

		NetworkTrafficPlayerAndRecorder()
		{
			FILE *fp;
			fp = fopen("data.txt", "rt");
			if (fp == NULL)
			{
				return;
			}
			char cTemp;
			Packet* First = new Packet;
			Packet* Temp = First;
			while ((fscanf(fp, "%c", &cTemp)) != EOF)
			{
				Temp->NextPacket = new Packet;
				if (isdigit(cTemp))
				{
					strcpy(Temp->Case, "Message");
					int i = 0;
					while (!isspace(cTemp))
					{
						strcat(Temp->IPAddr, &cTemp);
						fscanf(fp, "%c", &cTemp);
						i++;
					}
					Temp->IPAddr[i] = '\0';
					fscanf(fp, "%d", &Temp->ProtID);
					fscanf(fp, "%d", &Temp->SeqNum);
					fscanf(fp, "%d", &Temp->PacketType);
					fscanf(fp, "%d", &Temp->EntityID);
					fscanf(fp, "%d", &Temp->Period);
					fscanf(fp, "%d", &Temp->InputSize);
					for (i = 0; i < Temp->InputSize; i++)
					{
						fscanf(fp, "%d", &Temp->Input[i]);
					}
					Temp->Input[++i] = -1;
				}
				else if (cTemp == 'd')
				{
					strcpy(Temp->Case, "Delay");
					fscanf(fp, "%d", &Temp->Time);
				}
				else
				{
					while (cTemp != '\n')
					{
						fscanf(fp, "%c", &cTemp);
					}

				}
				Temp = Temp->NextPacket;
			}
			std::cout << First->Time << std::endl;
			fclose(fp);
		}

		~NetworkTrafficPlayerAndRecorder() {}

	};

}
