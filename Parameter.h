//insert the Headername here
#ifndef PARAMETER_H
#define PARAMETER_H

#include "core/resource.h"
#include "core/dictionary.h"
#include "Oscillator.h"
#include "NoiseMap.h"

//using std::unordered_map;

class Parameter : public Resource {
	GDCLASS(Parameter, Resource);
	OBJ_SAVE_TYPE(Parameter);

	
protected:
	static void _bind_methods();
	//maybe I should have oscillators and oscillator keys 
	Array oscillators;
	Array immutable_maps;//mutable maps
	String name;
	//This basically determines the weight of each map out of one.If you divide every value by the largest, then you get relative weight.
	//But wait, if I want them to be out of one, I would need to make global parameter mod be all of the mods combined.
	float mod;

public:
	Parameter();

	void reset_mod();
	void set_name(String p_name) { name = p_name;}
	String get_name() const {return name;}

	void set_oscillators(Array p_oscillators) { oscillators = p_oscillators; reset_mod(); }
	Array get_oscillators() const { return oscillators; }

	void set_immutable_maps(Array p_immutable_maps) { immutable_maps = p_immutable_maps; reset_mod(); }
	Array get_immutable_maps() const {return immutable_maps;}

	void set_mod(float p_mod) {mod = p_mod;} //not for normal use
	float get_mod() const {return mod;}

	float get_val(float x, float y, float time) ;
	float get_val_unmodified(float x, float y, float time);

	Ref<Resource> duplicate(bool p_subresources) const override; //overriden function

	void randomize_seeds();
};

#endif
