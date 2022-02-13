function ModelRectangle(modelPoint1, modelPoint2) {
{
	min_x;
	max_x;
	min_y;
	max_y;

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
	if (modelPoint1.y < modelPoint2.x)
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
	{
		return (min_x <= modelPoint.x && modelPoint.x <= max_x && min_y <= modelPoint.y && modelPoint.y <= max_y);
	};
}

export default ModelRectangle;
