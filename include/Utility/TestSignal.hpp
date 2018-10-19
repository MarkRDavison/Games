#ifndef INCLUDED_UTILITY_TEST_SIGNAL_HPP_
#define INCLUDED_UTILITY_TEST_SIGNAL_HPP_

#include <functional>

namespace inf {

	template <typename T, typename... U>
	class TestSignal {
	public:

		bool isInvoked(void) const noexcept { return m_InvokeCount > 0; }
		bool isInvokedOnce(void) const noexcept { return m_InvokeCount == 1; }
		bool isInvokedExactly(unsigned _number) const noexcept { return m_InvokeCount == _number; }
		
		T invoke(U... _params) const {
			m_InvokeCount++;

			if (m_Callback) {
				return m_Callback(_params...);
			}

			throw std::runtime_error("callback has not been registered");
		}

		void registerCallback(std::function<T(U...)> _callback) {
			m_Callback = _callback;
		}

		T operator() (U... _params) {
			return invoke(_params...);
		}

		T operator() (U... _params) const{
			return invoke(_params...);
		}

	private:
		mutable unsigned m_InvokeCount{ 0 };
		std::function<T(U...)> m_Callback;
	};

}

#endif // INCLUDED_UTILITY_TEST_SIGNAL_HPP_