import bpy
import math

file = open("data_out.txt", 'w')
for every_object in bpy.context.scene.objects:
    every_object.select_set(True)    
    loc = every_object.location
    rot = every_object.rotation_euler
    sca = every_object.scale
    name = ""
    if every_object.data.name.startswith("Cube"):
        name="rectangle"  

    if every_object.data.name.startswith("Sphere"):
        name="sphere"

    if name != "":
        file.write(str(name) +' '+str(loc.x)+' '+str(loc.y * -1)+' '+str(loc.z)+' '+ str(math.degrees(rot.x)) + ' '+str(math.degrees(rot.y))+ ' '+str(math.degrees(rot.z))+' '+ str(abs(sca.x)) + ' '+str(abs(sca.y))+ ' '+str(abs(sca.z))+ '\n' ) 

file.close()