using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;

namespace FishEyeDemo
{
    class ViewTransformationLog : ViewTransformation
    {
        public ViewTransformationLog(double zoom, double offset_x, double offset_y) : base(zoom, offset_x, offset_y){}

        override public Point ModelPointToPoint(ModelPoint mp)
        {
            ModelPoint euclidean = new ModelPoint(mp.x - offset_x, -offset_y + mp.y);
            double distance = euclidean.Length();
            if (distance <= 128.7463)
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x),
                                 Convert.ToInt32(300 - zoom * euclidean.y));
            }
            else
            {
                return new Point(Convert.ToInt32(300 + zoom * euclidean.x / distance * Math.Log(distance + 1, 1.5) / 12 * 129.7463),
                                 Convert.ToInt32(300 - zoom * euclidean.y / distance * Math.Log(distance + 1, 1.5) / 12 * 129.7463));
            }
        }

    }
}
