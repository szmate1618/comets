using System;
using System.Drawing;

namespace CollisionTestEditor
{

	class ViewTransformation
	{

		public double zoom;
		public double offset_x;
		public double offset_y;

		public ViewTransformation(double zoom, double offset_x, double offset_y)
		{
			this.zoom = zoom;
			this.offset_x = offset_x;
			this.offset_y = offset_y;
		}

		public Point ModelPointToPoint(ModelPoint mp)
		{
			return new Point(Convert.ToInt32(mp.x * zoom + offset_x), Convert.ToInt32(offset_y - mp.y * zoom));
		}

		public ModelPoint PointToModelPoint(Point p)
		{
			return new ModelPoint((p.X - offset_x) / zoom, (offset_y - p.Y) / zoom);
		}

	}

}
