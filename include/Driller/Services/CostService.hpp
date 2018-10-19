#ifndef INCLUDED_DRILLER_SERVICES_COST_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_COST_SERVICE_HPP_

#include <Driller/Services/Interfaces/ICostService.hpp>

namespace drl {
	
	class CostService : public ICostService {
	public:
		CostService(void);
		~CostService(void) override;

		int getDigShaftCost(int _level) const override;
		float getBuildingMultiplierCost(int _level, int _column) const override;
		float getDigTileTimeMultiplierCost(int _level, int _column) const override;
	};

}

#endif // INCLUDED_DRILLER_SERVICES_COST_SERVICE_HPP_