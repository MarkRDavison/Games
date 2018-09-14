level = {
	name = "Level1",
	width = 16,
	height = 8,
	tiles = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 8, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 7 },
		{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	},
	waves = {
		{ time = 3.0, amount = 1,  interval = 0.0, interval_range = 0.0, entity_prototype = "entity1", },
		{ time = 1.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity1", },
		{ time = 1.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity2", },
		{ time = 1.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity3", },
		{ time = 2.0, amount = 20, interval = 0.1, interval_range = 0.2, entity_prototype = "entity1", },
		{ time = 5.0, amount = 30, interval = 0.2, interval_range = 0.1, entity_prototype = "entity3", },
	}
}