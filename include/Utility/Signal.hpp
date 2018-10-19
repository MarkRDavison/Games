#ifndef INCLUDED_UTILITY_SIGNAL_HPP_
#define INCLUDED_UTILITY_SIGNAL_HPP_

#include <vector>
#include <algorithm>
#include <functional>

namespace inf {

	template <typename... T>
	class Signal {

	public:
		Signal(void) : m_CallbackId(0) {

		}

		void clearCallbacks(void) {
			m_CallbackId = 0;
			m_Callbacks.clear();
		}

		unsigned int getNumberOfCallbacks(void) const {
			return m_Callbacks.size();
		}

		int registerCallback(std::function<void(T...)> _callback) {
			m_Callbacks.push_back(std::make_pair(m_CallbackId, _callback));

			return m_CallbackId++;
		}

		void unregisterCallback(int _callbackId) {
			m_Callbacks.erase(
				std::remove_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const std::pair<int, std::function<void(T...)>>& _pair) {
				return _pair.first == _callbackId;
			}), m_Callbacks.end());
		}

		void invoke(T... params) {
			for (auto& p : m_Callbacks) {
				if (p.second) {
					p.second(params...);
				}
			}
		}

	private:
		std::vector<std::pair<int, std::function<void(T...)>>> m_Callbacks;
		int m_CallbackId;
	};


}

#endif // INCLUDED_UTILITY_SIGNAL_HPP_