using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;


public class MeshFactory
{

	//Set normal vectors.
	//Note that these are only used for calculating lighting,
	//Unity determines triangle visibility based on winding order (clockwise ordering is visible).
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
		Mesh mesh = new Mesh
		{
			vertices = vertices,
			uv = uvs,
			triangles = triangles
		};
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
		if (vertex_count != 2) //If it's a polygon.
		{
			Vector2[] vertex_vectors = new Vector2[vertex_count];
			Vector2[] uv_vectors = new Vector2[vertex_count];
			int[] triangle_ints = triangles.Take(triangle_count * 3).Select(Convert.ToInt32).ToArray();
			for (int i = 0; i < vertex_count; i++)
			{
				vertex_vectors[i] = new Vector2(vertices[2 * i], vertices[2 * i + 1]);
				uv_vectors[i] = new Vector2(uvs[2 * i], uvs[2 * i + 1]);
			}
			return Create(vertex_vectors, uv_vectors, triangle_ints);
		}
		else //If it's a circle.
		{
			Vector2 vertex0 = new Vector2(vertices[0], vertices[1]);
			Vector2 vertex1 = new Vector2(vertices[2], vertices[3]);
			return Create((vertex1 - vertex0).magnitude);
		}
	}

	//Create tessellated circle.
	public static Mesh Create(float radius)
	{
		int segment_count = Mathf.CeilToInt(10 * radius);
		Vector3[] vertices = new Vector3[segment_count + 1];
		int[] triangles = new int[segment_count * 3];
		Quaternion segment_degree = Quaternion.Euler(0, 0, 360.0f / segment_count);

		vertices[0] = new Vector3(0, 0);
		vertices[1] = new Vector3(0, radius);
		for (int i = 2; i < vertices.Length; i++)
		{
			vertices[i] = segment_degree * vertices[i - 1];

		}

		Vector2[] uvs = vertices
							.Select(vector3 => new Vector2((vector3.x + radius) / (2 * radius), (vector3.y + radius) / (2 * radius)))
							.ToArray();

		triangles = Enumerable
						.Range(1, segment_count)
						.Select(x => new int[]{ x, 0, x + 1 > segment_count ? 1 : x + 1}.AsEnumerable())
						.Aggregate((x, y) => x.Concat(y))
						.ToArray();

		return Create(vertices, uvs, triangles);
	}

	public static Mesh CreateFromFile (string filename) //TODO: This is different from the current plaintext format.
	{
		try
		{
			Mesh mesh = new Mesh();
			StreamReader file = new StreamReader(filename);
			string header = file.ReadLine();
			if (header != "2 1") //If it's a polygon.
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
				Vector2[] vertices = Enumerable
										.Range(1, 2)
										.Select(x => file.ReadLine().Split(' '))
										.Select(x => new Vector2(Single.Parse(x[0]), Single.Parse(x[1])))
										.ToArray();
				float radius = (vertices[1] - vertices[0]).magnitude;
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
