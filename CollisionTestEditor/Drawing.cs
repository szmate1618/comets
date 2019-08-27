﻿using System;
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
			foreach (ModelPoint modelPoint in shape.vertices)
			{
				DrawMarker(g, vt.ModelPointToPoint(modelPoint), 5, color);
			}
		}

		public static void Draw(Graphics g, ViewTransformation vt, Shape shape1, Shape shape2)
		{
			DrawShape(g, vt, shape1, Color.FromArgb(128, color1));
			DrawShape(g, vt, shape2, Color.FromArgb(128, color2));
			DrawMarkers(g, vt, shape1, color1);
			DrawMarkers(g, vt, shape2, color2);
				/*List<ModelPoint> points = m.getPoints();
				List<ModelPoint> selection = m.getSelection();
				List<ModelTriangle> grid = m.getGrid();
				g.Clear(Color.Black);
				SolidBrush normalbrush = new SolidBrush(normalcolor);
				SolidBrush selectionbrush = new SolidBrush(selectioncolor);
				Brush linebrush;
				foreach (ModelTriangle mt in grid)
				{
					DrawTriangle(g, normalbrush, mt);
				}
				for (int i = 0; i < points.Count; i++)
				{
					ModelPoint nextpoint = points[(i + 1) % points.Count];
					DrawLine(g, normalbrush, points[i], nextpoint);

					if (selection.Contains(points[i]))
					{
						if (selection.Contains(nextpoint))
						{
							linebrush = selectionbrush;
						}
						else
						{
							linebrush = CreateGradient(points[i], nextpoint, selectioncolor, normalcolor);
						}
						DrawLine(g, linebrush, points[i], nextpoint);
						DrawMarker(g, selectionbrush, points[i]);
					}
					else
					{
						if (selection.Contains(nextpoint))
						{
							linebrush = CreateGradient(points[i], nextpoint, normalcolor, selectioncolor);
						}
						else
						{
							linebrush = normalbrush;
						}
						DrawLine(g, linebrush, points[i], nextpoint);
						DrawMarker(g, normalbrush, points[i]);
					}*/
		}
	}
}
