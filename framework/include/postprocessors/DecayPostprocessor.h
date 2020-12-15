#pragma once

#include "GeneralPostprocessor.h"

class DecayPostprocessor;

template <>
InputParameters validParams<DecayPostprocessor>();

class DecayPostprocessor : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  DecayPostprocessor(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual PostprocessorValue getValue() override;

protected:
  const PostprocessorValue & _initial_val;
  const Real & _rate;
  const Real & _travel_time;
};
