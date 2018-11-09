#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_NEED_INSTANCE_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_NEED_INSTANCE_HPP_
#include <Driller/Infrastructure/Definitions.hpp>

namespace drl {
	
	struct NeedInstance {
		float sleep{ Definitions::BaseNeed_Sleep };
		float fun{ Definitions::BaseNeed_Fun };
		float nutrition{ Definitions::BaseNeed_Nutrition };

		float sleepMinimum{ Definitions::BaseNeedMin_Sleep };
		float funMinimum{ Definitions::BaseNeedMin_Fun };
		float nutritionMinimum{ Definitions::BaseNeedMin_Nutrition };
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_NEED_INSTANCE_HPP_