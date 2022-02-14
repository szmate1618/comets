import {Model} from './model.js';
import {ViewTransformation} from './viewtransformation.js';


/*
Image loading is based on
https://stackoverflow.com/questions/10906734/how-to-upload-image-into-html5-canvas
*/

var imageLoader = document.getElementById('texture');
	imageLoader.addEventListener('change', handleImage, false);
var canvas = document.getElementById('editor_canvas');
var ctx = canvas.getContext('2d');


function handleImage(e){
	var reader = new FileReader();
	reader.onload = function(event){
		var img = new Image();
		img.onload = function(){
			ctx.drawImage(img, 0, 0, canvas.width, canvas.height)
		}
		img.src = event.target.result;
	}
	reader.readAsDataURL(e.target.files[0]);
}

function Editor(normalColor = '#00AA00', selectionColor = 'DDDDDD') {
	this.normalColor = normalColor;
	this.selectionColor = selectionColor;
	this.model = new Model(10);
	this.viewTransformation = new ViewTransformation(100.0, canvas.width / 2, canvas.height / 2);

	this.Draw = function() {
		var points = this.model.points;
		var selection = this.model.selection;
		var grid = this.model.grid;

		grid.forEach(function(modelTriangle, index, arr) {
			this.DrawTriangle(ctx, this.normalColor, modelTriangle);
		})

		var lineColor;

		for (let i = 0; i < points.length; i++)
		{
			let nextModelPoint = points[(i + 1) % points.length];
			this.DrawLine(ctx, this.normalColor, points[i], nextModelPoint);

			if (selection.includes(points[i]))
			{
				if (selection.includes(nextModelPoint))
				{
					lineColor = this.selectionColor;
				}
				else
				{
					//lineColor = CreateGradient(points[i], nextModelPoint, selectioncolor, normalcolor);
				}
				this.DrawLine(ctx, lineColor, points[i], nextModelPoint);
				this.DrawMarker(ctx, this.selectionColor, points[i]);
			}
			else
			{
				if (selection.includes(nextModelPoint))
				{
					//lineColor = CreateGradient(points[i], nextModelPoint, normalcolor, selectioncolor);
				}
				else
				{
					lineColor = this.normalColor;
				}
				this.DrawLine(ctx, lineColor, points[i], nextModelPoint);
				this.DrawMarker(ctx, this.normalColor, points[i]);
			}
		}
		//pictureBox1.Invalidate();
	};

	this.DrawMarker = function(ctx, fillStyle, modelPoint) {
		let drawPoint = this.viewTransformation.ModelPointToCanvasPoint(modelPoint);
		ctx.fillStyle = fillStyle;
		ctx.fillRect(drawPoint.x - 2, drawPoint.y - 2, 5, 5);
	};

	this.DrawLine = function(ctx, strokeStyle, modelPoint1, modelPoint2) {
		let drawPoint1 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint1);
		let drawPoint2 = this.viewTransformation.ModelPointToCanvasPoint(modelPoint2);
		ctx.strokeStyle = strokeStyle;
		ctx.moveTo(drawPoint1.x, drawPoint1.y);
		ctx.lineTo(drawPoint2.x, drawPoint2.y);
		ctx.stroke();
	};

	this.DrawTriangle = function(ctx, strokeStyle, modelTriangle) {
		let drawPointA = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.a);
		let drawPointB = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.b);
		let drawPointC = this.viewTransformation.ModelPointToCanvasPoint(modelTriangle.c);
		this.DrawLine(ctx, strokeStyle, drawPointA, drawPointB);
		this.DrawLine(ctx, strokeStyle, drawPointB, drawPointC);
		this.DrawLine(ctx, strokeStyle, drawPointC, drawPointA);
	};
}

var editor = new Editor();
editor.Draw();
