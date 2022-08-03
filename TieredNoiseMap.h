//insert the Headername here
#ifndef TIEREDNOISEMAP_H
#define TIEREDNOISEMAP_H

#include "modules/opensimplex/open_simplex_noise.h"
#include <string.h>
#include "NoiseMap.h"
#include "core/resource.h"

class TieredNoiseMap : private NoiseMap {
  GDCLASS(TieredNoiseMap, NoiseMap);

  float lower_bound = -1; //this is just based on open simplex noise lower range being - 1
  int num_states = 5;
  float state_width = 0.2;

  NoiseMap states[5]; //all the states that can be switched between with the parent noise map


  void reset_state_vals();

protected:
  static void _bind_methods();
  
public:
  TieredNoiseMap();

  
  float get_noise(float x, float y);

  float get_noise_unmodified(float x, float y);

  void randomize_seeds();

	
};

#endif
/*

func get_primary_noise(x:float, y:float) -> float: #for tiered noise map
	return ((get_noise_2d(x,y) * mult) + add)

#maybe there is someway to put this on a curve, so the closer it gets to the edges, the less the primary noise moves
#so that it doesn't go past -1 or +1


func randomize_seeds():
	for state in states:
		state.randomize_seed()

func get_noise(x : float, y : float) -> float: #BUG POTENTIAL

	var primary_noise : float = get_primary_noise(x,y)

	if primary_noise < float(lower_bound):
		return states[0].get_noise(x, y)

	#I'm making a weighted value between 1 and 0, the shows how much each state should be included in the final value
	var floored_value = floor(primary_noise * num_states)/num_states


	var first_num = int((floored_value - lower_bound) / state_width )

	if (first_num + 1) >= states.size(): #plus one cause gotta correct for that damn index
		return states[states.size() - 1].get_noise(x, y)

	var relative_weight : float = (primary_noise - floored_value ) / state_width

	var secondary_noise : float =  (states[first_num].get_noise(x, y) * (1 - relative_weight)) + (states[first_num + 1].get_noise(x, y) * (relative_weight))

	return secondary_noise


func get_noise_unmodified(x,y):
	return get_noise(x, y) / mod


func _reset_state_vals():
	num_states = states.size()
	state_width = 2.0 / num_states

	var global_mod : float = 0.0
	for state in states:
		if global_mod < state.get_mod():
			global_mod = state.get_mod()

	mod = global_mod



#I think that this class doesn't need its base noise maps duplicated?
func duplicate(subresources: bool = false):# I need to go through this and make sure every member is dealt with in some way, SO far I have the noise maps, oscillators, and global mod
	#for every resource(but not their resources), I must call duplicate(true)
	var tierednoisemap : TieredNoiseMap = .duplicate()
#	if subresources == true:
#		tierednoisemap.states.clear()
#		for state in states:
#			tierednoisemap.states.push_back(state.duplicate())
#
#		_reset_state_vals()
	tierednoisemap._reset_state_vals()
	return tierednoisemap


func set_mult(mult):
	self.mult = mult
func get_mult():
	return self.mult

func set_add(add):
	self.add = add
func get_add():
	return self.add



*/
