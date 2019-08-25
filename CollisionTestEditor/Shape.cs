using System.Collections.Generic;

namespace CollisionTestEditor
{
	class Shape
	{
		string description;
		double orientation;
		ModelPoint position;
		List<ModelPoint> vertices;
		List<int> triangles;
		bool is_circle;

		public Shape(string description)
		{
			this.description = description;
		}
	}
}
