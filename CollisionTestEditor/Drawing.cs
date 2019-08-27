using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CollisionTestEditor
{
	static class Drawing
	{
		private static Color color1 = Color.Red;
		private static Color color2 = Color.Blue;
		private static Color color1transcluent = Color.FromArgb(128, color1);
		private static Color color2transcluent = Color.FromArgb(128, color2);

		private static void DrawShape(Graphics g, ViewTransformation vt, Shape shape, Color color)
		{
			if (shape == null) return;
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
					DrawMarker(g, vt.ModelPointToPoint(modelPoint), 5, color);
				}
			}
			else
			{
				ModelPoint modelCenter = new ModelPoint(0, 0);
				Point upperLeftCorner = vt.ModelPointToPoint(new ModelPoint(modelCenter.x - shape.radius, modelCenter.y - shape.radius));
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
