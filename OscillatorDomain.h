//insert the Headername here
#ifndef OSCILLATORDOMAIN_H
#define OSCILLATORDOMAIN_H

#include "core/resource.h"


class OscillatorDomain : public Resource {
	GDCLASS(OscillatorDomain, Resource);
	OBJ_SAVE_TYPE(OscillatorDomain);

	
protected:
	static void _bind_methods();

	float period;
	float phase_shift;
	String units;
	

public:
	OscillatorDomain();

	void set_period(float p_period) { period = p_period;}
	float get_period() const {return period;}

	void set_phase_shift(float p_phase_shift) { phase_shift = p_phase_shift; }
	float get_phase_shift() const { return phase_shift; }

	void set_units(String p_units) { units = p_units; }
	String get_units() const { return units; }
};

#endif
