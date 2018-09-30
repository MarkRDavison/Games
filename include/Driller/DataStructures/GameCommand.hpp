#ifndef INCLUDED_DRILLER_DATA_STRUCTURES_GAME_COMMAND_HPP_
#define INCLUDED_DRILLER_DATA_STRUCTURES_GAME_COMMAND_HPP_

#include <Utility/Hash.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace drl {

	struct GameCommand {
		
		struct PlaceBuildingEvent {
			PlaceBuildingEvent(void){}
			PlaceBuildingEvent(const std::string& _prototypeName, int _level, int _column) :
				PlaceBuildingEvent(_prototypeName.c_str(), _level, _column) { }
			PlaceBuildingEvent(const char *_prototypeName, int _level, int _column) :
				prototypeId(inf::djb_hash(_prototypeName)),
				level(_level),
				column(_column) { }
			std::size_t prototypeId{0u};
			int level{ 0 };
			int column{ 0 };
		};

		struct DigTileEvent {
			int level{ 0 };
			int column{ 0 };
		};

		struct DigShaftEvent {
			int level{0};
		};

		struct AdjustResourceEvent {
			AdjustResourceEvent(void) {}
			AdjustResourceEvent(const std::string& _resource, int _amount) :
				AdjustResourceEvent(_resource.c_str(), _amount) { }
			AdjustResourceEvent(const char *_resource, int _amount) :
				resourceId(inf::djb_hash(_resource)),
				amount(_amount) { }
			std::size_t resourceId{ 0u };
			int amount{ 0 };
		};

		struct CreateJobEvent {
			CreateJobEvent(void) {}
			CreateJobEvent(const std::string& _jobType, const sf::Vector2i& _coordinates, const sf::Vector2i& _bounds, const sf::Vector2f& _performOffset) :
				CreateJobEvent(_jobType.c_str(), _coordinates, _bounds, _performOffset) {}
			CreateJobEvent(const char *_jobType, const sf::Vector2i& _coordinates, const sf::Vector2i& _bounds, const sf::Vector2f& _performOffset) :
				jobTypeId(inf::djb_hash(_jobType)), coordinates(_coordinates), bounds(_bounds), jobPerformOffset(_performOffset) {}
				
			std::size_t jobTypeId{ 0u };
			sf::Vector2i coordinates;		// Top Left
			sf::Vector2i bounds;			// bounds the job encompasses, i.e. if placing building over multiple tiles it reserves those tiles
			sf::Vector2f jobPerformOffset;	// The offset to perform the job from, i.e. outside the tile for digging, inside for repairing etc
		};

		struct ResetJobAllocationsEvent {
			
		};

		enum EventType {
			PlaceBuilding,
			DigTile,
			DigShaft,
			AdjustResouce,
			CreateJob,
			ResetJobAllocations,

			Count
		} type;

		union {
			PlaceBuildingEvent placeBuilding;
			DigTileEvent digTile;
			DigShaftEvent digShaft;
			AdjustResourceEvent adjustResource;
			CreateJobEvent createJob;
			ResetJobAllocationsEvent resetJobAllocations;
		};


		explicit GameCommand(const PlaceBuildingEvent& _placeBuilding) :
			type(EventType::PlaceBuilding),
			placeBuilding(_placeBuilding) {
			
		}

		explicit GameCommand(const DigTileEvent& _digTile) :
			type(EventType::DigTile),
			digTile(_digTile) {
			
		}

		explicit GameCommand(const DigShaftEvent& _digShaft) :
			type(EventType::DigShaft),
			digShaft(_digShaft) {
			
		}

		explicit GameCommand(const AdjustResourceEvent& _adjustResource) :
			type(EventType::AdjustResouce),
			adjustResource(_adjustResource) {			
		}

		explicit  GameCommand(const CreateJobEvent& _createJob) :
			type(EventType::CreateJob),
			createJob(_createJob) {

		}

		explicit  GameCommand(const ResetJobAllocationsEvent& _resetJobAllocations) :
			type(EventType::ResetJobAllocations),
			resetJobAllocations(_resetJobAllocations) {

		}
	};

}

#endif // INCLUDED_DRILLER_DATA_STRUCTURES_GAME_COMMAND_HPP_