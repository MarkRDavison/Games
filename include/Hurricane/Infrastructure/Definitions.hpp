#ifndef INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_
#define INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_

namespace hur {
	
	class Definitions {
	public:
		Definitions(void) = delete;
		~Definitions(void) = delete;

		static constexpr char *BlueLaserTextureName{ "blue_laser" };
		static constexpr char *BluePlayerShip{ "player_ship" };

		static constexpr char *EnemyShipBlack1{ "enemy_ship_black_1" };
		static constexpr char *EnemyShipBlack2{ "enemy_ship_black_2" };
		static constexpr char *EnemyShipBlack3{ "enemy_ship_black_3" };
		static constexpr char *EnemyShipBlack4{ "enemy_ship_black_4" };
		static constexpr char *EnemyShipBlack5{ "enemy_ship_black_5" };

		static constexpr char *BoltBronze{ "bolt_bronze" };
		static constexpr char *BoltSilver{ "bolt_silver" };
		static constexpr char *BoltGold{ "bolt_gold" };

		static constexpr char *PillBlue{ "pill_blue" };
		static constexpr char *PillRed{ "pill_red" };
		static constexpr char *PillYellow{ "pill_yellow" };
		static constexpr char *PillGreen{ "pill_green" };

		static constexpr char *TestDropTableName{ "TestDropTable" };
		static constexpr char *BlackEnemyDropTable{ "BlackEnemyDropTable" };

		static constexpr char *StandardDamageType{ "Standard" };
		static constexpr int PlayerTeam{ 1 };
		static constexpr int EnemyTeam{ 2 };
	};

}

#endif // INCLUDED_HURRICANE_INFRASTRUCTURE_DEFINITIONS_HPP_