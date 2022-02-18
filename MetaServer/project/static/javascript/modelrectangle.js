function ModelRectangle(modelPoint1, modelPoint2) {
	this.min_x;
	this.max_x;
	this.min_y;
	this.max_y;

	if (modelPoint1.x < modelPoint2.x)
	{
		this.min_x = modelPoint1.x;
		this.max_x = modelPoint2.x;
	}
	else
	{
		this.min_x = modelPoint2.x;
		this.max_x = modelPoint1.x;
	}
	if (modelPoint1.y < modelPoint2.y)
	{
		this.min_y = modelPoint1.y;
		this.max_y = modelPoint2.y;
	}
	else
	{
		this.min_y = modelPoint2.y;
		this.max_y = modelPoint1.y;
	}

	this.Contains = function(modelPoint) {
		return (this.min_x <= modelPoint.x && modelPoint.x <= this.max_x && this.min_y <= modelPoint.y && modelPoint.y <= this.max_y);
	};
}


export {ModelRectangle};
