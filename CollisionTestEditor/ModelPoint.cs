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

		public bool Equals(ModelPoint other, double tolerance = 0)
		{
			return (Math.Abs(this.x - other.x) <= tolerance && Math.Abs(this.y - other.y) <= tolerance);
		}

		public double Dot(ModelPoint other)
		{
			return this.x * other.x + this.y * other.y;
		}

		public double LengthCross(ModelPoint other)
		{
			return this.x * other.y - this.y * other.x;
		}

		public double TurnAngle(ModelPoint other1, ModelPoint other2)
		{
			ModelPoint v1 = other1 - this;
			ModelPoint v2 = other2 - other1;
			double length_cross = v1.LengthCross(v2);
			double dot = v1.Dot(v2);
			if (dot >= 0)
			{
				return Math.Asin(length_cross / v1.Length() / v2.Length());
			}
			else
			{
				double sgn = Math.Sign(length_cross) >= 0 ? 1 : -1;
				return sgn * Math.PI - Math.Asin(length_cross / v1.Length() / v2.Length());
			}
		}

		public bool InTriangle(ModelPoint a, ModelPoint b, ModelPoint c)
		{
			ModelPoint ab = b - a;
			ModelPoint bc = c - b;
			ModelPoint ca = a - c;
			double sign1 = ab.LengthCross(this - a);
			double sign2 = bc.LengthCross(this - b);
			double sign3 = ca.LengthCross(this - c);
			return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) || (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0);
		}

		public double Length()
		{
			return Math.Sqrt(Math.Pow(this.x, 2) + Math.Pow(this.y, 2));
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
