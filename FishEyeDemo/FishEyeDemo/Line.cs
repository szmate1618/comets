using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FishEyeDemo
{
    class Line: Shape
    {
        ModelPoint start;
        ModelPoint end;
        double precision;

        public Line(ModelPoint start, ModelPoint end, double precision)
        {
            this.start = start;
            this.end = end;
            this.precision = precision;
        }

        public List<ModelPoint> GetPoints()
        {
            List<ModelPoint> ret = new List<ModelPoint>();
            ModelPoint direction = (end - start);
            int steps = Convert.ToInt32(direction.Length() / precision + 1);
            direction.Normalize();
            ModelPoint cursor = new ModelPoint(start.x, start.y);
            for (int i = 0; i < steps; i++)
            {
                ret.Add(new ModelPoint(cursor.x, cursor.y));
                cursor.x += direction.x;
                cursor.y += direction.y;
            }
            return ret;
        }
    }
}
