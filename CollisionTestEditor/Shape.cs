using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace CollisionTestEditor
{
	class Shape
	{
		private string description;
		private List<ModelPoint> vertices;
		private List<int> triangles;
		private bool is_circle;

		public double orientation;
		public ModelPoint position;

		public Shape(string description)
		{
			this.description = description;

			StringReader sr = new StringReader(description);

			string VT = sr.ReadLine();
			int vertex_count = Convert.ToInt32(VT.Split()[0]);
			int triangle_count = Convert.ToInt32(VT.Split()[1]);
			if (!VT.StartsWith("2 1"))
			{
				is_circle = false;
				vertices = sr.ReadLine()
					.Split()
					.Select((x, i) => new { Coord = Convert.ToDouble(x), Index = i })
					.GroupBy(x => (int)(x.Index / 2))
					//"Elements in a grouping are yielded in the order that the elements that produced them appear in source."
					//https://docs.microsoft.com/en-us/dotnet/api/system.linq.enumerable.groupby
					.Select(g => new ModelPoint(g.ToList()[0].Coord, g.ToList()[1].Coord))
					.ToList();
				sr.ReadLine();
				triangles = sr.ReadLine().Split().Select(i => Convert.ToInt32(i)).ToList();
			}
			else
			{
				is_circle = true;
				List<double> fake_vertices = sr.ReadLine().Split().Select(x => Convert.ToDouble(x)).ToList();
				ModelPoint vertex0 = new ModelPoint(fake_vertices[0], fake_vertices[1]);
				ModelPoint vertex1 = new ModelPoint(fake_vertices[2], fake_vertices[3]);

				double radius = (vertex1 - vertex0).Length();
				int segment_count = Convert.ToInt32(Math.Ceiling(20 * radius));

				vertices = new List<ModelPoint>(segment_count + 1);
				triangles = new List<int>(segment_count * 3);
				double segment_radian = 2 * Math.PI / segment_count;

				vertices[0] = new ModelPoint(0, 0);
				vertices[1] = new ModelPoint(0, radius);
				for (int i = 2; i < vertices.Count; i++)
				{
					vertices[i] = vertices[i - 1].Rotated(segment_radian);
				}
			}
		}
	}
}
