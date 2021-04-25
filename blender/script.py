import bpy

file = open("data_out.txt", 'w')
for every_object in bpy.context.scene.objects:
    every_object.select_set(True)    
    loc = every_object.location
    rot = every_object.rotation_euler
    sca = every_object.scale
    if every_object.data.name.startswith("Cube"):
        name="rectangle"
        file.write(str(name) +' '+str(loc.x)+' '+str(loc.y)+' '+str(loc.z)+' '+ str(rot.x) + ' '+str(rot.y)+ ' '+str(rot.z)+' '+ str(sca.x) + ' '+str(sca.y)+ ' '+str(sca.z)+ '\n' ) 

    if every_object.data.name.startswith("Sphere"):
        name="sphere"
        file.write(str(name) +' '+str(loc.x)+' '+str(loc.y)+' '+str(loc.z)+' '+ str(rot.x) + ' '+str(rot.y)+ ' '+str(rot.z)+' '+ str(sca.x) + ' '+str(sca.y)+ ' '+str(sca.z)+ '\n' ) 

file.close()


