#include "TieredNoiseMap.h"

TieredNoiseMap::TieredNoiseMap(){}

//Bind all your methods used in this class
void TieredNoiseMap::_bind_methods(){
  //ClassDB::bind_method(D_METHOD("get_noise", "x", "y"), &NoiseMap::get_noise);
 // ClassDB::bind_method(D_METHOD("get_noise_unmodified",  "x", "y"), &NoiseMap::get_noise_unmodified);
 // ClassDB::bind_method(D_METHOD("randomize_seeds"), &NoiseMap::randomize_seeds);

}

//Custom Functions
float TieredNoiseMap::get_noise(float x, float y)
{
	return -1.0;
	//STUB
}

float NoiseMap::get_noise_unmodified(float x, float y)
{
	//mult and add change the values in reference to the range -1 to 1
	return get_noise(x,y)/mod;
}

void TieredNoiseMap::reset_state_vals()
{
	//STUB
}

void TieredNoiseMap::randomize_seeds()
{
	//STUB
}

