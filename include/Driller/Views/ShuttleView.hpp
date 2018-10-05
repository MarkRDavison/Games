#ifndef INCLUDED_DRILLER_VIEWS_SHUTTLE_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_SHUTTLE_VIEW_HPP_

#include <Driller/Views/View.hpp>
#include <Driller/DataStructures/ShuttleData.hpp>

namespace drl {
	
	class ShuttleView : public View {
	public:
		explicit ShuttleView(const ShuttleData& _shuttleData);
		~ShuttleView(void) override;
		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		const ShuttleData& m_ShuttleData;
	};

}

#endif // INCLUDED_DRILLER_VIEWS_SHUTTLE_VIEW_HPP_