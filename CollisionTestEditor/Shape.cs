using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CollisionTestEditor
{
	class Shape
	{
		public string description;
		public List<ModelPoint> vertices;
		public List<int> triangles;
		public double radius;
		public bool is_circle;

		public double orientation;
		public ModelPoint position;

		public Shape(string description)
		{
			this.description = description;

			using (StringReader sr = new StringReader(description))
			{
				string VT = sr.ReadLine();
				int vertex_count = Convert.ToInt32(VT.Split()[0]);
				int triangle_count = Convert.ToInt32(VT.Split()[1]);
				if (!VT.StartsWith("2 1"))
				{
					is_circle = false;
					vertices = Enumerable
						.Range(1, vertex_count)
						.Select(x => sr.ReadLine().Split(' '))
						.Select(x => new ModelPoint(Convert.ToDouble(x[0]), Convert.ToDouble(x[1]))).
						ToList();
					//Skip UV coordinates.
					Enumerable.Range(1, vertex_count).Select(x => sr.ReadLine()).ToList();
					triangles = Enumerable
						.Range(1, triangle_count)
						.Select(x => sr.ReadLine().Split(' ').Select(y => Convert.ToInt32(y)))
						.Aggregate((x, y) => x.Concat(y))
						.ToList();
				}
				else
				{
					is_circle = true;
					List<ModelPoint> fake_vertices = Enumerable
						.Range(1, 2)
						.Select(x => sr.ReadLine().Split(' '))
						.Select(x => new ModelPoint(Convert.ToDouble(x[0]), Convert.ToDouble(x[1]))).
						ToList();

					radius = (fake_vertices[1] - fake_vertices[0]).Length();
					int segment_count = Convert.ToInt32(Math.Ceiling(20 * radius));

					vertices = new List<ModelPoint>(segment_count + 1);
					triangles = new List<int>(segment_count * 3);
					double segment_radian = 2 * Math.PI / segment_count;

					vertices.Add(new ModelPoint(0, 0));
					vertices.Add(new ModelPoint(0, radius));
					for (int i = 2; i < vertices.Count; i++)
					{
						vertices.Add(vertices.Last().Rotated(segment_radian));
					}
				}
			}
		}
	}
}
