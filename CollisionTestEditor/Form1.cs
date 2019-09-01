using System;
using System.ComponentModel;
using System.Diagnostics;
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
			openFileDialog3.InitialDirectory = defaultScenarioFolder;
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
			UpdateShapes();
			Draw();
		}

		private void button2_Click(object sender, EventArgs e)
		{
			openFileDialog2.ShowDialog();
		}

		private void openFileDialog2_FileOk(object sender, CancelEventArgs e)
		{
			shape2 = new Shape(File.ReadAllText(openFileDialog2.FileName), 0, new ModelPoint(0, 0));
			UpdateShapes();
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
				//Shape descriptions already contain a terminating newline.
				sw.Write(shape1);
				sw.Write(shape2);
			}
		}

		private void button4_Click(object sender, EventArgs e)
		{
			openFileDialog3.ShowDialog();
		}

		private void openFileDialog3_FileOk(object sender, CancelEventArgs e)
		{
			using (StreamReader sr = new StreamReader(openFileDialog3.FileName))
			{
				string line;
				line = sr.ReadLine();
				Debug.Assert(line == "TRUE" || line == "FALSE", "First line of " + openFileDialog3.FileName + " must be 'TRUE' or 'FALSE'.");
				checkBox1.Checked = (line == "TRUE");
				line = sr.ReadLine();
				Debug.Assert(line == "TRUE" || line == "FALSE", "Second line of " + openFileDialog3.FileName + " must be 'TRUE' or 'FALSE'.");
				checkBox2.Checked = (line == "TRUE");

				double orientation;
				ModelPoint position;

				orientation = Convert.ToDouble(sr.ReadLine());
				line = sr.ReadLine();
				position = new ModelPoint(Convert.ToDouble(line.Split()[0]), Convert.ToDouble(line.Split()[1]));
				trackBar1.Value = Convert.ToInt32(orientation / Math.PI * 180);
				trackBar2.Value = Convert.ToInt32(Math.Truncate(position.x));
				trackBar3.Value = Convert.ToInt32((position.x - Math.Truncate(position.x)) * 100);
				trackBar4.Value = Convert.ToInt32(Math.Truncate(position.y));
				trackBar5.Value = Convert.ToInt32((position.y - Math.Truncate(position.y)) * 100);

				line = sr.ReadLine();
				for (int i = 0; i < Convert.ToInt32(line.Split()[0]) * 2 + Convert.ToInt32(line.Split()[1]); i++)
				{
					line += "\n" + sr.ReadLine();
				}
				line += "\n";
				shape1 = new Shape(line, 0, new ModelPoint(0, 0));

				orientation = Convert.ToDouble(sr.ReadLine());
				line = sr.ReadLine();
				position = new ModelPoint(Convert.ToDouble(line.Split()[0]), Convert.ToDouble(line.Split()[1]));
				trackBar6.Value = Convert.ToInt32(orientation / Math.PI * 180);
				trackBar7.Value = Convert.ToInt32(Math.Truncate(position.x));
				trackBar8.Value = Convert.ToInt32((position.x - Math.Truncate(position.x)) * 100);
				trackBar9.Value = Convert.ToInt32(Math.Truncate(position.y));
				trackBar10.Value = Convert.ToInt32((position.y - Math.Truncate(position.y)) * 100);

				line = sr.ReadLine();
				for (int i = 0; i < Convert.ToInt32(line.Split()[0]) * 2 + Convert.ToInt32(line.Split()[1]); i++)
				{
					line += "\n" + sr.ReadLine();
				}
				line += "\n";
				shape2 = new Shape(line, 0, new ModelPoint(0, 0));
			}

			UpdateShapes();
			Draw();
		}
	}
}
