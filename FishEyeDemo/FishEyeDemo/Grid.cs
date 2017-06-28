using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FishEyeDemo
{
    class Grid : Shape
    {
        double precision;
        List<Line> lines;

        public Grid(ModelPoint lower_left, ModelPoint upper_right, double gap, double precision)
        {
            this.precision = precision;
            lines = new List<Line>();
            for (double d = lower_left.x; d <= upper_right.x; d += gap)
            {
                lines.Add(new Line(new ModelPoint(d, lower_left.y), new ModelPoint(d, upper_right.y), precision));
            }
            for (double d = lower_left.y; d <= upper_right.y; d += gap)
            {
                lines.Add(new Line(new ModelPoint(lower_left.x, d), new ModelPoint(upper_right.y, d), precision));
            }
        }

        public List<ModelPoint> GetPoints()
        {
            List<ModelPoint> ret = new List<ModelPoint>();
            foreach (Line line in lines)
            {
                //ret.AddAll(line.GetPoints());
                foreach (ModelPoint mp in line.GetPoints())
                {
                    ret.Add(mp);  
                }   
            }
            return ret;
        }
    }
}
