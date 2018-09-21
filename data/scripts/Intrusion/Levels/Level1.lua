level = {
	name = "Level1",
	width = 16,
	height = 10,
	tiles = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 7 },
		{ 8, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	},
	waves = {
		{ time = 2.0, amount = 1,  interval = 0.0, interval_range = 0.0, entity_prototype = "entity1", wave_index = 0 },
		{ time = 2.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity1", wave_index = 1 },
		{ time = 2.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity2", wave_index = 2 },
		{ time = 2.0, amount = 10, interval = 1.0, interval_range = 0.0, entity_prototype = "entity3", wave_index = 3 },
		{ time = 2.0, amount = 20, interval = 0.1, interval_range = 0.2, entity_prototype = "entity1", wave_index = 4 },
		{ time = 2.0, amount = 30, interval = 0.2, interval_range = 0.1, entity_prototype = "entity3", wave_index = 5 },
		{ time = 2.0, amount = 40, interval = 1.0, interval_range = 0.0, entity_prototype = "entity2", wave_index = 6 },
		{ time = 2.5, amount = 40, interval = 1.0, interval_range = 0.0, entity_prototype = "entity1", wave_index = 6 },
		{ time = 2.0, amount = 20, interval = 0.4, interval_range = 0.2, entity_prototype = "entity1", wave_index = 7 },
		{ time = 2.0, amount = 30, interval = 0.4, interval_range = 0.1, entity_prototype = "entity3", wave_index = 7 },
	}
}