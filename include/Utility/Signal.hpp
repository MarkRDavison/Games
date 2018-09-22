#ifndef INCLUDED_UTILITY_SIGNAL_HPP_
#define INCLUDED_UTILITY_SIGNAL_HPP_

#include <vector>
#include <algorithm>
#include <functional>

namespace inf {

	////////////////////////////////////////////////////////////
	///
	///	\brief	Class to handle callbacks and registrations
	///
	///	\tparam	The parameters of the callback
	///
	////////////////////////////////////////////////////////////
	template <typename... T>
	class Signal {

	public:
		////////////////////////////////////////////////////////////
		///
		///	\brief	Constructor
		///
		////////////////////////////////////////////////////////////
		Signal(void) : m_CallbackId(0) {

		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Clears all callbacks
		///
		////////////////////////////////////////////////////////////
		void clearCallbacks(void) {
			m_CallbackId = 0;
			m_Callbacks.clear();
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Gets the number of registered callbacks
		///
		////////////////////////////////////////////////////////////
		unsigned int getNumberOfCallbacks(void) const {
			return m_Callbacks.size();
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Registers a callback
		///
		///	\param	The callback to register
		///
		///	\return	The id the callback is registered under
		///
		////////////////////////////////////////////////////////////
		int registerCallback(std::function<void(T...)> _callback) {
			m_Callbacks.push_back(std::make_pair(m_CallbackId, _callback));

			return m_CallbackId++;
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Unregister a callback
		///
		///	\param	The callback id to unregister
		///
		////////////////////////////////////////////////////////////
		void unregisterCallback(int _callbackId) {
			m_Callbacks.erase(
				std::remove_if(m_Callbacks.begin(), m_Callbacks.end(), [&](const std::pair<int, std::function<void(T...)>>& _pair) {
				return _pair.first == _callbackId;
			}), m_Callbacks.end());
		}

		////////////////////////////////////////////////////////////
		///
		///	\brief	Invoke the callback
		///
		///	\tparam	The parameters to invoke with
		///
		////////////////////////////////////////////////////////////
		void invoke(T... params) {
			for (auto& p : m_Callbacks) {
				if (p.second) {
					p.second(params...);
				}
			}
		}

	private:
		std::vector<std::pair<int, std::function<void(T...)>>> m_Callbacks;		///<	The callbacks
		int m_CallbackId;														///<	The next callback id
	};
}

#endif // INCLUDED_UTILITY_SIGNAL_HPP_