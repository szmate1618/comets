using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace FishEyeDemo
{
    abstract class ViewTransformation
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

        public abstract Point ModelPointToPoint(ModelPoint mp);

        /*public ModelPoint PointToModelPoint(Point p)
        {
            return new ModelPoint((p.X - offset_x) / zoom, (offset_y - p.Y) / zoom);
        }*/

    }
}
