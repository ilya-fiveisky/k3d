K3D_TEST(node.equality
	K3D_PYTHON_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/node.equality.py
	REQUIRES K3D_BUILD_NODE_MODULE
	LABELS node equality)
