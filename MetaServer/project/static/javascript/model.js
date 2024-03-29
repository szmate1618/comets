import {ModelPoint} from './modelpoint.js';
import {ModelRectangle} from './modelrectangle.js';
import {ModelTriangle} from './modeltriangle.js';


function Model(numberOfPoints) {
	this.points = [];
	this.selection = [];
	this.grid = [];

	const phi = 2 * Math.PI / numberOfPoints;
	const radius = 0.5 / Math.sin(phi / 2);
	var pos = new ModelPoint(0, radius);
	for (let i = 0; i < numberOfPoints; i++)
	{
		this.points.push(new ModelPoint(pos.x, pos.y));
		let x = Math.cos(phi) * pos.x - Math.sin(phi) * pos.y;
		let y = Math.sin(phi) * pos.x + Math.cos(phi) * pos.y;
		pos.x = x;
		pos.y = y;
	}
	
	this.FromArrays = function(pointArray, gridArray) {
		this.points = pointArray;
		this.selection = [];
		this.grid = gridArray;
		
		return this;
	};
	
	this.CalculateGrid = function() {
		this.grid = [];
		let ap = [...this.points];

		while (ap.length > 3)
		{
			biggest_angle = 0;	// Is there always an angle bigger than this? What if the user turns it inside out?
								// Yeah, turning it inside out is problematic.
			ba_index = -1;
			for (let i = 0; i < ap.length; i++)
			{
				current_angle = ap[i].TurnAngle(ap[(i + 1) % ap.length], ap[(i + 2) % ap.length]);
				if (current_angle > biggest_angle)
				{
					covers_vertex = false;
					for (let j = 0; j < ap.length; j++)
					{
						if (j == i || j == (i + 1) % ap.length || j == (i + 2) % ap.length) continue;
						if (ap[j].InTriangle(ap[i], ap[(i + 1) % ap.length], ap[(i + 2) % ap.length])) { covers_vertex = true; break; }
					}
					if (!covers_vertex)
					{
						biggest_angle = current_angle;
						ba_index = i;
					}
				}
			}
			this.grid.push(new ModelTriangle(ap[ba_index], ap[(ba_index + 1) % ap.length], ap[(ba_index + 2) % ap.length]));
			ap.splice(ap[(ba_index + 1) % ap.length], 1);
		}

		this.grid.push(new ModelTriangle(ap[0], ap[1], ap[2]));
	};

	this.GetNearest = function(modelPoint, targetModelPoints = this.points) {
		var mindist = Number.MAX_VALUE;
		var minindex = -1;
		for (let i = 0; i < targetModelPoints.length; i++)
		{
			var dist = Math.sqrt(Math.pow(targetModelPoints[i].x - modelPoint.x, 2) + Math.pow(targetModelPoints[i].y - modelPoint.y, 2 ));
			if (dist < mindist)
			{
				mindist = dist;
				minindex = i;
			}
		}
		return targetModelPoints[minindex];
	};

	this.SelectNearest = function(modelPoint) {
		this.selection = [];
		this.selection.push(this.GetNearest(modelPoint));
	};

	this.SelectArea = function(modelRectangle) {
		this.selection = [];
		let _this = this;
		this.points.forEach(function(modelPoint, index, arr) {
			if (modelRectangle.Contains(modelPoint)) {
				_this.selection.push(modelPoint);
			}
		})
	};

	this.SelectAll = function() {
		this.selection = [...this.points];
	};


	this.Translate = function(translationModelPoint) {
		for (let i = 0; i < this.selection.length; i++)
		{
			this.selection[i].x += translationModelPoint.x;
			this.selection[i].y += translationModelPoint.y;
		}
	};

	this.TranslateAll = function(translationModelPoint) {
		for (let i = 0; i < this.points.length; i++)
		{
			this.points[i].x += translationModelPoint.x;
			this.points[i].y += translationModelPoint.y;
		}
	};

	this.GetCenter = function(modelPointArray) {
		var center = new ModelPoint(0,0);
		for (let i = 0; i < modelPointArray.length; i++)
		{
			center.x += modelPointArray[i].x;
			center.y += modelPointArray[i].y;
		}
		center.x /= modelPointArray.length;
		center.y /= modelPointArray.length;
		return center;
	};

	this.Normalize = function() {
		var center = this.GetCenter(points);
		this.TranslateAll(-center);

		distance = 0;
		for (let i = 0; i < points.length; i++)
		{
			distance += Math.sqrt(Math.pow(this.points[i].x - this.points[(i + 1) % this.points.length].x, 2)
								+ Math.pow(this.points[i].y - this.points[(i + 1) % this.points.length].y, 2));
		}
		ratio = this.points.length / distance;
		for (let i = 0; i < this.points.length; i++)
		{
			this.points[i].x *= ratio;
			this.points[i].y *= ratio;
		}
	};

	this.MoveTo = function(destinationModelPoint) {
		var center = this.GetCenter(this.selection);
		this.Translate(destinationModelPoint.Subtract(center));
	};
	
	this.SymmetrizeOnXAxis = function() {
		let mirroredPoints = JSON.parse(JSON.stringify(this.points));
		
		for (let i = 0; i < mirroredPoints.length; i++)
		{
			mirroredPoints[i].y *= -1;
		}
		
		for (let i = 0; i < this.points.length; i++)
		{
			let closestMirroredPoint = this.GetNearest(this.points[i], mirroredPoints);
			this.points[i] = new ModelPoint((this.points[i].x + closestMirroredPoint.x) / 2,(this.points[i].y + closestMirroredPoint.y) / 2)
		}
	};
	
	this.SymmetrizeOnYAxis = function() {
		let mirroredPoints = JSON.parse(JSON.stringify(this.points));
		
		for (let i = 0; i < mirroredPoints.length; i++)
		{
			mirroredPoints[i].x *= -1;
		}
		
		for (let i = 0; i < this.points.length; i++)
		{
			let closestMirroredPoint = this.GetNearest(this.points[i], mirroredPoints);
			this.points[i] = new ModelPoint((this.points[i].x + closestMirroredPoint.x) / 2,(this.points[i].y + closestMirroredPoint.y) / 2)
		}
	};
}


export {Model};
