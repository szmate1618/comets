/*
Based on
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
