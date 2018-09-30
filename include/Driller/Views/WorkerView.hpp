#ifndef INCLUDED_DRILLER_VIEWS_WORKER_VIEW_HPP_
#define INCLUDED_DRILLER_VIEWS_WORKER_VIEW_HPP_

#include <Driller/Views/View.hpp>
#include <Driller/DataStructures/WorkerData.hpp>

namespace drl {
	
	class WorkerView : public View {
	public:
		WorkerView(const WorkerData& _workerData);
		~WorkerView(void) override;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states, float _alpha) const override;

	private:
		const WorkerData& m_WorkerData;
	};

}

#endif // INCLUDED_DRILLER_VIEWS_WORKER_VIEW_HPP_