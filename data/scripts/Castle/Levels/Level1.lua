level = {
	name = "Level 1",
	width = 23,
	height = 13,
	tiles = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	},
	entities = {
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 1,  y = 9 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 2,  y = 9 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 2,  y = 3 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 5,  y = 8 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 6,  y = 8 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 5,  y = 5 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 6,  y = 5 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 9,  y = 7 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 10, y = 7 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 17, y = 3 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 18, y = 3 } },
		{ prototype = "coin", size = { x = 1.0, y = 1.0 },   coordinates = { x = 21, y = 7 } },

		{ prototype = "ladder", size = { x = 1.0, y = 3.0 }, coordinates = { x = 4, y = 11 } },
		
		{ prototype = "flame", size = { x = 1.0, y = 1.0 },  coordinates = { x = 3,  y = 4 }, flip = { x = false, y = false } },
		{ prototype = "flame", size = { x = 1.0, y = 1.0 },  coordinates = { x = 7,  y = 6 }, flip = { x = false, y = false } },
		{ prototype = "flame", size = { x = 1.0, y = 1.0 },  coordinates = { x = 21, y = 8 }, flip = { x = false, y = false } },

		{ prototype = "level_transition", size = { x = 1.0, y = 2.0 }, coordinates = { x = 21,  y = 11 }, target_level = "Level 2", target_coordinates = { x = 1.0, y = 6.0 }, color = { r = 255, g = 125, b = 0 }, },
		
		{ 
		  prototype = "moving_platform", 
		  impacts_movement = true,
		  effected_by_gravity = false,
		  can_be_moved_by_others = false,
		  can_move_others = true,
		  is_one_way = true,
		  size = { x = 1, y = 1 }, 
		  coordinates = { x = 12, y = 8 }, 
		  color = { r = 255, g = 125, b = 0 },
		  waypoints = { 
		    { x = 12,  y = 8, speed = 1.0 }, 
		    { x = 14,  y = 8, speed = 1.0 }, 
		    { x = 14,  y = 4, speed = 1.0 }, 
			{ x = 12,  y = 4, speed = 1.0 } 
		  }
		},
		{ 
		  prototype = "moving_platform", 
		  impacts_movement = true,
		  effected_by_gravity = false,
		  can_be_moved_by_others = false,
		  can_move_others = true,
		  is_one_way = false,
		  size = { x = 1, y = 1 }, 
		  coordinates = { x = 12, y = 11 }, 
		  color = { r = 25, g = 125, b = 0 },
		  waypoints = { 
		    { x = 4,  y = 11, speed = 2.0 }, 
			{ x = 18,  y = 11, speed = 2.0 } 
		  }
		},
	}
}