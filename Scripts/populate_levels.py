import unreal

def populate_level(path):
    unreal.EditorLevelLibrary.load_level(path)
    world = unreal.EditorLevelLibrary.get_editor_world()
    # Add a directional light
    light = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.DirectionalLight, unreal.Vector(0,0,500), unreal.Rotator(-45, 0, 0))
    # Add a camera
    cam = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.CameraActor, unreal.Vector(0, -500, 200), unreal.Rotator(0, 90, 0))
    # Add sky sphere (if available)
    try:
        sky = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.SkySphere, unreal.Vector(0,0,0))
    except Exception as e:
        unreal.log("SkySphere not available: " + str(e))
    unreal.EditorLevelLibrary.save_current_level()
    unreal.log("Populated and saved: " + path)

populate_level("/Game/Maps/MainMenu")
populate_level("/Game/Maps/MissionDesigner")
unreal.log("DONE")
