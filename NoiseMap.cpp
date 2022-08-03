#include "NoiseMap.h"

#include "core/core_string_names.h"

NoiseMap::NoiseMap() {}

//Bind all your methods used in this class
void NoiseMap::_bind_methods(){
  ClassDB::bind_method(D_METHOD("get_noise", "x", "y"), &NoiseMap::get_noise);
  ClassDB::bind_method(D_METHOD("get_noise_unmodified",  "x", "y"), &NoiseMap::get_noise_unmodified);
  ClassDB::bind_method(D_METHOD("randomize_seed"), &NoiseMap::randomize_seed);

  ClassDB::bind_method(D_METHOD("set_name", "name"), &NoiseMap::set_name);
  ClassDB::bind_method(D_METHOD("get_name"), &NoiseMap::get_name);

  ClassDB::bind_method(D_METHOD("set_mod", "mod"), &NoiseMap::set_mod);
  ClassDB::bind_method(D_METHOD("get_mod"), &NoiseMap::get_mod);

  ClassDB::bind_method(D_METHOD("set_mult", "mult"), &NoiseMap::set_mult);
  ClassDB::bind_method(D_METHOD("get_mult"), &NoiseMap::get_mult);

  ClassDB::bind_method(D_METHOD("set_add", "add"), &NoiseMap::set_add);
  ClassDB::bind_method(D_METHOD("get_add"), &NoiseMap::get_add);

  ClassDB::bind_method(D_METHOD("set_units", "units"), &NoiseMap::set_units);
  ClassDB::bind_method(D_METHOD("get_units"), &NoiseMap::get_units);


  ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
  ADD_PROPERTY(PropertyInfo(Variant::REAL, "mod"), "set_mod", "get_mod");
  ADD_PROPERTY(PropertyInfo(Variant::REAL, "mult"), "set_mult", "get_mult");
  ADD_PROPERTY(PropertyInfo(Variant::REAL, "add"), "set_add", "get_add");
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "units"), "set_units", "get_units");
}

//Custom Functions
float NoiseMap::get_noise(float x, float y)
{
	//mult and add change the values in reference to the range -1 to 1, mod maps that range to the real world range
	return ((get_noise_2d(x,y) * mult) + add) * mod; 
}

float NoiseMap::get_noise_unmodified(float x, float y)
{
	//mult and add change the values in reference to the range -1 to 1
	return ((get_noise_2d(x,y) * mult) + add);
}

void NoiseMap::randomize_seed()
{
	set_seed((int)rand());
}
