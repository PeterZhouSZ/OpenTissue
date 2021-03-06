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

typedef OpenTissue::mbd::default_ublas_math_policy<float> math_types;

void (*fcase4_ptr1)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::BisectionStepSimulator> );
void (*fcase4_ptr2)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ExplicitFixedStepSimulator> );
void (*fcase4_ptr3)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ExplicitSeparateErrorCorrectionFixedStepSimulator> );
void (*fcase4_ptr4)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::FixPointStepSimulator> );
void (*fcase4_ptr5)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::ImplicitFixedStepSimulator> );
void (*fcase4_ptr6)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::SemiImplicitFixedStepSimulator> );
//void (*fcase4_ptr7)() = &(simulator_type_compile_test<math_types, test4,OpenTissue::mbd::SeparatedCollisionContactFixedStepSimulator> );
