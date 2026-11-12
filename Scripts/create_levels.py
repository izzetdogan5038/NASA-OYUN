import unreal

def create_level(path):
    try:
        # New empty level
        success = unreal.EditorLevelLibrary.new_level(path)
        unreal.log("new_level result: " + str(success))
        # Save
        saved = unreal.EditorLevelLibrary.save_current_level()
        unreal.log("save result: " + str(saved))
    except Exception as e:
        unreal.log_error("Failed to create level " + path + ": " + str(e))

create_level("/Game/Maps/MainMenu")
create_level("/Game/Maps/MissionDesigner")

unreal.log("DONE creating levels")
