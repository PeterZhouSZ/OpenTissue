INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src )

ADD_EXECUTABLE(unit_nonlinear_solver src/unit_nonlinear_solver.cpp)

TARGET_LINK_LIBRARIES(unit_nonlinear_solver ${OPENTISSUE_LIBS} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

INSTALL(
  TARGETS unit_nonlinear_solver
  RUNTIME DESTINATION  bin/units
  )

ADD_TEST( unit_nonlinear_solver unit_nonlinear_solver )
