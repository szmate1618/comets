import {Editor} from './editor.js';
import {ModelRectangle} from './modelrectangle.js';


function EditorControl(editor) {
	this.editor = editor;
	this.areaSelectionStart = {x: 0, y: 0};

	this.CanvasPointsAlmostEqual = function(canvasPoint1, canvasPoint2, tolerance = 0) {
		return (Math.abs(canvasPoint1.x - canvasPoint2.x) <= tolerance && Math.abs(canvasPoint1.y - canvasPoint2.y) <= tolerance);
	};

	this.GetMouseCoordinates = function(event) {
		const rect = this.editor.canvas.getBoundingClientRect()
		const x = event.clientX - rect.left
		const y = event.clientY - rect.top
		return {x: x, y: y};
	}
	var _this = this;
	
	this.editor.canvas.addEventListener('click', function(event) {
		var click_point = _this.GetMouseCoordinates(event);
		if (!_this.CanvasPointsAlmostEqual(click_point, _this.areaSelectionStart, 20)) return;
		_this.editor.model.SelectNearest(_this.editor.viewTransformation.CanvasPointToModelPoint(click_point));
		_this.editor.Draw();
	}, false);
	
	this.editor.canvas.addEventListener('contextmenu', function(event) {
		event.preventDefault();
		var click_point = _this.GetMouseCoordinates(event);
		if (!_this.CanvasPointsAlmostEqual(click_point, _this.areaSelectionStart, 20)) return;
		_this.editor.model.MoveTo(_this.editor.viewTransformation.CanvasPointToModelPoint(click_point));
		_this.editor.Draw();
	}, false);
	
	this.editor.canvas.addEventListener('mousedown', function(event) {
		_this.areaSelectionStart = _this.GetMouseCoordinates(event);
	}, false);
	
	this.editor.canvas.addEventListener('mouseup', function(event) {
		var click_point = _this.GetMouseCoordinates(event);
		if (_this.CanvasPointsAlmostEqual(click_point, _this.areaSelectionStart, 20)) return;
		_this.editor.model.SelectArea(new ModelRectangle(
			_this.editor.viewTransformation.CanvasPointToModelPoint(_this.areaSelectionStart),
			_this.editor.viewTransformation.CanvasPointToModelPoint(click_point)
		));
		_this.editor.Draw();
	}, false);

}


export {EditorControl};
