//insert the Headername here
#ifndef SIMPLEOSCILLATOR_H
#define SIMPLEOSCILLATOR_H

#include "core/resource.h"
#include "core/os/os.h"

class SimpleOscillator : public Resource {
	GDCLASS(SimpleOscillator, Resource);
	OBJ_SAVE_TYPE(SimpleOscillator);




protected:
	String amp_units; //must be plural
	float mod; //what the value is multiplied by, it represents the real world interpretation of the change between 0 and 1#ONLY USED WHEN vals = MODIFIED
	float amp_shift;

	String phase_units; //must be plural
	float period; // phase mult #represents the real world time between 0 and 1 #time / cycle, also known as phase_mult
	float phase_shift;

	static void _bind_methods();

public:
	SimpleOscillator();

	void set_amp_units(String p_amp_units) { amp_units = p_amp_units; }
	String get_amp_units() const { return amp_units; }

	void set_mod(float p_mod) { mod = p_mod; }
	float get_mod() const { return mod; }

	void set_amp_shift(float p_amp_shift) { amp_shift = p_amp_shift; }
	float get_amp_shift() const { return amp_shift; }

	void set_phase_units(String p_phase_units) { phase_units = p_phase_units; }
	String get_phase_units() const { return phase_units; }

	void set_period(float p_period) { period = p_period; }
	//The question is how the period is changed. Shift is easier, but does the set_period also warp the starting point? perhaps give another function for that

	float get_period() const { return period; }

	void set_phase_shift(float p_phase_shift) { phase_shift = p_phase_shift; }
	float get_phase_shift() const { return phase_shift; }

	float get_val(float time);

	float get_val_unmodified(float time);

	void warp_period(float current_time, float new_period); //this changes the starting point in relation to how much the time is warped
};

#endif
