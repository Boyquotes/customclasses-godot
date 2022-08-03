//insert the Headername here
#ifndef NOISEMAP_H
#define NOISEMAP_H

#include "modules/opensimplex/open_simplex_noise.h"

#include "core/reference.h"


class NoiseMap : public OpenSimplexNoise {
  GDCLASS(NoiseMap, OpenSimplexNoise);
  OBJ_SAVE_TYPE(NoiseMap);


  String name;
  String units; //not sure if I should use this one
  float mod; //this determines the transformation of the values between -1 and 1 to real world values, such as -40 to 120 degrees
  float add; //add added to the values between -1 and 1
  float mult; //values between -1 and 1 are multiplied by this
 


protected:
  static void _bind_methods();
  

public:
  NoiseMap();

  void set_mod(int p_mod) { mod = p_mod; }
  float get_mod() const { return mod; }
  
  void set_add(int p_add) { add = p_add ; }
  float get_add() const { return add; }

  void set_mult(int p_mult) {mult = p_mult;}
  float get_mult() const { return mult; }
  
  void set_units(String p_units) {units = p_units;}
  String get_units() const { return units; }

  void set_name(String p_name) {name = p_name;}
  String get_name() const { return name; }


  float get_noise_unmodified(float x, float y);

  float get_noise(float x, float y);

  void randomize_seed();

};

#endif
