#ifndef INCLUDED_DRILLER_SERVICES_INTERFACES_I_COST_SERVICE_HPP_
#define INCLUDED_DRILLER_SERVICES_INTERFACES_I_COST_SERVICE_HPP_

namespace drl {
	
	class ICostService {
	protected:
		virtual ~ICostService(void) = 0;

	public:
		virtual int getDigShaftCost(int _level) const = 0;
		virtual float getBuildingMultiplierCost(int _level, int _column) const = 0;
		virtual float getDigTileTimeMultiplierCost(int _level, int _column) const = 0;
	};

	inline ICostService::~ICostService(void) = default;

}

#endif // INCLUDED_DRILLER_SERVICES_INTERFACES_I_COST_SERVICE_HPP_