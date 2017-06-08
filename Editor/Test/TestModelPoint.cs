using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Editor;

namespace Test
{
    [TestClass]
    public class TestModelPoint
    {
        public double RadToDeg(double rad)
        {
            return rad / Math.PI * 180;
        }

        public double DegToRad(double deg)
        {
            return deg * Math.PI / 180;
        }

        [TestMethod]
        public void TestTurnAngle()
        {
            const double precision = 0.00001;

            ModelPoint mp1 = new ModelPoint(0, 0);
            ModelPoint mp2 = new ModelPoint(1, 0);
            ModelPoint mp3 = new ModelPoint(1, 1);
            double angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(Math.PI / 2), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify 90°.");

            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(1, -1);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(-Math.PI / 2), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify -90°.");

            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(2, 0);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(0), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify 0°.");

            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(0, 0);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(Math.PI), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify 180°.");
            
            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(2, 1);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(Math.PI / 4), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify 45°.");

            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(0, 1);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(Math.PI * 3 / 4), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify 135°.");

            mp1 = new ModelPoint(0, 0);
            mp2 = new ModelPoint(1, 0);
            mp3 = new ModelPoint(0, -1);
            angle = mp1.TurnAngle(mp2, mp3);
            Assert.AreEqual(RadToDeg(-Math.PI * 3 / 4), RadToDeg(angle), precision, "Incorrect turn angle. Failed to identify -135°.");
        }

        [TestMethod]
        public void TestTurnAngleRandom()
        {
            Random r = new Random(123123123);
            const double precision = 0.00001;

            for (int i = 0; i < 10; i++)
            {
                double degree = r.NextDouble() * 360 - 180;
                ModelPoint mp1 = new ModelPoint(-1, 0);
                ModelPoint mp2 = new ModelPoint(0, 0);
                ModelPoint mp3 = new ModelPoint(Math.Cos(DegToRad(degree)), Math.Sin(DegToRad(degree)));
                double angle = mp1.TurnAngle(mp2, mp3);
                Assert.AreEqual(degree, RadToDeg(angle), precision, String.Format("Incorrect turn angle. Failed to identify {0}°.", degree));
            }
        }

        [TestMethod]
        public void TestInTriangleSpecial()
        {
            ModelPoint a = new ModelPoint(0, 0);
            ModelPoint b = new ModelPoint(1, 0);
            ModelPoint c = new ModelPoint(0, 1);
            ModelPoint[] pi = { new ModelPoint(0, 0), new ModelPoint(1, 0), new ModelPoint(0, 1), new ModelPoint(0.5, 0.5),
                                new ModelPoint(0.4, 0.4), new ModelPoint(0.9, 0.01), new ModelPoint(0.01, 0.9) };
            foreach (ModelPoint p in pi)
            {
                Assert.IsTrue(p.InTriangle(a, b, c), String.Format("Error with point {0} in triangle {1} {2} {3}.", p, a, b, c));
            }
            foreach (ModelPoint p in pi)
            {
                Assert.IsTrue(p.InTriangle(a, c, b), String.Format("Error with point {0} in triangle {1} {2} {3}.", p, a, c, b));
            }
            ModelPoint[] po = { new ModelPoint(-0.001, 0), new ModelPoint(1.0002, 0), new ModelPoint(0, 1.1), new ModelPoint(0.51, 0.5),
                                new ModelPoint(0.9, 0.11), new ModelPoint(0.11, 0.9) };
            foreach (ModelPoint p in po)
            {
                Assert.IsFalse(p.InTriangle(a, b, c), String.Format("Error with point {0} outside of triangle {1} {2} {3}.", p, a, b, c));
            }
        }

        [TestMethod]
        public void TestInTriangleRandom()
        {
            Random r = new Random(1337);

            ModelPoint a = new ModelPoint(0, 0);
            ModelPoint b = new ModelPoint(1, 0);
            ModelPoint c = new ModelPoint(0, 1);

            for (int i = 0; i < 20; i++)
            {
                ModelPoint p = new ModelPoint(r.NextDouble(), r.NextDouble());
                bool is_inside = (p.x + p.y <= 1);
                string where = is_inside ? "in" : "outside of";
                Assert.AreEqual(is_inside, p.InTriangle(a, b, c), "Error with point {0} {1} triangle {2} {3} {4}.", p, where, a, b, c);
            }
        }

    }
}
