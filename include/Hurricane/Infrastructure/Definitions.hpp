#ifndef INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace hur {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr const char BlueLaserTextureName[] = "blue_laser";
		static constexpr const char BluePlayerShip[] = "player_ship";

		static constexpr const char EnemyShipBlack1[] = "enemy_ship_black_1";
		static constexpr const char EnemyShipBlack2[] = "enemy_ship_black_2";
		static constexpr const char EnemyShipBlack3[] = "enemy_ship_black_3";
		static constexpr const char EnemyShipBlack4[] = "enemy_ship_black_4";
		static constexpr const char EnemyShipBlack5[] = "enemy_ship_black_5";

		static constexpr const char BoltBronze[] = "bolt_bronze";
		static constexpr const char BoltSilver[] = "bolt_silver";
		static constexpr const char BoltGold[] = "bolt_gold";

		static constexpr const char PillBlue[] = "pill_blue";
		static constexpr const char PillRed[] = "pill_red";
		static constexpr const char PillYellow[] = "pill_yellow";
		static constexpr const char PillGreen[] = "pill_green";

		static constexpr const char TestDropTableName[] = "TestDropTable";
		static constexpr const char BlackEnemyDropTable[] = "BlackEnemyDropTable";

		static constexpr const char StandardDamageType[] = "Standard";
		static constexpr const int& PlayerTeam = 1;
		static constexpr const int& EnemyTeam = 2;
	};

}

#endif // INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_