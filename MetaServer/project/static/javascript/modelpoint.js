function ModelPoint(x, y) {
	this.x = x;
	this.y = y;
	
	this.Equals = function(otherModelPoint, tolerance = 0) {
		return (Math.abs(this.x - otherModelPoint.x) <= tolerance && Math.abs(this.y - otherModelPoint.y) <= tolerance);
	};
	
	this.Dot = function(otherModelPoint) {
			return this.x * otherModelPoint.x + this.y * otherModelPoint.y;
	};
	
	this.LengthCross = function(otherModelPoint) {
			return this.x * otherModelPoint.y - this.y * otherModelPoint.x;
	};
	
	this.TurnAngle = function(otherModelPoint1, otherModelPoint2) {
			v1 = otherModelPoint1.Subtract(this);
			v2 = otherModelPoint2.Subtract(otherModelPoint1);
			length_cross = v1.LengthCross(v2);
			dot = v1.Dot(v2);
			if (dot >= 0)
			{
				return Math.asin(length_cross / v1.Length() / v2.Length());
			}
			else
			{
				sgn = Math.sign(length_cross) >= 0 ? 1 : -1;
				return sgn * Math.PI - Math.asin(length_cross / v1.Length() / v2.Length());
			}
	};

	this.InTriangle = function(modelPointA, modelPointB, modelPointC)
	{
		modelPointAB = modelPointB - modelPointA;
		modelPointBC = modelPointC - modelPointB;
		modelPointCA = modelPointA - modelPointC;
		sign1 = ab.LengthCross(this - modelPointA);
		sign2 = bc.LengthCross(this - modelPointB);
		sign3 = ca.LengthCross(this - modelPointC);
		return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) || (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0); 
	}
	
	this.Length = function()
	{
		return Math.sqrt(Math.pow(this.x, 2) + Math.pow(this.y, 2));
	};
	
	this.Negate = function()
	{
		return new ModelPoint(-this.x, -this.y);
	};

	this.Add = function(otherModelPoint)
	{
		return new ModelPoint(this.x + otherModelPoint.x, this.y + otherModelPoint.y);
	};

	this.Subtract = function(otherModelPoint)
	{
		return new ModelPoint(this.x - otherModelPoint.x, this.y - otherModelPoint.y);
	};

	
	this.toString = function() {
		return `(${this.x};${this.y})`;
	};
}

export default ModelPoint;
