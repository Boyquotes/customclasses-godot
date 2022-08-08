#include "OscillatorDomain.h"
#include "core/Variant.h"
#include "core/core_string_names.h"


OscillatorDomain::OscillatorDomain() {};


//Bind all your methods used in this class
void OscillatorDomain::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_period", "period"), &OscillatorDomain::set_period);
	ClassDB::bind_method(D_METHOD("get_period"), &OscillatorDomain::get_period);
	
	ClassDB::bind_method(D_METHOD("set_phase_shift", "phase_shift"), &OscillatorDomain::set_phase_shift);
	ClassDB::bind_method(D_METHOD("get_phase_shift"), &OscillatorDomain::get_phase_shift);

	ClassDB::bind_method(D_METHOD("set_units", "units"), &OscillatorDomain::set_units);
	ClassDB::bind_method(D_METHOD("get_units"), &OscillatorDomain::get_units);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "period"), "set_period", "get_period");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "phase_shift"), "set_phase_shift", "get_phase_shift");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "units"), "set_units", "get_units");
}

//Custom Functions
