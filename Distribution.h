//insert the Headername here
#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "core/resource.h"


class Distribution : public Resource {
	GDCLASS(Distribution, Resource);
	OBJ_SAVE_TYPE(Distribution);


protected:
	static void _bind_methods();


public:
	Distribution();




};

#endif
