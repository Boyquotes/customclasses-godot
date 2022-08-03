#include "MapDomain.h"

#include "core/core_string_names.h"

MapDomain::MapDomain() {};

//const StringName get_val_string = StringName("get_val");

//Bind all your methods used in this class
void MapDomain::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_rg_tconversion", "rg_tconversion"), &MapDomain::set_rg_tconversion);
	ClassDB::bind_method(D_METHOD("get_rg_tconversion"), &MapDomain::get_rg_tconversion);

	ClassDB::bind_method(D_METHOD("set_mw_conversion", "mw_conversion"), &MapDomain::set_mw_conversion);
	ClassDB::bind_method(D_METHOD("get_mw_conversion"), &MapDomain::get_mw_conversion);


	ADD_PROPERTY(PropertyInfo(Variant::REAL, "rg_tconversion"), "set_rg_tconversion", "get_rg_tconversion");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "mw_conversion"), "set_mw_conversion", "get_mw_conversion");
}


//Custom Functions
