#python

import k3d

document = k3d.new_document()

vectorToPoint = k3d.plugin.create("VectorToPoint", document)

vector = k3d.vector3(1, 2, 3)
vectorToPoint.vector = vector
point = k3d.point3(1, 2, 3)

if vectorToPoint.point != point:
  raise Exception("Incorrect convertion: vector = " + str(vector) + "; vectorToPoint.point = " 
    + str(vectorToPoint.point))
