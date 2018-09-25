#ifndef INCLUDED_EXPEDITION_UTILITY_VECTOR_MATH_HPP
#define INCLUDED_EXPEDITION_UTILITY_VECTOR_MATH_HPP


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>


namespace inf {

	namespace VectorMath {

		static const constexpr float Pi = 3.14159265f;

		enum class AngleType {
			Radians,
			Degrees
		};

		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the distance between two sf::Vector2's
		///
		/// \param  _vec1    sf::Vector2 object
		///
		/// \param  _vec2   sf::Vector2 object
		///
		/// \return T distance between \a _vec1 and \a _vec2
		///
		////////////////////////////////////////////////////////////
		float distance(const sf::Vector2f& _vec1, const sf::Vector2f& _vec2);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the distance between two Vector3's
		///
		/// \param  _vec1    Vector3 object
		///
		/// \param  _vec2   Vector3 object
		///
		/// \return T distance between \a _vec1 and \a _vec2
		///
		////////////////////////////////////////////////////////////
		float distance(const sf::Vector3f& _vec1, const sf::Vector3f& _vec2);


		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the length of a sf::Vector2
		///
		/// \param  _vec    sf::Vector2 object
		///
		/// \return T length of sf::Vector2
		///
		////////////////////////////////////////////////////////////
		float length(const sf::Vector2f& _vec);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the length of a Vector3
		///
		/// \param  _vec    Vector3 object
		///
		/// \return T length of Vector3
		///
		////////////////////////////////////////////////////////////
		float length(const sf::Vector3f& _vec);


		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the length squared of a sf::Vector2
		///
		/// \param  _vec    sf::Vector2 object
		///
		/// \return T length squared of sf::Vector2
		///
		////////////////////////////////////////////////////////////
		float lengthSquared(const sf::Vector2f& _vec);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Returns the length squared of a Vector3
		///
		/// \param  _vec    Vector3 object
		///
		/// \return T length squared of Vector3
		///
		////////////////////////////////////////////////////////////
		float lengthSquared(const sf::Vector3f& _vec);


		////////////////////////////////////////////////////////////
		///
		///	\brief  Normalises the given sf::Vector2
		///
		/// \param  _vec    sf::Vector2 object
		///
		/// \return sf::Vector2 reference to \a _vec which has been normalised
		///
		////////////////////////////////////////////////////////////
		sf::Vector2f& normalise(sf::Vector2f& _vec);
		sf::Vector2f normalise(const sf::Vector2f& _vec);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Normalises the given Vector3
		///
		/// \param  _vec    Vector3 object
		///
		/// \return Vector3 reference to \a _vec which has been normalised
		///
		////////////////////////////////////////////////////////////
		sf::Vector3f& normalise(sf::Vector3f& _vec);


		////////////////////////////////////////////////////////////
		///
		///	\brief  Generates the cross product of 2 Vector3's
		///
		/// \param  _left   Vector3 object
		///
		/// \param  _right  Vector3 object
		///
		/// \return Vector3 representing cross product of \a _left
		///         and \a _right
		///
		////////////////////////////////////////////////////////////
		sf::Vector3f cross(const sf::Vector3f& _left, const sf::Vector3f& _right);


		////////////////////////////////////////////////////////////
		///
		///	\brief  Generates the dot product of 2 sf::Vector2's
		///
		/// \param  _left   sf::Vector2 object
		///
		/// \param  _right  sf::Vector2 object
		///
		/// \return T representing dot product of \a _left and \a _right
		///
		////////////////////////////////////////////////////////////
		float dot(const sf::Vector2f& _left, const sf::Vector2f& _right);

		////////////////////////////////////////////////////////////
		///
		///	\brief  Generates the dot product of 2 Vector3's
		///
		/// \param  _left   Vector3 object
		///
		/// \param  _right  Vector3 object
		///
		/// \return T representing dot product of \a _left and \a _right
		///
		////////////////////////////////////////////////////////////
		float dot(const sf::Vector3f& _left, const sf::Vector3f& _right);

		float toAngle(const sf::Vector2f& _vec, AngleType _type);

		sf::Vector2f toDirection(float _angle, AngleType _type);
	}
}


#endif //~ INCLUDED_EXPEDITION_UTILITY_VECTOR_MATH_HPP