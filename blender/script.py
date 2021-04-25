import bpy

file = open("data_out.txt", 'w')
for every_object in bpy.context.scene.objects:
    if every_object.name.startswith("cl"):
        every_object.select_set(True)    
        name=every_object.name
        objectType = every_object.data.name
        loc = every_object.location
        rot = every_object.rotation_euler
        sca = every_object.scale
        file.write(str(objectType) +' '+str(loc.x)+' '+str(loc.y)+' '+str(loc.z)+' '+ str(rot.x) + ' '+str(rot.y)+ ' '+str(rot.z)+' '+ str(sca.x) + ' '+str(sca.y)+ ' '+str(sca.z)+ '\n' ) 
file.close()