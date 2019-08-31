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

			string defaultShapeFolder = Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), @"..\..\..\Shapes"));
			string defaultScenarioFolder = Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), @"..\..\..\CometServer\Test\CollisionTestScenarios"));
			openFileDialog1.InitialDirectory = defaultShapeFolder;
			openFileDialog2.InitialDirectory = defaultShapeFolder;
			saveFileDialog1.InitialDirectory = defaultScenarioFolder;
		}

		private void Draw()
		{
			Drawing.Draw(Graphics.FromImage(pictureBox1.Image), viewTransformation, shape1, shape2);
			pictureBox1.Invalidate();
		}

		private void UpdateShapes()
		{
			if (shape1 != null)
			{
				shape1.orientation = TrackBarUtils.GetRadian(trackBar1);
				shape1.position = new ModelPoint(TrackBarUtils.GetCoordinate(trackBar2, trackBar3), TrackBarUtils.GetCoordinate(trackBar4, trackBar5));
			}
			if (shape2 != null)
			{
				shape2.orientation = TrackBarUtils.GetRadian(trackBar6);
				shape2.position = new ModelPoint(TrackBarUtils.GetCoordinate(trackBar7, trackBar8), TrackBarUtils.GetCoordinate(trackBar9, trackBar10));
			}
		}

		private void button1_Click(object sender, EventArgs e)
		{
			openFileDialog1.ShowDialog();
		}

		private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
		{
			shape1 = new Shape(File.ReadAllText(openFileDialog1.FileName), 0, new ModelPoint(0, 0));
			Draw();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			openFileDialog2.ShowDialog();
		}

		private void openFileDialog2_FileOk(object sender, CancelEventArgs e)
		{
			shape2 = new Shape(File.ReadAllText(openFileDialog2.FileName), 0, new ModelPoint(0, 0));
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

		private void trackBar1_ValueChanged(object sender, EventArgs e)
		{
			UpdateShapes();
			Draw();
		}

		private void button3_Click(object sender, EventArgs e)
		{
			saveFileDialog1.ShowDialog();
		}

		private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
		{
			using (StreamWriter sw = new StreamWriter(saveFileDialog1.FileName))
			{
				sw.WriteLine(checkBox1.Checked ? "TRUE" : "FALSE");
				sw.WriteLine(checkBox2.Checked ? "TRUE" : "FALSE");
				sw.WriteLine(shape1);
				sw.WriteLine(shape2);
			}
		}
	}
}
