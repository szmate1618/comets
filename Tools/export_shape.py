import bpy


def export_shape(context, filepath):
    print("running export_shape...")
    f = open(filepath, 'w', encoding='utf-8')
    f.write("Hello World")
    f.close()

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
