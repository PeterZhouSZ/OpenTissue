//
// OpenTissue, A toolbox for physical based simulation and animation.
// Copyright (C) 2007 Department of Computer Science, University of Copenhagen
//
#include <OpenTissue/configuration.h>

#include "simulator_type_compile_test.h"

template< typename types  >
class test4
  : public OpenTissue::mbd::ConstraintBasedShockPropagationStepper< types, OpenTissue::mbd::ProjectedGaussSeidel<typename types::math_policy> >
{};

typedef OpenTissue::mbd::default_ublas_math_policy<double>  math_types;

void (*case4_ptr1)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::BisectionStepSimulator> );
void (*case4_ptr2)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ExplicitFixedStepSimulator> );
void (*case4_ptr3)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ExplicitSeparateErrorCorrectionFixedStepSimulator> );
void (*case4_ptr4)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::FixPointStepSimulator> );
void (*case4_ptr5)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ImplicitFixedStepSimulator> );
void (*case4_ptr6)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::SemiImplicitFixedStepSimulator> );
//void (*case4_ptr7)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::SeparatedCollisionContactFixedStepSimulator> );
