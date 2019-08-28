using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace CollisionTestEditor
{
	public partial class Form1 : Form
	{
		ViewTransformation viewTransformation;
		Shape shape1;
		Shape shape2;

		public Form1()
		{
			InitializeComponent();

			pictureBox1.MouseWheel += pictureBox1_MouseWheel;
			pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
			viewTransformation = new ViewTransformation(40.0, pictureBox1.Width / 2, pictureBox1.Height / 2);
		}

		private void Draw()
		{
			Drawing.Draw(Graphics.FromImage(pictureBox1.Image), viewTransformation, shape1, shape2);
			pictureBox1.Invalidate();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			openFileDialog1.ShowDialog();
		}

		private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
		{
			shape1 = new Shape(File.ReadAllText(openFileDialog1.FileName));
			Draw();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			openFileDialog2.ShowDialog();
		}

		private void openFileDialog2_FileOk(object sender, CancelEventArgs e)
		{
			shape2 = new Shape(File.ReadAllText(openFileDialog2.FileName));
			Draw();
		}

		private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
		{
			viewTransformation.zoom *= 1 + 0.1 * e.Delta / 120;
			Draw();
		}

		private void Form1_ResizeEnd(object sender, EventArgs e)
		{
			pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
			viewTransformation = new ViewTransformation(viewTransformation.zoom, pictureBox1.Width / 2, pictureBox1.Height / 2);
			Draw();
		}
	}
}
