#ifndef INCLUDED_DRILLER_VIEWS_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_VIEW_HPP_

#include <SFML/Graphics.hpp>

namespace drl {

	class View {
	public:
		virtual ~View(void) = 0 { }

		virtual void update(float _delta) = 0;
		virtual void draw(sf::RenderTarget & _target, sf::RenderStates _states, float _alpha) const = 0;
	};
	
}

#endif // INCLUDED_DRILLER_VIEWS_VIEW_HPP_