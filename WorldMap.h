//insert the Headername here
#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "core/resource.h"
#include "Parameter.h"
#include "MapDomain.h"
#include "OscillatorDomain.h"
#include "core/math/vector2.h"
#include "core/vector.h"

//struct test_struct_type {
//	float period;
//	float phase_shift;
//	String units;
//};

class WorldMap : public Resource {
	GDCLASS(WorldMap, Resource);
	OBJ_SAVE_TYPE(WorldMap);


protected:
	static void _bind_methods();

	
	Ref<OscillatorDomain> oscillator_domain; //Don't know if there is a better way to do this making a seperate class to do this seems annoying to me
	Ref<MapDomain> map_domain;
	float time;
	Array parameters;
	Vector2 init_map_pos;
	Array static_object_list;
	
public:
	WorldMap();

	void set_oscillator_domain(Ref<OscillatorDomain> p_oscillator_domain) { oscillator_domain = p_oscillator_domain; }
	Ref<OscillatorDomain> get_oscillator_domain() const { return Ref<OscillatorDomain>(oscillator_domain); }

	void set_map_domain(Ref<MapDomain> p_map_domain) { map_domain = p_map_domain; }
	Ref<MapDomain> get_map_domain() const { return map_domain; }

	void set_parameters(Array p_parameters) { parameters = p_parameters; }
	Array get_parameters() const { return parameters; }

	void set_time(float p_time) { time = p_time; }
	float get_time() const { return time; }

	void set_init_map_pos(Vector2 p_init_map_pos) { init_map_pos = p_init_map_pos; }
	Vector2 get_init_map_pos() const { return init_map_pos; }
	
	Vector3 get_world_pos(Vector2 map_pos);
	Vector2 get_map_pos(Vector3 world_pos);
	
	Dictionary get_val_dict(Variant map_or_world_pos);

	float get_val(String parameter_name, Variant map_or_world_pos);

	float get_val_unmodified(String parameter_name, Variant map_or_world_pos);

	//OBJECTS----
	//-static objects
	Array get_static_object_list();
	void set_static_object_list(Array static_object_list);
	//-dynamic objects
	Array get_parameter_names();//returns keys of parameters
	Vector3 get_world_correction_factor();

	Ref<Resource> duplicate(bool p_subresources) const override; //overriden function

	void randomize_seeds();
};

#endif
/*

#-dynamic objects
func init_dynamic_objects(dynamic_object_list):
	pass

func list_dyanmic_objects():
	pass

func start_event(event_name): #WILL EXPAND ON THIS, MAKE IT MORE PRODCEDURAL, LEVELS AND MIXING BETWEEN EVENTS
	#ONE EXAMPLE OF AN EVENT IS A VOLCANIC WINTER
	#THERE IS A CONTINUOS SCALE TO CERTAIN EVENTS
	#ANOTHER MAY BE A FOREST FIRE, THIS CAN BE RECORDED AS A PARAMATER, WHEN YOU GET THE VALUE AT A CERTAIN LOC, IT PROVIDES THE LIKELYHOOD OF FIRE BEING THERE
	#IN ORDER TO DO THIS, I NEED TO BE ABLE TO WRITE TO A MAP, AND THAT MAP HAS TO BE CONTINOUS
	#I CAN MIX EVENTS, HAVE MULTIPLE EVENTS GOING AT ONCE, ETC.
	pass

func list_current_events(event_name):
	pass

func load_texture_pack(texture_pack_id): #Environmental effects are part of this
	pass
*/
