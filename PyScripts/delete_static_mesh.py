import unreal

# instances of unreal classes
editor_level_lib = unreal.EditorLevelLibrary()
editor_filter_lib = unreal.EditorFilterLibrary()

# get all level actors and filter by StaticMeshActor
level_actors = editor_level_lib.get_all_level_actors()
static_mesh_actors = editor_filter_lib.by_class(level_actors, unreal.StaticMeshActor)
deleted = 0

for actor in static_mesh_actors:
    actor_name = actor.get_fname()

    # get the static mesh through the static mesh component
    actor_mesh_comp = actor.static_mesh_component
    actor_mesh = actor_mesh_comp.static_mesh
    is_valid_actor = actor_mesh != None

    # if mesh not valid, destroy
    if not is_valid_actor:
        actor.destroy_actor()
        deleted += 1
        unreal.log("The Mesh Component of Actor {} is invalid and was deleted".format(actor_name))

unreal.log("Deleted {} Actors with invalid Mesh Component".format(deleted))