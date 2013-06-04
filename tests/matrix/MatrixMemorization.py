#python

import k3d
import testing

document = k3d.new_document()

matrixMemorization = k3d.plugin.create("MatrixMemorization", document)

matrixMemorization.input = 2 * k3d.identity3()

if matrixMemorization.output != k3d.identity3():
  raise Exception("Output before event should be: " + str(k3d.identity3()) + 
    " but is: " + str(matrixMemorization.output))

matrixMemorization.event = True

if matrixMemorization.output != matrixMemorization.input:
  raise Exception("Output after event sould be: " + str(matrixMemorization.input) + 
    " but is: " + str(matrixMemorization.output))
