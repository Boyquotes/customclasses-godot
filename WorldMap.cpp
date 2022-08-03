#include "WorldMap.h"

WorldMap::WorldMap() {}

//float(*get_val_unnmodified)(Vector3) = &WorldMap::get_val_unnmodified; // selects int f(int)
//Bind all your methods used in this class
void WorldMap::_bind_methods() {
	//getter/setters

	//ClassDB::bind_method(D_METHOD("set_test", "test"), &WorldMap::set_test);
	//ClassDB::bind_method(D_METHOD("get_test"), &WorldMap::get_test);

	ClassDB::bind_method(D_METHOD("set_oscillator_domain", "oscillator_domain"), &WorldMap::set_oscillator_domain);
	ClassDB::bind_method(D_METHOD("get_oscillator_domain"), &WorldMap::get_oscillator_domain);

	ClassDB::bind_method(D_METHOD("set_map_domain", "map_domain"), &WorldMap::set_map_domain);
	ClassDB::bind_method(D_METHOD("get_map_domain"), &WorldMap::get_map_domain);

	ClassDB::bind_method(D_METHOD("set_parameters", "parameters"), &WorldMap::set_parameters);
	ClassDB::bind_method(D_METHOD("get_parameters"), &WorldMap::get_parameters);

	ClassDB::bind_method(D_METHOD("set_time", "time"), &WorldMap::set_time);
	ClassDB::bind_method(D_METHOD("get_time"), &WorldMap::get_time);

	ClassDB::bind_method(D_METHOD("set_init_map_pos", "init_map_pos"), &WorldMap::set_init_map_pos);
	ClassDB::bind_method(D_METHOD("get_init_map_pos"), &WorldMap::get_init_map_pos);

	//other methods
	ClassDB::bind_method(D_METHOD("get_world_pos", "map_pos"), &WorldMap::get_world_pos);
	ClassDB::bind_method(D_METHOD("get_map_pos", "world_pos"), &WorldMap::get_map_pos);

	ClassDB::bind_method(D_METHOD("get_val_dict", "map_pos"), static_cast<Dictionary (WorldMap::*)(Vector2) > (&WorldMap::get_val_dict));
	ClassDB::bind_method(D_METHOD("get_val_dict", "world_pos"), static_cast<Dictionary(WorldMap::*)(Vector3)> (&WorldMap::get_val_dict));

	ClassDB::bind_method(D_METHOD("get_val", "map_pos"), static_cast<float (WorldMap::*)(Vector2)> (&WorldMap::get_val));
	ClassDB::bind_method(D_METHOD("get_val", "world_pos"), static_cast<float (WorldMap::*)(Vector3)> (&WorldMap::get_val));

	ClassDB::bind_method(D_METHOD("get_val_unnmodified", "map_pos"), static_cast<float (WorldMap::*)(Vector2)> (&WorldMap::get_val_unnmodified));
	ClassDB::bind_method(D_METHOD("get_val_unnmodified", "world_pos"), static_cast<float (WorldMap::*)(Vector3)> (&WorldMap::get_val_unnmodified));

	ClassDB::bind_method(D_METHOD("get_static_objects"), &WorldMap::get_static_objects);
	ClassDB::bind_method(D_METHOD("init_static_objects", "static_object_list"), &WorldMap::init_static_objects);

	ClassDB::bind_method(D_METHOD("get_parameter_names"), &WorldMap::get_parameter_names);
	ClassDB::bind_method(D_METHOD("get_world_correction_factor"), &WorldMap::get_world_correction_factor);

	ClassDB::bind_method(D_METHOD("duplicate", "p_subresources"), &WorldMap::duplicate);

	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "test"), "set_test", "get_test");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "oscillator_domain"), "set_oscillator_domain", "get_oscillator_domain");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "map_domain"), "set_map_domain", "get_map_domain");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "parameters"), "set_parameters", "get_parameters");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "time"), "set_time", "get_time");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "init_map_pos"), "set_init_map_pos", "get_init_map_pos");
}

//Custom Functions

Vector3 WorldMap::get_world_pos(Vector2 map_pos)
{
	/*Vector3 world_pos = Vector3();
	world_pos.x = (map_pos.x - init_map_pos.x) * map_domain->*/

	return Vector3();
}

Vector2 WorldMap::get_map_pos(Vector3 world_pos)
{
	return Vector2();
}

Dictionary WorldMap::get_val_dict(Vector2 map_pos)
{
	return Dictionary();
}

Dictionary WorldMap::get_val_dict(Vector3 world_pos)
{
	return Dictionary();
}

float WorldMap::get_val(Vector2 map_pos)
{
	return 0.0f;
}

float WorldMap::get_val(Vector3 world_pos)
{
	return 0.0f;
}

float WorldMap::get_val_unnmodified(Vector2 map_pos)
{
	return 0.0f;
}

float WorldMap::get_val_unnmodified(Vector3 world_pos)
{
	return 0.0f;
}

Array WorldMap::get_static_objects()
{
	return Array();
}

void WorldMap::init_static_objects(Array static_object_list)
{
}

Array WorldMap::get_parameter_names()
{
	return Array();
}

float WorldMap::get_world_correction_factor()
{
	return 0.0f;
}

Ref<Resource> WorldMap::duplicate(bool p_subresources) const
{
	return Ref<Resource>();
}
