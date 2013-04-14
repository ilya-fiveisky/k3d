#python

import k3d

document = k3d.new_document()

pointSubtraction = k3d.plugin.create("PointSubtraction", document)

pointSubtraction.a = k3d.point3(1, 2, 3)
pointSubtraction.b = k3d.point3(3, 2, 1)

if pointSubtraction.a_minus_b != k3d.vector3(-2, 0, 2):
  raise Exception("(1, 2, 3) - (3, 2, 1) != (-2, 0, 2)")
