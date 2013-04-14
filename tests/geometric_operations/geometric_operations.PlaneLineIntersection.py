#python

import k3d

document = k3d.new_document()

planeLineIntersection = k3d.plugin.create("PlaneLineIntersection", document)

normal = k3d.vector3(0, 0, 1)
point = k3d.point3(0, 1, 0)

plane = k3d.plane(normal, point)
line = k3d.line3(normal, point)

planeLineIntersection.plane = plane
planeLineIntersection.line = line

if planeLineIntersection.intersection_point != point:
  raise Exception("Incorrect intersection point: " + str(planeLineIntersection.intersection_point))
