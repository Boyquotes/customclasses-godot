#include "register_types.h"
#include "core/class_db.h"
#include "NoiseMap.h"
#include "Oscillator.h"
#include "SimpleOscillator.h"
#include "WorldMap.h"
#include "Parameter.h"
#include "OscillatorDomain.h"
#include "MapDomain.h"

void register_customclasses_types(){
	ClassDB::register_class<NoiseMap>();
	ClassDB::register_class<SimpleOscillator>();
	ClassDB::register_class<Oscillator>();
	ClassDB::register_class<Parameter>();
	ClassDB::register_class<OscillatorDomain>();
	ClassDB::register_class<MapDomain>();
	ClassDB::register_class<WorldMap>();

}

void unregister_customclasses_types() {
}
