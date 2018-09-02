drop_tables = {
	{
		name = "TestDropTable",
		drops = {
			{
				chance = 50,
				entities = {
					"bolt_bronze"
				}
			},
			{
				chance = 25,
				entities = {
					"bolt_silver"
				}
			},
			{
				chance = 10,
				entities = {
					"bolt_gold"
				}
			}
		}
	},
	{
		name = "BlackEnemyDropTable",
		drops = {
			{
				chance = 5,
				entities = {
					"bolt_gold",
				}
			},
			{
				chance = 10,
				entities = {
					"bolt_silver"
				}
			},
			{
				chance = 20,
				entities = {
					"bolt_bronze"
				}
			},
			{
				chance = 50,
				entities = {
					"pill_red",
					"pill_blue",
					"pill_green",
				}
			},
		}
	}
}