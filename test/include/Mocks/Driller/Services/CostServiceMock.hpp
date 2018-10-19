#ifndef INCLUDED_MOCKS_DRILLER_SERVICES_COST_SERVICE_MOCK_HPP_
#define INCLUDED_MOCKS_DRILLER_SERVICES_COST_SERVICE_MOCK_HPP_

#include <Driller/Services/Interfaces/ICostService.hpp>
#include <Utility/TestSignal.hpp>

namespace drl {
	
	class CostServiceMock : public ICostService {
	public:
		~CostServiceMock(void) override {}

		int getDigShaftCost(int _level) const override {
			return getDigShaftCostCallback(_level);
		}
		float getBuildingMultiplierCost(int _level, int _column) const override {
			return getBuildingMultiplierCostCallback(_level, _column);
		}
		float getDigTileTimeMultiplierCost(int _level, int _column) const override {
			return getDigTileTimeMultiplierCostCallback(_level, _column);
		}

		inf::TestSignal<int, int> getDigShaftCostCallback;
		inf::TestSignal<float, int, int> getBuildingMultiplierCostCallback;
		inf::TestSignal<float, int, int> getDigTileTimeMultiplierCostCallback;
	};

}

#endif // INCLUDED_MOCKS_DRILLER_SERVICES_COST_SERVICE_MOCK_HPP_