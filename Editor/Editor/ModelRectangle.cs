using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
    class ModelRectangle
    {
        public double min_x;
        public double max_x;
        public double min_y;
        public double max_y;

        public ModelRectangle(ModelPoint p1, ModelPoint p2)
        {
            if (p1.x < p2.x)
            {
                min_x = p1.x;
                max_x = p2.x;
            }
            else
            {
                min_x = p2.x;
                max_x = p1.x;
            }
            if (p1.y < p2.y)
            {
                min_y = p1.y;
                max_y = p2.y;
            }
            else
            {
                min_y = p2.y;
                max_y = p1.y;
            }
        }

        public bool contains(ModelPoint p)
        {
            return (min_x <= p.x && p.x <= max_x && min_y <= p.y && p.y <= max_y);
        }
    }
}
