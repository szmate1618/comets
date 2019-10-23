using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class TextureManager
{
	private static Dictionary<UInt32, Texture> textures = new Dictionary<UInt32, Texture>();

	private const UInt32 placeholderTextureId = UInt32.MaxValue;

	private const string texturesPath = "Assets/Resources/EntityTextures";

	//This path is relative to Resources.
	private const string placeholderTexturePath = "EntityTextures/placeholder";

	public TextureManager()
	{
		textures.Add(placeholderTextureId, Resources.Load<Texture>(placeholderTexturePath));

		foreach(string filename in Directory.GetFiles(texturesPath, "*.png"))
		{
			try
			{
				Texture texture = Resources.Load<Texture>(filename);
				UInt32 id = Convert.ToUInt32(filename.Split('-')[0]);
				textures.Add(id, texture);
			}
			catch(Exception e)
			{
				Debug.Log("Loading textures, " + filename + " skipped.");
			}
		}

		if (!textures.ContainsKey(placeholderTextureId)) Debug.Log("Placeholder texture not loaded.");
	}
	
	public Texture GetTexture(UInt32 texture_id)
	{
		if (textures.ContainsKey(texture_id)) return textures[texture_id];
		else return textures[placeholderTextureId];
	}
}
