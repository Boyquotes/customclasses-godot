//insert the Headername here
#ifndef MAPDOMAIN_H
#define MAPDOMAIN_H

#include "core/resource.h"

//using std::unordered_map;

class MapDomain : public Resource {
	GDCLASS(MapDomain, Resource);
	OBJ_SAVE_TYPE(MapDomain);

	
protected:
	static void _bind_methods();

	float rg_tconversion;
	float mw_conversion;

public:
	MapDomain();

	void set_rg_tconversion(float p_rg_tconversion) { rg_tconversion = p_rg_tconversion;}
	float get_rg_tconversion() const {return rg_tconversion;}


	void set_mw_conversion(float p_mw_conversion) { mw_conversion = p_mw_conversion; }
	float get_mw_conversion() const { return mw_conversion; }
};

#endif
