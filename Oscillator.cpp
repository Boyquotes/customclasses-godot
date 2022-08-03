#include "Oscillator.h"

#include "core/core_string_names.h"

Oscillator::Oscillator() {}

//Bind all your methods used in this class
void Oscillator::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_val", "time"), &Oscillator::get_val);
	ClassDB::bind_method(D_METHOD("get_val_unmodified", "time"), &Oscillator::get_val_unmodified);
	
	ClassDB::bind_method(D_METHOD("set_octaves", "octaves"), &Oscillator::set_octaves);
	ClassDB::bind_method(D_METHOD("get_octaves"), &Oscillator::get_octaves);

	ClassDB::bind_method(D_METHOD("set_persistence", "persistence"), &Oscillator::set_persistence);
	ClassDB::bind_method(D_METHOD("get_persistence"), &Oscillator::get_persistence);

	ClassDB::bind_method(D_METHOD("set_lacunarity", "lacunarity"), &Oscillator::set_lacunarity);
	ClassDB::bind_method(D_METHOD("get_lacunarity"), &Oscillator::get_lacunarity);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "octaves"), "set_octaves", "get_octaves");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "persistence"), "set_persistence", "get_persistence");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "lacunarity"), "set_lacunarity", "get_lacunarity");
}

//Custom Functions
float Oscillator::get_val(float time)
{

	float total = 0;

	total += amp_mult * sin((period * time) + phase_shift) + amp_shift;

	for (int i = 0; i < octaves; i++) {
		total += (amp_mult * pow(persistence, i / (i - octaves))) * sin(((period * pow(lacunarity, i / (i - octaves))) * time) + (phase_shift * pow(lacunarity, i / (i - octaves)))) + amp_shift;
	}
	return total;
}

float Oscillator::get_val_unmodified(float time) 
{
	return get_val(time) / amp_mult; //?
}



