#python

import k3d

document = k3d.new_document()

boolNot = k3d.plugin.create("Not", document)

boolNot.a = True

if boolNot.not_a != False:
  raise Exception("~true != false")

boolNot.a = False

if boolNot.not_a != True:
  raise Exception("~false != true")
