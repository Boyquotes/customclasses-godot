#include "WorldMap.h"
#include <typeinfo>/*
...
cout << typeid(variable).name() << endl;*/


//float(*get_val_unmodified)(Vector3) = &WorldMap::get_val_unmodified; // selects int f(int)
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

	ClassDB::bind_method(D_METHOD("get_val_dict", "world_or_map_pos"), &WorldMap::get_val_dict);

	ClassDB::bind_method(D_METHOD("get_val", "world_or_map_pos"), (&WorldMap::get_val));

	ClassDB::bind_method(D_METHOD("get_val_unmodified", "world_or_map_pos"), (&WorldMap::get_val_unmodified));

	ClassDB::bind_method(D_METHOD("get_static_object_list"), &WorldMap::get_static_object_list);
	ClassDB::bind_method(D_METHOD("set_static_object_list", "static_object_list"), &WorldMap::set_static_object_list);

	ClassDB::bind_method(D_METHOD("get_parameter_names"), &WorldMap::get_parameter_names);
	ClassDB::bind_method(D_METHOD("get_world_correction_factor"), &WorldMap::get_world_correction_factor);

	ClassDB::bind_method(D_METHOD("duplicate", "p_subresources"), &WorldMap::duplicate);

	ClassDB::bind_method(D_METHOD("randomize_seeds"), &WorldMap::randomize_seeds);

	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "test"), "set_test", "get_test");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "oscillator_domain"), "set_oscillator_domain", "get_oscillator_domain");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "map_domain"), "set_map_domain", "get_map_domain");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "parameters"), "set_parameters", "get_parameters");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "time"), "set_time", "get_time");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "init_map_pos"), "set_init_map_pos", "get_init_map_pos");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "static_object_list"), "set_static_object_list", "get_static_object_list");
}

//Custom Functions
WorldMap::WorldMap() {
	if (typeid(oscillator_domain).name() != typeid(OscillatorDomain).name()) {
		OS::get_singleton()->print("Does not have oscillator domain\n");
	}
	if (typeid(map_domain).name() != typeid(MapDomain).name()) {
		OS::get_singleton()->print("Does not have map domain\n");
	}

}

Vector3 WorldMap::get_world_pos(Vector2 map_pos)
{
	Vector3 world_pos = Vector3();
	//world_pos.x = (map_pos.x) * map_domain.mw_conversion #
	world_pos.x = (map_pos.x - init_map_pos.x) * map_domain->get_mw_conversion();
	world_pos.y = 0; //this is because I don't want to rely on their being a particular param
	world_pos.z = (map_pos.y - init_map_pos.y) * map_domain->get_mw_conversion();
	//i can just solve it at the site it is needed
	//world_pos.z = (map_pos.y) * map_domain.mw_conversion #
	return world_pos;
}

Vector2 WorldMap::get_map_pos(Vector3 world_pos)
{
	Vector2 map_pos = Vector2();
	map_pos.x = (world_pos.x / map_domain->get_mw_conversion()) + init_map_pos.x; //+ init_map_pos.x
	//map_pos.x = (world_pos.x / map_domain.mw_conversion)
	map_pos.y = (world_pos.z / map_domain->get_mw_conversion()) + init_map_pos.y; // + init_map_pos.y
	//map_pos.y = (world_pos.z / map_domain.mw_conversion)
	return map_pos;
}

Dictionary WorldMap::get_val_dict(Variant map_or_world_pos)
{
	Dictionary val_dict = Dictionary();
	Vector2 map_pos;
	if (map_or_world_pos.get_type() == Variant::Type::VECTOR3) {
		map_pos = get_map_pos(map_or_world_pos);
	}
	else {
		map_pos = map_or_world_pos;
	}
		
	for (int i = 0; i < parameters.size(); i++) {
		val_dict[((Ref<Parameter>)parameters[i])->call("get_name")]
			= ((Ref<Parameter>)parameters[i])->call("get_val", (float)map_pos.x, (float)map_pos.y, (float)time);
	}

	return val_dict;
}

