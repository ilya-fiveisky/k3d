#python

import k3d

document = k3d.new_document()

nodeEquality = k3d.plugin.create("NodeEquality", document)
null1 = k3d.plugin.create("Null", document)
null2 = k3d.plugin.create("Null", document)

nodeEquality.a = null1
nodeEquality.b = null2

if nodeEquality.a_equals_b != False:
  raise Exception("Two different nodes are equal.")

nodeEquality.a = null1
nodeEquality.b = null1

if nodeEquality.a_equals_b != True:
  raise Exception("Node is not equal to itself.")
