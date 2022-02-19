import {Editor} from './editor.js';
import {EditorControl} from './editorcontrol.js';


window.app = {};
window.app.canvas = document.getElementById('editor_canvas');
window.app.editor = new Editor(window.app.canvas);
window.app.editorControl = new EditorControl(window.app.editor);