float WorldMap::get_val(String parameter_name, Variant map_or_world_pos)
{
	float val = 0;
	Vector2 map_pos;
	if (map_or_world_pos.get_type() == Variant::Type::VECTOR3) {
		map_pos = get_map_pos(map_or_world_pos);
	}
	else {
		map_pos = map_or_world_pos;
	}

	for (int i = 0; i < parameters.size(); i++) {
		if (((Ref<Parameter>)parameters[i])->call("get_name") == parameter_name){
			val = ((Ref<Parameter>)parameters[i])->call("get_val", (float)map_pos.x, (float)map_pos.y, (float)time);
			break;
		}
	}
	return val;
}

float WorldMap::get_val_unmodified(String parameter_name, Variant map_or_world_pos)
{
	float val = 0;
	Vector2 map_pos;
	if (map_or_world_pos.get_type() == Variant::Type::VECTOR3) {
		map_pos = get_map_pos(map_or_world_pos);
	}
	else {
		map_pos = map_or_world_pos;
	}

	for (int i = 0; i < parameters.size(); i++) {
		if (((Ref<Parameter>)parameters[i])->call("get_name") == parameter_name) {
			val = ((Ref<Parameter>)parameters[i])->call("get_val_unmodified", (float)map_pos.x, (float)map_pos.y, (float)time);
			break;
		}
	}
	return val;
}

Array WorldMap::get_static_object_list()
{
	/*Array new_static_object_list;

	for (int i = 0; i < static_objects.size(); i++) {
		new_static_object_list.push_back()
	}*/
	return static_object_list; //(Ref<Array>)
}

void WorldMap::set_static_object_list(Array p_static_object_list)
{
	static_object_list = p_static_object_list;
}

Array WorldMap::get_parameter_names()
{
	Array parameter_names;
	for (int i = 0; i < parameters.size(); i++) {
		parameter_names.push_back(((Ref<Parameter>)parameters[i])->call("get_name"));
	}
	return parameter_names;
}

Vector3 WorldMap::get_world_correction_factor()
{
	Vector2 map_pos = init_map_pos;
	Vector3 world_pos = Vector3();
	world_pos.x = (map_pos.x) * map_domain->get_mw_conversion(); //#(map_pos.x - init_map_pos.x) * map_domain.mw_conversion
	world_pos.y = 0; //#this is because I don't want to rely on their being a particular param
	//#i can just solve it at the site it is needed
	world_pos.z = (map_pos.y) * map_domain->get_mw_conversion(); //#(map_pos.y - init_map_pos.y) * map_domain.mw_conversion
	return world_pos;
}

Ref<Resource> WorldMap::duplicate(bool p_subresources) const //this is not quite ready. It doesn't actually to full duplication
{
	print_line("WORLDMAP DUPLICATE");
	Ref<WorldMap> new_world_map = Resource::duplicate();
	if (p_subresources == true) {
		new_world_map->set_oscillator_domain(oscillator_domain->duplicate(true));
		new_world_map->set_map_domain(map_domain->duplicate(true));
		new_world_map->set_time(time);
		Array new_parameters;

		for (int i = 0; i < parameters.size(); i++) {
			new_parameters.push_back(((Ref<Parameter>)parameters[i])->duplicate(true));
		}

		new_world_map->set_parameters(new_parameters);
		new_world_map->set_init_map_pos(init_map_pos);

		Array new_static_object_list;
		for (int i = 0; i < static_object_list.size(); i++) {
			new_static_object_list.push_back(((Ref<Resource>)static_object_list[i])->duplicate(true));//should be ref static object
		}
	}

	return new_world_map;
}

void WorldMap::randomize_seeds()
{

	for (int i = 0; i < parameters.size(); i++) {
		((Ref<Parameter>)parameters[i])->randomize_seeds();
	}

}
