import {Model} from './model.js';
import {ViewTransformation} from './viewtransformation.js';
import {EditorControl} from './editorcontrol.js';


function Editor(canvas, normalColor = '#00AA00', selectionColor = '#DDDDDD') {
	this.canvas = canvas;
	this.ctx = canvas.getContext('2d');
	this.normalColor = normalColor;
	this.selectionColor = selectionColor;
	this.model = new Model(10);
	this.viewTransformation = new ViewTransformation(100.0, this.canvas.width / 2, this.canvas.height / 2);
	this.texture = new Image();

	this.CreateGradient = function(modelPoint1, modelPoint2, color1, color2)
	{
		let canvasPoint1 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint1);
		let canvasPoint2 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint2);
		let gradient = this.ctx.createLinearGradient(canvasPoint1.x, canvasPoint1.y, canvasPoint2.x, canvasPoint2.y);
		gradient.addColorStop(0, color1);
		gradient.addColorStop(1, color2);
		return gradient;
	}

	this.Draw = function() {
		var points = this.model.points;
		var selection = this.model.selection;
		var grid = this.model.grid;

		this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
		this.ctx.drawImage(this.texture, 0, 0, this.canvas.width, this.canvas.height)

		grid.forEach(function(modelTriangle, index, arr) {
			this.DrawTriangle(this.ctx, this.normalColor, modelTriangle);
		})

		var lineColor;

		for (let i = 0; i < points.length; i++)
		{
			let nextModelPoint = points[(i + 1) % points.length];
			//this.DrawLine(this.ctx, this.normalColor, points[i], nextModelPoint);

			if (selection.includes(points[i]))
			{
				if (selection.includes(nextModelPoint))
				{
					lineColor = this.selectionColor;
				}
				else
				{
					lineColor = this.CreateGradient(points[i], nextModelPoint, this.selectionColor, this.normalColor);
				}
				this.DrawLine(this.ctx, lineColor, points[i], nextModelPoint);
				this.DrawMarker(this.ctx, this.selectionColor, points[i]);
			}
			else
			{
				if (selection.includes(nextModelPoint))
				{
					lineColor = this.CreateGradient(points[i], nextModelPoint, this.normalColor, this.selectionColor);
				}
				else
				{
					lineColor = this.normalColor;
				}
				this.DrawLine(this.ctx, lineColor, points[i], nextModelPoint);
				this.DrawMarker(this.ctx, this.normalColor, points[i]);
			}
		}
	};

	this.DrawMarker = function(ctx, fillStyle, modelPoint) {
		let drawPoint = this.viewTransformation.ModelPointToCanvasPoint(modelPoint);
		this.ctx.fillStyle = fillStyle;
		this.ctx.fillRect(drawPoint.x - 3, drawPoint.y - 3, 7, 7);
	};

	this.DrawLine = function(ctx, strokeStyle, modelPoint1, modelPoint2) {
		let drawPoint1 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint1);
		let drawPoint2 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint2);
		this.ctx.beginPath();
		this.ctx.strokeStyle = strokeStyle;
		this.ctx.moveTo(drawPoint1.x, drawPoint1.y);
		this.ctx.lineTo(drawPoint2.x, drawPoint2.y);
		this.ctx.stroke();
	};

	this.DrawTriangle = function(ctx, strokeStyle, modelTriangle) {
		let drawPointA = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.a);
		let drawPointB = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.b);
		let drawPointC = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.c);
		this.DrawLine(this.ctx, strokeStyle, drawPointA, drawPointB);
		this.DrawLine(this.ctx, strokeStyle, drawPointB, drawPointC);
		this.DrawLine(this.ctx, strokeStyle, drawPointC, drawPointA);
	};
}

var canvas = document.getElementById('editor_canvas');
var editor = new Editor(canvas);
var editorControl = new EditorControl(editor);


export {Editor};