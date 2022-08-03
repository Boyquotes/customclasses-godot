#include "SimpleOscillator.h"

#include "core/core_string_names.h"

SimpleOscillator::SimpleOscillator() {}

//Bind all your methods used in this class
void SimpleOscillator::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_val", "time"), &SimpleOscillator::get_val);
	ClassDB::bind_method(D_METHOD("get_val_unmodified", "time"), &SimpleOscillator::get_val_unmodified);
	ClassDB::bind_method(D_METHOD("warp_period", "current_time", "new_period"), &SimpleOscillator::warp_period);

	ClassDB::bind_method(D_METHOD("set_amp_units", "amp_units"), &SimpleOscillator::set_amp_units);
	ClassDB::bind_method(D_METHOD("get_amp_units"), &SimpleOscillator::get_amp_units);

	ClassDB::bind_method(D_METHOD("set_amp_mult", "amp_mult"), &SimpleOscillator::set_amp_mult);
	ClassDB::bind_method(D_METHOD("get_amp_mult"), &SimpleOscillator::get_amp_mult);

	ClassDB::bind_method(D_METHOD("set_amp_shift", "amp_shift"), &SimpleOscillator::set_amp_shift);
	ClassDB::bind_method(D_METHOD("get_amp_shift"), &SimpleOscillator::get_amp_shift);

	ClassDB::bind_method(D_METHOD("set_phase_units", "phase_units"), &SimpleOscillator::set_phase_units);
	ClassDB::bind_method(D_METHOD("get_phase_units"), &SimpleOscillator::get_phase_units);

	ClassDB::bind_method(D_METHOD("set_period", "period"), &SimpleOscillator::set_period);
	ClassDB::bind_method(D_METHOD("get_period"), &SimpleOscillator::get_period);

	ClassDB::bind_method(D_METHOD("set_phase_shift", "phase_shift"), &SimpleOscillator::set_phase_shift);
	ClassDB::bind_method(D_METHOD("get_phase_shift"), &SimpleOscillator::get_period);


	ADD_PROPERTY(PropertyInfo(Variant::STRING, "amp_units"), "set_amp_units", "get_amp_units");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "amp_mult"), "set_amp_mult", "get_amp_mult");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "amp_shift"), "set_amp_shift", "get_amp_shift");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "phase_units"), "set_phase_units", "get_phase_units");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "period"), "set_period", "get_period");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "phase_shift"), "set_phase_shift", "get_phase_shift");
}

//Custom Functions
float SimpleOscillator::get_val(float time)
{
	return amp_mult * sin((period * time) + phase_shift) + amp_shift;
}

float SimpleOscillator::get_val_unmodified(float time)
{
	return (amp_mult * sin(((period * time) + phase_shift) / period) + amp_shift) / amp_mult;
}

void SimpleOscillator::warp_period(float current_time, float new_period)
{
	phase_shift += current_time * (new_period - period);
	period = new_period;
}
