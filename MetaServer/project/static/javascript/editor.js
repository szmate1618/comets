var imageLoader = document.getElementById('texture');
	imageLoader.addEventListener('change', handleImage, false);
var canvas = document.getElementById('editor_canvas');
var ctx = canvas.getContext('2d');


function handleImage(e){
	var reader = new FileReader();
	reader.onload = function(event){
		var img = new Image();
		img.onload = function(){
			//canvas.width = img.width;
			//canvas.height = img.height;
			ctx.drawImage(img, 0, 0, canvas.width, canvas.height)
		}
		img.src = event.target.result;
	}
	reader.readAsDataURL(e.target.files[0]);
}
