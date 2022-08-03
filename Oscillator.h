//insert the Headername here
#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "core/resource.h"
#include "SimpleOscillator.h"

class Oscillator : public SimpleOscillator {
	GDCLASS(Oscillator, SimpleOscillator);
	OBJ_SAVE_TYPE(Oscillator);


	int octaves;
	float lacunarity;
	float persistence;


protected:
	static void _bind_methods();


public:
	Oscillator();

	void set_octaves(int p_octaves) { octaves = p_octaves; }
	float get_octaves() const { return octaves; }

	void set_persistence(int p_persistence) { persistence = p_persistence; }
	float get_persistence() const { return persistence; }

	void set_lacunarity(int p_lacunarity) { lacunarity = p_lacunarity; }
	float get_lacunarity() const { return lacunarity; }

	float get_val(float time);
	float get_val_unmodified(float time);


};

#endif
