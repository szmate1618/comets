using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FishEyeDemo
{
    public partial class Form1 : Form
    {
        ViewTransformation vt;
        List<Shape> shapes;

        public Form1()
        {
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            vt = new ViewTransformation(1, pictureBox1.Width / 2, pictureBox1.Height / 2);
            shapes = new List<Shape>();
            shapes.Add(new Circle(new ModelPoint(100, 100), 20, 0.1));
            shapes.Add(new Circle(new ModelPoint(200, 300), 32, 0.1));
            shapes.Add(new Circle(new ModelPoint(10, -240), 23, 0.1));
            shapes.Add(new Circle(new ModelPoint(-100, 100), 40, 0.1));
            shapes.Add(new Circle(new ModelPoint(-100, -100), 12, 0.1));
            shapes.Add(new Line(new ModelPoint(-100, -100), new ModelPoint(0, 0), 1));
            //shapes.Add(new Grid(new ModelPoint(-500, -500), new ModelPoint(500, 500), 50, 1));

            Draw();
        }

        private void DrawMarker(Graphics g, Brush brush, ModelPoint mp)
        {
            Point drawPoint = vt.ModelPointToPoint(mp);
            drawPoint.X = drawPoint.X - 2;
            drawPoint.Y = drawPoint.Y - 2;
            Rectangle rect = new Rectangle(drawPoint, new Size(5, 5));
            g.FillRectangle(brush, rect);
        }

        private void Draw()
        {
            SolidBrush brush = new SolidBrush(Color.AliceBlue);
            using (Graphics g = Graphics.FromImage(pictureBox1.Image))
            {
                g.Clear(Color.Black);
                foreach (Shape shape in shapes)
                {
                    foreach (ModelPoint mp in shape.GetPoints())
                    {
                        DrawMarker(g, brush, mp);
                    }
                }
            }
            pictureBox1.Invalidate();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Draw();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            vt.offset_x += 10;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            vt.offset_x -= 10;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            vt.offset_y += 10;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            vt.offset_y -= 10;
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            label1.Text = e.KeyCode.ToString();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
           
        }

    }
}
