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
	Dictionary parameters;
	Vector2 init_map_pos;
	
public:
	WorldMap();

	void set_oscillator_domain(Ref<OscillatorDomain> p_oscillator_domain) { oscillator_domain = p_oscillator_domain; }
	Ref<OscillatorDomain> get_oscillator_domain() const { return oscillator_domain; }

	void set_map_domain(Ref<MapDomain> p_map_domain) { map_domain = p_map_domain; }
	Ref<MapDomain> get_map_domain() const { return map_domain; }

	void set_parameters(Dictionary p_parameters) { parameters = p_parameters; }
	Dictionary get_parameters() const { return parameters; }

	void set_time(float p_time) { time = p_time; }
	float get_time() const { return time; }

	void set_init_map_pos(Vector2 p_init_map_pos) { init_map_pos = p_init_map_pos; }
	Vector2 get_init_map_pos() const { return init_map_pos; }


	Vector3 get_world_pos(Vector2 map_pos);
	Vector2 get_map_pos(Vector3 world_pos);

	
	Dictionary get_val_dict(Vector2 map_pos);
	Dictionary get_val_dict(Vector3 world_pos);

	//void test_func();
	//void(WorldMap::* test_func_ptr)() = &test_func;
	float get_val(Vector2 map_pos);	
	float get_val(Vector3 world_pos);
	//float(WorldMap::* get_val_ptr)(Vector2) = &get_val;

	float get_val_unnmodified(Vector2 map_pos);
	float get_val_unnmodified(Vector3 world_pos);

	//OBJECTS----
	//-static objects
	Array get_static_objects();
	void init_static_objects(Array static_object_list);
	//-dynamic objects
	Array get_parameter_names();//returns keys of parameters
	float get_world_correction_factor();

	Ref<Resource> duplicate(bool p_subresources) const override; //overriden function
	
};

#endif
/*
func get_parameter_noise_map(parameter_name, noise_map_name):
	return parameters[parameter_name].immutable_maps[noise_map_name] #PASSED BY REFERENCE, SO I CAN MODIFY IT OUTSIDE OF HERE

func get_parameter_oscillator(parameter_name, oscillator_name):

	return parameters[parameter_name].oscillators[oscillator_name] #PASSED BY REFERENCE, SO I CAN MODIFY IT OUTSIDE OF HERE


func get_map_pos(world_pos):
	var map_pos = Vector2.ZERO
	map_pos.x = (world_pos.x / map_domain.mw_conversion)  + init_map_pos.x #+ init_map_pos.x
#	map_pos.x = (world_pos.x / map_domain.mw_conversion)
	map_pos.y = (world_pos.z / map_domain.mw_conversion) + init_map_pos.y #+ init_map_pos.y
#	map_pos.y = (world_pos.z / map_domain.mw_conversion)
	return map_pos

func get_world_pos(map_pos):
	var world_pos = Vector3.ZERO
#	world_pos.x = (map_pos.x) * map_domain.mw_conversion #
	world_pos.x = (map_pos.x - init_map_pos.x) * map_domain.mw_conversion
	world_pos.y = 0 #this is because I don't want to rely on their being a particular param
	#i can just solve it at the site it is needed
#	world_pos.z = (map_pos.y)  * map_domain.mw_conversion #
	world_pos.z = (map_pos.y- init_map_pos.y)  * map_domain.mw_conversion
	return world_pos

func get_val_dict(world_or_map_pos):
	var val_dict : Dictionary


	for parameter_name in parameters.keys():
		val_dict[parameter_name] = get_val(parameter_name, world_or_map_pos)

	return val_dict


func get_val(parameter_name, world_or_map_pos):
	#this changes the world position back to map position using the correction factor
	if world_or_map_pos is Vector2: #2d pos
		var map_pos = world_or_map_pos #already must be map pos
		return parameters[parameter_name].get_val(map_pos.x, map_pos.y, time)
	if world_or_map_pos is Vector3: #3d pos
		var map_pos = get_map_pos(world_or_map_pos) #I solve from world to map pos
		return parameters[parameter_name].get_val(map_pos.x, map_pos.y, time)

func get_val_unmodified(parameter_name, world_or_map_pos):
	if world_or_map_pos is Vector2: #2d pos
		var map_pos = world_or_map_pos #already must be map pos
		return parameters[parameter_name].get_val_unmodified(map_pos.x, map_pos.y, time)
	if world_or_map_pos is Vector3: #3d pos
		var map_pos = get_map_pos(world_or_map_pos) #I solve from world to map pos
		return parameters[parameter_name].get_val_unmodified(map_pos.x, map_pos.y, time)

func print_parameters():
	var parameter_key_array = parameters.keys()
	for i in parameter_key_array.size():
		print(parameter_key_array[i])


#OBJECTS-----

#-static objects
func get_static_objects():
	var new_static_object_list :Array = []

	for i in static_object_list.size():
		new_static_object_list.push_back(static_object_list[i].duplicate()) #Maybe I should change this to duplicate(True), as they might end up changing

	return new_static_object_list

func init_static_objects(static_object_list):
	self.static_object_list = static_object_list

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

func get_parameters():

	return parameters.keys()

func get_init_map_pos():
	return init_map_pos

func get_world_correction_factor():
	var map_pos = init_map_pos
	var world_pos = Vector3.ZERO
	world_pos.x = (map_pos.x) * map_domain.mw_conversion #(map_pos.x - init_map_pos.x) * map_domain.mw_conversion
	world_pos.y = 0 #this is because I don't want to rely on their being a particular param
	#i can just solve it at the site it is needed
	world_pos.z = (map_pos.y)  * map_domain.mw_conversion #(map_pos.y- init_map_pos.y)  * map_domain.mw_conversion
	return world_pos

func duplicate(subresources: bool = false):
	#for every resource(but not their resources), I must call duplicate(true)
	var new_map : Map
	if subresources == true:
		new_map = .duplicate()
		new_map.oscillator_domain = oscillator_domain.duplicate(true)
		new_map.map_domain = map_domain.duplicate(true)
		new_map.time = time
		for key in parameters.keys():
			var new_parameter = parameters[key].duplicate(true)
			new_map.parameters[key] = new_parameter
		new_map.static_object_list = static_object_list.duplicate(true)
		new_map.init_map_pos = init_map_pos

	else:
		new_map = .duplicate()

	return new_map


*/
