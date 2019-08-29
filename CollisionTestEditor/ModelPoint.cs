using System;

namespace CollisionTestEditor
{
	class ModelPoint
	{
		public double x;
		public double y;

		public ModelPoint(double x, double y)
		{
			this.x = x;
			this.y = y;
		}

		public double Length()
		{
			return Math.Sqrt(Math.Pow(this.x, 2) + Math.Pow(this.y, 2));
		}

		public ModelPoint Rotated(double radian)
		{
			return new ModelPoint(Math.Cos(radian) * x - Math.Sin(radian) * y, Math.Sin(radian) * x + Math.Cos(radian) * y);
		}

		public ModelPoint Transformed(double radian, ModelPoint position)
		{
			return Rotated(radian) + position;
		}

		public static ModelPoint operator -(ModelPoint p)
		{
			return new ModelPoint(-p.x, -p.y);
		}

		public static ModelPoint operator +(ModelPoint p1, ModelPoint p2)
		{
			return new ModelPoint(p1.x + p2.x, p1.y + p2.y);
		}

		public static ModelPoint operator -(ModelPoint p1, ModelPoint p2)
		{
			return new ModelPoint(p1.x - p2.x, p1.y - p2.y);
		}
	}
}
