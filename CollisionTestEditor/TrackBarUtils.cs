using System;
using System.Windows.Forms;

namespace CollisionTestEditor
{
	static class TrackBarUtils
	{
		public static double GetRadian(TrackBar trackBar)
		{
			return trackBar.Value / 180.0 * Math.PI;
		}

		public static double GetCoordinate(TrackBar integerPart, TrackBar fractionalPart)
		{
			return integerPart.Value + fractionalPart.Value / 100.0;
		}
	}
}
