#python

import k3d

document = k3d.new_document()

pointToVector = k3d.plugin.create("PointToVector", document)

vector = k3d.vector3(1, 2, 3)
point = k3d.point3(1, 2, 3)
pointToVector.point = point


if pointToVector.vector != vector:
  raise Exception("Incorrect convertion: pointToVector.vector = " + str(pointToVector.vector) 
    + "; point = " + str(point))
