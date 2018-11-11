using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;

public class MeshFactory
{

	public static void SetNormals(Mesh mesh)
	{
		mesh.normals = new Vector3[mesh.vertexCount];
		for (int i = 0; i < mesh.vertexCount; i++)
		{
			//TODO: Maybe make this adaptive to the camera position.
			mesh.normals[i].x = 0;
			mesh.normals[i].y = 0;
			mesh.normals[i].z = -1;
		}
	}

	//Create polygon mesh.
	public static Mesh Create(Vector3[] vertices, Vector2[] uvs, int[] triangles)
	{
		Mesh mesh =  new Mesh();
		mesh.vertices = vertices;
		mesh.uv = uvs;
		mesh.triangles = triangles;
		SetNormals(mesh);
		return mesh;
	}

	//Create polygon mesh.
	public static Mesh Create(Vector2[] vertices, Vector2[] uvs, int[] triangles)
	{
		return Create(vertices.Select(vector2 => new Vector3(vector2.x, vector2.y, 0)).ToArray(), uvs, triangles);
	}

	//Create polygon mesh.
	public static Mesh Create(int vertex_count, int triangle_count, float[] vertices, float[] uvs, ushort[] triangles)
	{
		Vector2[] vertex_vectors = new Vector2[vertex_count];
		Vector2[] uv_vectors = new Vector2[vertex_count];
		int[] triangle_ints = triangles.Take(triangle_count * 3).Select(Convert.ToInt32).ToArray();
		for (int i = 0; i < vertex_count * 2; i += 2)
		{
			vertex_vectors[i] = new Vector2(vertices[i], vertices[i + 1]);
			uv_vectors[i] = new Vector2(uvs[i], uvs[i + 1]);
		}
		return Create(vertex_vectors, uv_vectors, triangle_ints);
	}

	//Create tessellated circle.
	public static Mesh Create(double radius)
	{
		return new Mesh(); //TODO: Actually implement this.
	}

	public static Mesh CreateFromFile (string filename)
	{
		try
		{
			Mesh mesh = new Mesh();
			StreamReader file = new StreamReader(filename);
			string header = file.ReadLine();
			if (header.Contains(' ')) //If it's a polygon.
			{
				int[] NM = Array.ConvertAll(header.Split(' '), x => Int32.Parse(x));
				int N = NM[0];
				int M = NM[1];
				Vector2[] vertices = Enumerable
										.Range(1, N)
										.Select(x => file.ReadLine().Split(' '))
										.Select(x => new Vector2(Single.Parse(x[0]), Single.Parse(x[1])))
										.ToArray();
				Vector2[] uvs = Enumerable
									.Range(1, N)
									.Select(x => file.ReadLine().Split(' '))
									.Select(x => new Vector2(Single.Parse(x[0]), Single.Parse(x[1])))
									.ToArray();
				int[] triangles = Enumerable
									.Range(1, M)
									.Select(x => file.ReadLine().Split(' ').Select(y => Int32.Parse(y)))
									.Aggregate((x, y) => x.Concat(y))
									.ToArray();
				return Create(vertices, uvs, triangles);
			}
			else //If it's a circle.
			{
				double radius = Double.Parse(header);
				return Create(radius);
			}
		}
		catch (Exception e)
		{
			//TODO: C# 6 has string interpolation. Investigate if it's worth upgrading from C# 4.
			Debug.LogError("Failed to read file " + filename + ".");
			return null; 
		}
	}

}
