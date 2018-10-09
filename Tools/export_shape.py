import bpy


def export_shape(context, filepath):
    print("running export_shape...")
    object = context.active_object
    bpy.ops.object.mode_set(mode='EDIT')
    bpy.ops.mesh.quads_convert_to_tris()
    bpy.ops.object.mode_set(mode='OBJECT') #quads_convert_to_tris() sometimes does not take effect without switching back to Object Mode.
    object.data.transform(object.matrix_world)
    mesh = object.data
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write("{} {}\n".format(len(mesh.vertices), len(mesh.polygons)))
        #Print vertices.
        for v in mesh.vertices:
            assert len(v.co) == 3, "Coordinate is not XYZ."
            f.write("{} {}\n".format(v.co[0], v.co[1])) #Z coordinate is implicitly 0.
        #Print UV coordinates.
        if mesh.uv_layers.active: #If there is a UV mapping specified.
            uvs = {mesh.loops[l].vertex_index: mesh.uv_layers.active.data[l].uv for p in mesh.polygons for l in p.loop_indices}
            for v in mesh.vertices:
                f.write("{} {}\n".format(uvs[v.index][0], uvs[v.index][1]))
        else: #If there is no UV mapping specified.
            x_coordinates = [v.co[0] for v in mesh.vertices]
            y_coordinates = [v.co[1] for v in mesh.vertices]
            min_x = min(x_coordinates)
            max_x = max(x_coordinates)
            min_y = min(y_coordinates)
            max_y = max(y_coordinates)
            max_diff = max_x - min_x if max_x - min_x > max_y - min_y else max_y - min_y
            for v in mesh.vertices:
                f.write("{} {}\n".format((v.co[0] - min_x) / max_diff, (v.co[1] - min_y) / max_diff))
        #Print triangles.
        for p in mesh.polygons:
            assert len(p.vertices) == 3, "Mesh is not triangulated."
            f.write("{} {} {}\n".format(p.vertices[0], p.vertices[1], p.vertices[2]))

    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ShapeExporter(Operator, ExportHelper):
    """Export the active object as a Comet Shape file"""
    bl_idname = "export_mesh.shape"  # important since its how bpy.ops.import_mesh.shape is constructed
    bl_label = "Export Shape"

    # ExportHelper mixin class uses this
    filename_ext = ".shp"

    filter_glob = StringProperty(
            default="*.shp",
            options={'HIDDEN'},
            maxlen=255,  # Max internal buffer length, longer would be clamped.
            )

    def execute(self, context):
        return export_shape(context, self.filepath)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ShapeExporter.bl_idname, text="Shape (.shp)")


def register():
    bpy.utils.register_class(ShapeExporter)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ShapeExporter)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_mesh.shape('INVOKE_DEFAULT')
