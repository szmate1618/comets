using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FishEyeDemo
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
            if (length_cross >= 0)
            {
                return Math.Acos(length_cross / v1.Length() / v2.Length());
            }
            else
            {
                return -Math.Acos(length_cross / v1.Length() / v2.Length());
            }
        }

        public double Length()
        {
            return Math.Sqrt(Math.Pow(this.x, 2) + Math.Pow(this.y, 2));
        }

        public void Normalize()
        {
            double length = this.Length();
            x /= length;
            y /= length;
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
