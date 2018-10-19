#include <Driller/Services/CostService.hpp>

namespace drl {

	CostService::CostService(void) {
		
	}
	CostService::~CostService(void) {
		
	}

	int CostService::getDigShaftCost(int _level) const {
		return 100 * (_level * _level);
	}
	float CostService::getBuildingMultiplierCost(int _level, int _column) const {
		return static_cast<float>(_level * (_column / 10));
	}
	float CostService::getDigTileTimeMultiplierCost(int _level, int _column) const {
		return static_cast<float>(_level * (_column / 10));
	}

}