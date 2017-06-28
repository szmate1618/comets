using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FishEyeDemo
{
    class Circle : Shape
    {
        ModelPoint origo;
        double radius;
        double precision;

        public Circle(ModelPoint origo, double radius, double precision)
        {
            this.origo = origo;
            this.radius = radius;
            this.precision = precision;
        }

        public List<ModelPoint> GetPoints()
        {
            List<ModelPoint> ret = new List<ModelPoint>();
            int steps = Convert.ToInt32(Math.PI * 2 / precision);
            ModelPoint cursor = new ModelPoint(radius, 0);
            for (int i = 0; i < steps; i++)
            {
                ret.Add(new ModelPoint(origo.x + cursor.x, origo.y + cursor.y));
                double new_x = cursor.x * Math.Cos(precision) - cursor.y * Math.Sin(precision);
                double new_y = cursor.x * Math.Sin(precision) + cursor.y * Math.Cos(precision);
                cursor.x = new_x;
                cursor.y = new_y;
            }
            return ret;
        }
    }
}
