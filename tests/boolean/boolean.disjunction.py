#python

import k3d

document = k3d.new_document()

boolOr = k3d.plugin.create("Or", document)

boolOr.a = True
boolOr.b = False

if boolOr.a_or_b != True:
  raise Exception("true V false != true")

boolOr.a = False
boolOr.b = False

if boolOr.a_or_b != False:
  raise Exception("false V false != false")

boolOr.a = True
boolOr.b = True

if boolOr.a_or_b != True:
  raise Exception("true V true != true")
