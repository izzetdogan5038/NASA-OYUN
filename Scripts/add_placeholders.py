import unreal

# Add placeholder actors to levels
for path in ["/Game/Maps/MainMenu", "/Game/Maps/MissionDesigner"]:
    unreal.EditorLevelLibrary.load_level(path)
    # Spawn a cube as spacecraft placeholder
    cube = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(0, 0, 100))
    mesh_comp = cube.get_editor_property("static_mesh_component")
    cube_mesh = unreal.EditorAssetLibrary.load_asset("/Engine/BasicShapes/Cube")
    mesh_comp.set_static_mesh(cube_mesh)
    mesh_comp.set_world_scale3d(unreal.Vector(0.5, 0.5, 0.5))
    # Spawn a sphere as planet placeholder
    sphere = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(300, 0, 0))
    sphere_comp = sphere.get_editor_property("static_mesh_component")
    sphere_mesh = unreal.EditorAssetLibrary.load_asset("/Engine/BasicShapes/Sphere")
    sphere_comp.set_static_mesh(sphere_mesh)
    sphere_comp.set_world_scale3d(unreal.Vector(2.0, 2.0, 2.0))
    unreal.EditorLevelLibrary.save_current_level()
    unreal.log("Populated with placeholders: " + path)

unreal.log("DONE placeholders")
