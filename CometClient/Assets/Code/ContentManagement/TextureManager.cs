using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;


public class TextureManager
{
	private static Dictionary<UInt32, Texture> textures = new Dictionary<UInt32, Texture>();

	private const UInt32 placeholderTextureId = 0;

	//This path is relative to the application directory.
	private const string texturesPath = "../Textures";

	//This path is relative to Resources.
	private const string placeholderTexturePath = "EntityTextures/placeholder";

	private void LoadTextureFromFile(string path)
	{
		try
		{
			string filename = Path.GetFileName(path);
			UInt32 id = Convert.ToUInt32(filename.Split('-')[0]);
			Texture2D texture = new Texture2D(2, 2);
			texture.LoadImage(File.ReadAllBytes(path));
			textures.Add(id, texture);
		}
		catch (Exception)
		{
			Debug.Log("Loading textures, " + path + " skipped.");
		}
	}

	public TextureManager()
	{
		textures.Add(placeholderTextureId, Resources.Load<Texture>(placeholderTexturePath));

		foreach (string filename in Directory.GetFiles(texturesPath, "*.png"))
		{
			LoadTextureFromFile(filename);
		}
		foreach (string filename in Directory.GetFiles(texturesPath, "*.jpg"))
		{
			LoadTextureFromFile(filename);
		}

		if (!textures.ContainsKey(placeholderTextureId)) Debug.Log("Placeholder texture not loaded.");
	}

	public Texture GetTexture(UInt32 texture_id)
	{
		if (textures.ContainsKey(texture_id)) return textures[texture_id];
		else return textures[placeholderTextureId];
	}
}
