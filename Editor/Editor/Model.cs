using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace Editor
{
    class Model
    {
        List<ModelPoint> points;
        List<ModelPoint> selection;
        List<ModelTriangle> grid;

        public Model(int n)
        {
            points = new List<ModelPoint>();
            selection = new List<ModelPoint>();
            grid = new List<ModelTriangle>();

            double phi = 2 * Math.PI / n;
            double radius = 0.5 / Math.Sin(phi / 2);
            ModelPoint pos = new ModelPoint(0, radius);
            for (int i = 0; i < n; i++)
            {
                points.Add(new ModelPoint(pos.x, pos.y));
                double x = Math.Cos(phi) * pos.x - Math.Sin(phi) * pos.y;
                double y = Math.Sin(phi) * pos.x + Math.Cos(phi) * pos.y;
                pos.x = x;
                pos.y = y;
            }
        }

        public Model(List<ModelPoint> points, List<ModelTriangle> grid)
        {
            this.points = points;
            this.selection = new List<ModelPoint>();
            this.grid = grid;
        }

        public List<ModelPoint> getPoints()
        {
            return new List<ModelPoint>(points);
        }

        public List<ModelPoint> getSelection()
        {
            return new List<ModelPoint>(selection);
        }

        public List<ModelTriangle> getGrid()
        {
            return new List<ModelTriangle>(grid);
        }

        public void CalculateGrid()
        {
            grid = new List<ModelTriangle>();
            List<ModelPoint> ap = new List<ModelPoint>(points);

            while (ap.Count > 3)
            {
                double biggest_angle = 0;  // Is there always an angle bigger than this? What if the user turns it inside out?
                                           // Yeah, turning it inside out is problematic.
                int ba_index = -1;
                for (int i = 0; i < ap.Count; i++)
                {
                    double current_angle = ap[i].TurnAngle(ap[(i + 1) % ap.Count], ap[(i + 2) % ap.Count]);
                    if (current_angle > biggest_angle)
                    {
                        bool covers_vertex = false;
                        for (int j = 0; j < ap.Count; j++)
                        {
                            if (j == i || j == (i + 1) % ap.Count || j == (i + 2) % ap.Count) continue;
                            if (ap[j].InTriangle(ap[i], ap[(i + 1) % ap.Count], ap[(i + 2) % ap.Count])) { covers_vertex = true; break; }
                        }
                        if (!covers_vertex)
                        {
                            biggest_angle = current_angle;
                            ba_index = i;
                        }
                    }
                }
                grid.Add(new ModelTriangle(ap[ba_index], ap[(ba_index + 1) % ap.Count], ap[(ba_index + 2) % ap.Count]));
                ap.Remove(ap[(ba_index + 1) % ap.Count]);
            }

            grid.Add(new ModelTriangle(ap[0], ap[1], ap[2]));
        }

        public void selectNearest(ModelPoint p)
        {
            double mindist = Double.MaxValue;
            int minindex = -1;
            for (int i = 0; i < points.Count; i++)
            {
                double dist = Math.Sqrt(Math.Pow(points[i].x - p.x, 2) + Math.Pow(points[i].y - p.y, 2 ));
                if (dist < mindist)
                {
                    mindist = dist;
                    minindex = i;
                }
            }
            selection = new List<ModelPoint>();
            selection.Add(points[minindex]);
        }

        public void selectArea(ModelRectangle r)
        {
            selection = new List<ModelPoint>();
            foreach (ModelPoint p in points)
            {
                if (r.contains(p))
                {
                    selection.Add(p);
                }
            }
        }

        public void selectAll()
        {
            selection = new List<ModelPoint>(points);
        }

        public void translate(ModelPoint translation)
        {
            for (int i = 0; i < selection.Count; i++)
            {
                selection[i].x += translation.x;
                selection[i].y += translation.y;
            }
        }

        public void translateAll(ModelPoint translation)
        {
            for (int i = 0; i < points.Count; i++)
            {
                points[i].x += translation.x;
                points[i].y += translation.y;
            }
        }

        public ModelPoint getCenter(List<ModelPoint> point_set)
        {
            ModelPoint center = new ModelPoint(0,0);
            for (int i = 0; i < point_set.Count; i++)
            {
                center.x += point_set[i].x;
                center.y += point_set[i].y;
            }
            center.x /= point_set.Count;
            center.y /= point_set.Count;
            return center;
        }

        public void normalize()
        {
            ModelPoint center = getCenter(points);
            translateAll(-center);

            double distance = 0;
            for (int i = 0; i < points.Count; i++)
            {
                distance += Math.Sqrt(Math.Pow(points[i].x - points[(i + 1) % points.Count].x, 2)
                                    + Math.Pow(points[i].y - points[(i + 1) % points.Count].y, 2));
            }
            double ratio = points.Count / distance;
            for (int i = 0; i < points.Count; i++)
            {
                points[i].x *= ratio;
                points[i].y *= ratio;
            }
        }

        public void moveTo(ModelPoint destination)
        {
            ModelPoint center = getCenter(selection);
            translate(destination - center);
        }
    }
}
