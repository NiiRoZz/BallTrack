# BallTrack

BAULARD Guillaume (guillaume.baulard@edu.univ-fcomte.fr)
SIMONIN Rémi (remi.simonin@edu.univ-fcomte.fr)
VETTER Florian (florian.vetter@edu.univ-fcomte.fr)

OpenGL
GLUT
Blender

Liste des fichiers sources nécaissaires a la compilation : 
Src/BallTrack.cpp
Src/Drawables/Triangle.cpp
Src/Drawables/Model3D.cpp
Src/Math/CH3D.cpp
Src/Math/Dir3D.cpp
Src/Math/Pos3D.cpp
Src/Math/Rt3D.cpp
Src/Math/Sc3D.cpp
Src/Math/TG3D.cpp
Src/Math/Tr3D.cpp
Src/Math/Vector2.cpp
Src/Math/Vector3.cpp
Src/Utils/ObjLoader.cpp
Src/Physics/CollisionPrimitive.cpp
Src/Physics/RectangleCollisionPrimitive.cpp
Src/Physics/SphereCollisionPrimitive.cpp
Src/Entities/Entity.cpp
Src/Entities/PhysicEntity.cpp

Pour compiler le projet, il faut ajouter le dossier Src dans le "include directories".
Et il faut copier le dossier data a la racine du projet.

Notre circuit est minimaliste car on s'est concentré sur le reste avant de créer le circuit.

Dans le dossier blender se trouve un script, qui permet d'extraire les informations d'un objet pour notre projet.

Nous avons créé notre propre type de fichier, avec une extension .bt.
Cela nous permet de définir la texture sur notre objet, mais aussi les primitives de collisions liées à cet objet.

Nous allons décrire comment une primitive est définie dans notre fichier:
type posx posy posz rotx roty rotz scalex scaley scalez

type est forcément soit "rectangle", soit "sphere".

