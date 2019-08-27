using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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

			pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
			viewTransformation = new ViewTransformation(100.0, pictureBox1.Width / 2, pictureBox1.Height / 2);
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
	}
}
