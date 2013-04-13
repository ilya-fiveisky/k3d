K3D_TEST(boolean.conjunction
	K3D_PYTHON_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/boolean.conjunction.py
	REQUIRES K3D_BUILD_BOOLEAN_MODULE
	LABELS boolean conjunction)

K3D_TEST(boolean.disjunction
	K3D_PYTHON_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/boolean.disjunction.py
	REQUIRES K3D_BUILD_BOOLEAN_MODULE
	LABELS boolean disjunction)

K3D_TEST(boolean.negation
	K3D_PYTHON_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/boolean.negation.py
	REQUIRES K3D_BUILD_BOOLEAN_MODULE
	LABELS boolean negation)
