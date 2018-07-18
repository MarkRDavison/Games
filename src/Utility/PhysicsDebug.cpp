#include <Utility/PhysicsDebug.hpp>

namespace inf {
	PhysicsDebug::PhysicsDebug(sf::RenderTarget& _target)
		: m_Target(_target) {

	}

	void PhysicsDebug::draw(const c2Poly& _poly, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::Vertex shape[C2_MAX_POLYGON_VERTS];

		for (int i = 0; i < _poly.count; i++) {
			shape[i] = sf::Vertex(sf::Vector2f(_poly.verts[i].x, _poly.verts[i].y), _color);
		}
		// Connect last and first vertex
		shape[_poly.count] = sf::Vertex(sf::Vector2f(_poly.verts[0].x, _poly.verts[0].y), _color);

		m_Target.draw(shape, _poly.count + 1, sf::LineStrip, _states);
	}

	void PhysicsDebug::draw(const c2Circle& _body, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::CircleShape shape(_body.r);

		shape.setOrigin(_body.r, _body.r);
		shape.setPosition(_body.p.x, _body.p.y);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(_color);
		shape.setOutlineThickness(1.0f);

		m_Target.draw(shape, _states);
	}

	void PhysicsDebug::draw(const c2AABB& _aabb, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::RectangleShape shape(sf::Vector2f(_aabb.max.x - _aabb.min.x, _aabb.max.y - _aabb.min.y));

		shape.setPosition(_aabb.min.x, _aabb.min.y);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(_color);
		shape.setOutlineThickness(1.0f);

		m_Target.draw(shape, _states);
	}

	void PhysicsDebug::draw(const c2Ray& _ray, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::Vertex shape[] = {
			sf::Vertex(sf::Vector2f(_ray.p.x, _ray.p.y), _color),
			sf::Vertex(sf::Vector2f(_ray.p.x + (_ray.d.x * _ray.t), _ray.p.y + (_ray.d.y * _ray.t)), _color)
		};

		m_Target.draw(shape, 2, sf::Lines, _states);
	}

	void PhysicsDebug::draw(const c2Capsule& _capsule, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::CircleShape circle(_capsule.r);
		circle.setOrigin(_capsule.r, _capsule.r);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineColor(_color);
		circle.setOutlineThickness(1.0f);

		sf::Vertex topLine[] = {
			sf::Vertex(sf::Vector2f(_capsule.a.x, _capsule.a.y + _capsule.r), _color),
			sf::Vertex(sf::Vector2f(_capsule.b.x, _capsule.b.y + _capsule.r), _color)
		};

		sf::Vertex bottomLine[] = {
			sf::Vertex(sf::Vector2f(_capsule.a.x, _capsule.a.y - _capsule.r), _color),
			sf::Vertex(sf::Vector2f(_capsule.b.x, _capsule.b.y - _capsule.r), _color)
		};

		circle.setPosition(_capsule.a.x, _capsule.a.y);
		m_Target.draw(circle, _states);
		circle.setPosition(_capsule.b.x, _capsule.b.y);
		m_Target.draw(circle, _states);

		m_Target.draw(topLine, 2, sf::Lines, _states);
		m_Target.draw(bottomLine, 2, sf::Lines, _states);
	}

	void PhysicsDebug::draw(const c2v& _point1, const c2v& _point2, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::Vertex shape[] = {
			sf::Vertex(sf::Vector2f(_point1.x, _point1.y), _color),
			sf::Vertex(sf::Vector2f(_point2.x, _point2.y), _color)
		};

		m_Target.draw(shape, 2, sf::Lines, _states);
	}

	void PhysicsDebug::draw(const c2v& _point, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		sf::Vertex shape[] = {
			sf::Vertex(sf::Vector2f(_point.x, _point.y), _color)
		};

		m_Target.draw(shape, 1, sf::Points, _states);
	}

	void PhysicsDebug::draw(const c2Manifold& _manifold, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		for (int i = 0; i < _manifold.count; ++i) {
			c2v n = _manifold.normal;
			c2v p = _manifold.contact_points[i];
			float d = _manifold.depths[i];
			n = c2Mulvs(n, d);

			draw(p, c2Add(p, n));
			draw(p, sf::Color::Red, _states);
		}
	}

	void PhysicsDebug::draw(const c2Raycast& _cast, const c2Ray& _ray, sf::Color _color /*= sf::Color::White*/, sf::RenderStates _states /*= sf::RenderStates::Default*/) const {
		if (_cast.t > 0) {
			const c2v impact = c2Impact(_ray, _cast.t);

			draw(impact, c2Add(impact, c2Mulvs(_cast.n, 10)));
			draw(impact, sf::Color::Red, _states);
		}
	}
}
