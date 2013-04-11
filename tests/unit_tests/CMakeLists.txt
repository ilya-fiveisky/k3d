INCLUDE_DIRECTORIES(${k3d_SOURCE_DIR})
INCLUDE_DIRECTORIES(${k3dsdk_BINARY_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${K3D_SIGC_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${K3D_GLIBMM_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

LINK_DIRECTORIES(${K3D_SIGC_LIB_DIRS})

LINK_LIBRARIES(k3dsdk)

ADD_EXECUTABLE(unit_tests main.cpp 
    signal_handler.cpp
    modules/matrix/translation_extractor_tests.cpp ${k3d_SOURCE_DIR}/modules/matrix/translation_extractor.cpp
    sdk/function_nodes_tests.cpp sdk/stdx/functional_tests.cpp
    costring_tests.cpp)

K3D_TEST(unit_tests TARGET unit_tests LABELS unit_tests)

ADD_SUBDIRECTORY(modules)
ADD_SUBDIRECTORY(sdk)
