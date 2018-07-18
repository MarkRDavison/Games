#ifndef INCLUDED_CASTLE_COMPONENTS_TIMER_COMPONENT_HPP_
#define INCLUDED_CASTLE_COMPONENTS_TIMER_COMPONENT_HPP_

#include <EntityComponentSystem/Component.hpp>
#include <EntityComponentSystem/Entity.hpp>

#include <functional>


namespace castle {

	struct TimerComponent : ecs::Component {
		float timeRemaining;
		float time;
		std::function<void(ecs::Entity *)> elapsedCallback;

		TimerComponent(std::function<void(ecs::Entity *)> _callback, float _time, float _startingTime) :
			timeRemaining(_startingTime),
			time(_time),
			elapsedCallback(_callback) {

		}
		TimerComponent(std::function<void(ecs::Entity *)> _callback, float _time) :
			TimerComponent(_callback, _time, _time) {

		}
		TimerComponent(float _time) :
			TimerComponent(nullptr, _time) {

		}
		TimerComponent(float _time, float _startingTime) :
			TimerComponent(nullptr, _time, _startingTime) {

		}

		void update(float _delta) override {
			timeRemaining -= _delta;
			if (timeRemaining <= 0.0f) {
				if (elapsedCallback) {
					elapsedCallback(entity);
				} else {
					entity->destroy();
				}
			}
		}
	};

}

#endif // INCLUDED_CASTLE_COMPONENTS_TIMER_COMPONENT_HPP_