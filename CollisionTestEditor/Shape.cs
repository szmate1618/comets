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
					.Select((c, i) => new { Coord = Convert.ToDouble(c), Index = i })
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
			}
		}
	}
}
