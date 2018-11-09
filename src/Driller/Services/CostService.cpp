#include <Driller/Services/CostService.hpp>
#include <algorithm>

namespace drl {

	CostService::CostService(void) {
		
	}
	CostService::~CostService(void) {
		
	}

	int CostService::getDigShaftCost(int _level) const {
		return 100 * (_level * _level);
	}
	float CostService::getBuildingMultiplierCost(int _level, int _column) const {
		return std::max(1.0f, static_cast<float>(_level * std::abs(_column / 10)));
	}
	float CostService::getDigTileTimeMultiplierCost(int _level, int _column) const {
		return std::max(1.0f, static_cast<float>(_level * std::abs(_column / 10)));
	}

}