#python

import k3d

document = k3d.new_document()

boolAnd = k3d.plugin.create("And", document)

boolAnd.a = True
boolAnd.b = False

if boolAnd.a_and_b != False:
  raise Exception("true & false != false")

boolAnd.a = False
boolAnd.b = False

if boolAnd.a_and_b != False:
  raise Exception("false & false != false")

boolAnd.a = True
boolAnd.b = True

if boolAnd.a_and_b != True:
  raise Exception("true & true != true")
