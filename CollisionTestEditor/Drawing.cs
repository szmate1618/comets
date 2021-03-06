﻿using System.Drawing;

namespace CollisionTestEditor
{
	static class Drawing
	{
		private static Color color1 = Color.Red;
		private static Color color2 = Color.Blue;

		private static void DrawShape(Graphics g, ViewTransformation vt, Shape shape, Color color)
		{
			if (shape == null) return;
			Brush brush = new SolidBrush(color);
			if (!shape.is_circle)
			{
				for (int i = 0; i < shape.triangles.Count; i += 3)
				{
					Point[] points = new Point[]
					{
						vt.ModelPointToPoint(shape.vertices[shape.triangles[i]].Transformed(shape.orientation, shape.position)),
						vt.ModelPointToPoint(shape.vertices[shape.triangles[i + 1]].Transformed(shape.orientation, shape.position)),
						vt.ModelPointToPoint(shape.vertices[shape.triangles[i + 2]].Transformed(shape.orientation, shape.position))
					};
					g.FillPolygon(brush, points);
				}
			}
			else
			{
				ModelPoint modelCenter = shape.position;
				//NOTE: Y is mirrored between model and screen coordinate systems.
				Point upperLeftCorner = vt.ModelPointToPoint(new ModelPoint(modelCenter.x - shape.radius, modelCenter.y + shape.radius));
				int diameter = 2 * vt.ModelLengthToLength(shape.radius);
				g.FillEllipse(brush, upperLeftCorner.X, upperLeftCorner.Y, diameter, diameter);
			}
		}

		private static void DrawMarker(Graphics g, Point p, int halfLength, Color color)
		{
			Pen pen = new Pen(color);
			g.DrawLine(pen, new Point(p.X - halfLength, p.Y), new Point(p.X + halfLength, p.Y));
			g.DrawLine(pen, new Point(p.X, p.Y - halfLength), new Point(p.X, p.Y + halfLength));
		}

		private static void DrawMarkers(Graphics g, ViewTransformation vt, Shape shape, Color color)
		{
			if (shape == null) return;
			if (!shape.is_circle)
			{
				foreach (ModelPoint modelPoint in shape.vertices)
				{
					DrawMarker(g, vt.ModelPointToPoint(modelPoint.Transformed(shape.orientation, shape.position)), 5, color);
				}
			}
			else
			{
				ModelPoint modelCenter = shape.position;
				//NOTE: Y is mirrored between model and screen coordinate systems.
				Point upperLeftCorner = vt.ModelPointToPoint(new ModelPoint(modelCenter.x - shape.radius, modelCenter.y + shape.radius));
				int diameter = 2 * vt.ModelLengthToLength(shape.radius);

				Pen pen = new Pen(color);
				g.DrawEllipse(pen, upperLeftCorner.X, upperLeftCorner.Y, diameter, diameter);
			}
		}

		public static void Draw(Graphics g, ViewTransformation vt, Shape shape1, Shape shape2)
		{
			g.Clear(Color.Black);
			DrawShape(g, vt, shape1, Color.FromArgb(128, color1));
			DrawShape(g, vt, shape2, Color.FromArgb(128, color2));
			DrawMarkers(g, vt, shape1, color1);
			DrawMarkers(g, vt, shape2, color2);
		}
	}
}
