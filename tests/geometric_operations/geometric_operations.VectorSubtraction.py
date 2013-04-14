#python

import k3d

document = k3d.new_document()

vectorSubtraction = k3d.plugin.create("VectorSubtraction", document)

vectorSubtraction.a = k3d.vector3(1, 2, 3)
vectorSubtraction.b = k3d.vector3(3, 2, 1)

if vectorSubtraction.a_minus_b != k3d.vector3(-2, 0, 2):
  raise Exception("(1, 2, 3) - (3, 2, 1) != (-2, 0, 2)")
