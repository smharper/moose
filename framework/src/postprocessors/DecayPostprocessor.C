#include "DecayPostprocessor.h"

registerMooseObject("MooseApp", DecayPostprocessor);

defineLegacyParams(DecayPostprocessor);

InputParameters
DecayPostprocessor::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();

  params.addRequiredParam<PostprocessorName>("initial_val", "The initial concentration");
  params.addRequiredParam<Real>("rate", "Decay rate");
  params.addRequiredParam<Real>("travel_time", "Time of the species spent outside of the problem");
  return params;
}

DecayPostprocessor::DecayPostprocessor(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _initial_val(getPostprocessorValue("initial_val")),
    _rate(getParam<Real>("rate")),
    _travel_time(getParam<Real>("travel_time"))
{
}

void
DecayPostprocessor::initialize()
{
}

void
DecayPostprocessor::execute()
{
}

PostprocessorValue
DecayPostprocessor::getValue()
{
  return _initial_val * std::exp(-_rate * _travel_time);
}

