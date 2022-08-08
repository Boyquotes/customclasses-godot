#include "Parameter.h"

#include "core/core_string_names.h"
#include "Oscillator.h"
#include "core/variant.h"

//const StringName get_val_string = StringName("get_val");

//Bind all your methods used in this class
void Parameter::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_val", "x", "y", "time"), &Parameter::get_val);
	ClassDB::bind_method(D_METHOD("get_val_unmodified", "x", "y", "time"), &Parameter::get_val_unmodified);

	ClassDB::bind_method(D_METHOD("set_name", "p_name"), &Parameter::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Parameter::get_name);

	ClassDB::bind_method(D_METHOD("set_immutable_maps", "p_immutable_maps"), &Parameter::set_immutable_maps);
	ClassDB::bind_method(D_METHOD("get_immutable_maps"), &Parameter::get_immutable_maps);

	ClassDB::bind_method(D_METHOD("set_oscillators", "p_oscillators"), &Parameter::set_oscillators);
	ClassDB::bind_method(D_METHOD("get_oscillators"), &Parameter::get_oscillators);

	ClassDB::bind_method(D_METHOD("set_mod", "p_mod"), &Parameter::set_mod);
	ClassDB::bind_method(D_METHOD("get_mod"), &Parameter::get_mod);

	ClassDB::bind_method(D_METHOD("reset_mod"), &Parameter::reset_mod);

	ClassDB::bind_method(D_METHOD("duplicate", "p_subresources"), &Parameter::duplicate);


	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "oscillators"), "set_oscillators", "get_oscillators");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "immutable_maps"), "set_immutable_maps", "get_immutable_maps");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "mod"), "set_mod", "get_mod");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
}

//Custom Functions
Parameter::Parameter() {
	OS::get_singleton()->print("PARAMETER CONSTRUCTOR\n");
	reset_mod();
}

float Parameter::get_val(float x, float y, float time)
{
	float total = 0;

	for (int i = 0; i < oscillators.size(); i++) {
		//if (oscillators[i].has_method("get_val")) { //I don't need to check if it actually has the method!!
		total += (float)((Ref<Oscillator>)oscillators[i])->call("get_val", time);
		//}
	}
	for (int i = 0; i < immutable_maps.size(); i++) {
		//if (immutable_maps[i].has_method("get_val")) { //I don't need to check if it actually has the method!!
		total += (float)((Ref<NoiseMap>)immutable_maps[i])->call("get_noise", x, y);
		//}
	}
	return total;
}

float Parameter::get_val_unmodified(float x, float y, float time)
{
	return get_val(x, y, time) / mod;
}

Ref<Resource> Parameter::duplicate(bool p_subresources)  const 
{

	print_line("PARAMETER DUPLICATE");
	
	Ref<Parameter> new_parameter = Resource::duplicate();
	if (p_subresources == true) {

		Array new_oscillators;
		for (int i = 0; i < oscillators.size(); i++) {
			new_oscillators.push_back(((Ref<Oscillator>)oscillators[i])->duplicate(true));
		}
		new_parameter->set_oscillators(new_oscillators);


		Array new_immutable_maps;
		for (int i = 0; i < immutable_maps.size(); i++) {
			new_immutable_maps.push_back(((Ref<NoiseMap>)immutable_maps[i])->duplicate(true));
		}
		new_parameter->set_immutable_maps(new_immutable_maps);

		new_parameter->set_mod(mod);
	}
	new_parameter->reset_mod();
	return (Ref<Parameter>)new_parameter;

	
}

void Parameter::reset_mod()
{
	//maybe I should just determine relative weights for each thing
	//this determines a value that all noise map get_vals can be divided by, to get relative weights of each value out of one
	float f_mod = 0.0; //function mod

	for (int i = 0; i < immutable_maps.size(); i++) {
		f_mod += ((Ref<NoiseMap>)immutable_maps[i])->get_mod();
	}
	for (int i = 0; i < oscillators.size(); i++) {
		f_mod += ((Ref<Oscillator>)oscillators[i])->get_mod();
	}

	mod = f_mod;
}


void Parameter::randomize_seeds()
{
	for (int i = 0; i < immutable_maps.size(); i++) {
		((Ref<NoiseMap>)immutable_maps[i])->randomize_seed();
	}
	/*for (int i = 0; i < oscillators.size(); i++) {
		((Ref<Oscillator>)oscillators[i])->randomize_seed();
	}*/
}
