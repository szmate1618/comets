using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace FishEyeDemo
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
            ModelPoint euclidean = new ModelPoint(mp.x - offset_x, -offset_y + mp.y);
            double distance = euclidean.Length();
           /* if (distance <= 128.7463)
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x),
                                 Convert.ToInt32(300 - zoom * euclidean.y));
            }
            else
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x / distance * Math.Log(distance + 1, 1.5) / 12 * 129.7463),
                                 Convert.ToInt32(300 - zoom * euclidean.y / distance * Math.Log(distance + 1, 1.5) / 12 * 129.7463));
            }*/
            if (distance <= 100)
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x),
                                 Convert.ToInt32(300 - zoom * euclidean.y));
            }
            else
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x / distance * Math.Sqrt(distance) * 10),
                                 Convert.ToInt32(300 - zoom * euclidean.y / distance * Math.Sqrt(distance) * 10));
            }
        }

     /*   public ModelPoint PointToModelPoint(Point p)
        {
            return new ModelPoint((p.X - offset_x) / zoom, (offset_y - p.Y) / zoom);
        }*/

    }
}
