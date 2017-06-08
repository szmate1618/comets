using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace Editor
{
    public partial class Form1 : Form
    {
        Model m;
        ViewTransformation vt;
        Point AreaSelectionStart;

        Color normalcolor = Color.Orange;
        Color selectioncolor = Color.White;

        public Form1()
        {
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            pictureBox1.MouseWheel += pictureBox1_MouseWheel;

            m = new Model(7);
            vt = new ViewTransformation(100.0, pictureBox1.Width / 2, pictureBox1.Height / 2);

            Draw();
        }

        private bool PointsAlmostEqual(Point p1, Point p2, double tolerance = 0)
        {
            double dist = Math.Sqrt(Math.Pow(p1.X - p2.X, 2) + Math.Pow(p1.Y - p2.Y, 2));
            return dist <= tolerance;
        }

        private void DrawMarker(Graphics g, Brush brush, ModelPoint mp)
        {
            Point drawPoint = vt.ModelPointToPoint(mp);
            drawPoint.X = drawPoint.X - 2;
            drawPoint.Y = drawPoint.Y - 2;
            Rectangle rect = new Rectangle(drawPoint, new Size(5, 5));
            g.FillRectangle(brush, rect);
        }

        private void DrawLine(Graphics g, Brush brush, ModelPoint mp1, ModelPoint mp2)
        {
            Pen pen = new Pen(brush);
            g.DrawLine(pen, vt.ModelPointToPoint(mp1), vt.ModelPointToPoint(mp2));
        }

        private void DrawTriangle(Graphics g, Brush brush, ModelTriangle mt)
        {
            Pen pen = new Pen(brush);
            g.DrawLine(pen, vt.ModelPointToPoint(mt.a), vt.ModelPointToPoint(mt.b));
            g.DrawLine(pen, vt.ModelPointToPoint(mt.b), vt.ModelPointToPoint(mt.c));
            g.DrawLine(pen, vt.ModelPointToPoint(mt.c), vt.ModelPointToPoint(mt.a));
        }

        LinearGradientBrush CreateGradient(ModelPoint mp1, ModelPoint mp2, Color c1, Color c2)
        {
            return new LinearGradientBrush(vt.ModelPointToPoint(mp1), vt.ModelPointToPoint(mp2), c1, c2);
        }

        private void Draw()
        {
            using (Graphics g = Graphics.FromImage(pictureBox1.Image))
            {
                List<ModelPoint> points = m.getPoints();
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
                    }
                }
            }
            pictureBox1.Invalidate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            m.selectAll();
            Draw();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            Point click_point = new Point(e.X, e.Y);
            if (!PointsAlmostEqual(click_point, AreaSelectionStart, 20)) return;

            if (e.Button.Equals(MouseButtons.Left))
            {
                m.selectNearest(vt.PointToModelPoint(click_point));
            }
            else if (e.Button.Equals(MouseButtons.Right))
            {
                m.moveTo(vt.PointToModelPoint(click_point));
            }

            Draw();
        }

        private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            vt.zoom *= 1 + 0.1 * e.Delta / 120;
            Draw();
        }

        private void pictureBox1_MouseEnter(object sender, EventArgs e)
        {
            pictureBox1.Focus();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            AreaSelectionStart = new Point(e.X, e.Y);
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            Point click_point = new Point(e.X, e.Y);
            if (PointsAlmostEqual(click_point, AreaSelectionStart, 20)) return;
            m.selectArea(new ModelRectangle(vt.PointToModelPoint(AreaSelectionStart),
                vt.PointToModelPoint(click_point)));
            Draw();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            m.CalculateGrid();
            Draw();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)  // We should use dots as decimal separators, not commas.
        {
            List<ModelPoint> points = m.getPoints();
            StreamWriter sw = new StreamWriter(saveFileDialog1.FileName);
            foreach (ModelPoint mp in points)
            {
                sw.Write("{0} {1}\n", mp.x, mp.y);
            }
            foreach (ModelTriangle mt in m.getGrid())
            {
                sw.Write("{0} {1} {2}\n", points.IndexOf(mt.a), points.IndexOf(mt.b), points.IndexOf(mt.c));
            }
            sw.Close();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            StreamReader sr = new StreamReader(openFileDialog1.FileName);
            List<ModelPoint> points = new List<ModelPoint>();
            List<ModelTriangle> grid = new List<ModelTriangle>();

            while (!sr.EndOfStream)
            {
                String[] line = sr.ReadLine().Split();
                if (line.Length == 2)
                {
                    points.Add(new ModelPoint(Double.Parse(line[0]), Double.Parse(line[1])));
                }
                else
                {
                    grid.Add(new ModelTriangle(points[Int32.Parse(line[0])], points[Int32.Parse(line[1])], points[Int32.Parse(line[2])]));
                }
            }
            m = new Model(points, grid);

            sr.Close();

            Draw();
        }
    }
}
