function ViewTransformation(zoom, offset_x, offset_y) {
	this.zoom = zoom;
	this.offset_x = offset_x;
	this.offset_y = offset_y;
	
	this.ModelPointToCanvasPoint = function(modelPoint) {
		return {x: modelPoint.x * zoom + offset_x, y: offset_y - modelPoint.y * zoom};
	};
	
	this.CanvasPointToModelPoint = function(canvasPoint) {
		return new ModelPoint((canvasPoint.x - offset_x) / zoom, (offset_y - canvasPoint.y) / zoom);
	};
}

export {ViewTransformation};
