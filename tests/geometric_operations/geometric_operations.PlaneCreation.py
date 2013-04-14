#python

import k3d

document = k3d.new_document()

planeCreation = k3d.plugin.create("PlaneCreation", document)

normal = k3d.vector3(0, 0, 1)
point = k3d.point3(0, 1, 0)

planeCreation.normal = normal
planeCreation.point = point

if planeCreation.plane != k3d.plane(normal, point):
  raise Exception("Incorrect plane: " + str(planeCreation.plane))
