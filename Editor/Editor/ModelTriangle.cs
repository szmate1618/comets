using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Editor
{
    class ModelTriangle
    {
        public ModelPoint a;
        public ModelPoint b;
        public ModelPoint c;

        public ModelTriangle(ModelPoint a, ModelPoint b, ModelPoint c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }
}
