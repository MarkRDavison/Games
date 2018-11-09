#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <Driller/Services/ResearchService.hpp>
#include <Driller/Infrastructure/Definitions.hpp>
#include <Driller/DataStructures/ResearchData.hpp>

namespace drl {
	namespace ResearchServiceTests {

		struct Package {

			Package() :
				service(data) {

			}

			ResearchData data;
			ResearchService service;

		};

		TEST_CASE("registerResearchCategory creates new category", "[Driller][Services][ResearchServiceTests]") {
			Package package{};
			
			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);

			REQUIRE(1 == package.data.categories.size());
		}
		
		TEST_CASE("registerResearchInstasnce creates new instance in the given category", "[Driller][Services][ResearchServiceTests]") {
			Package package{};
			
			ResearchInstance instance{};
			instance.level = 55;

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			package.service.registerResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed, instance);

			REQUIRE(1 == package.data.categories[0].instances.size());
			REQUIRE(instance.level == package.data.categories[0].instances[0].level);
		}

		TEST_CASE("isResearchOutstanding returns false when the category is not registered", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			REQUIRE_FALSE(package.service.isResearchOutstanding(Definitions::ResearchCategory_WorkerMovementSpeed));
		}

		TEST_CASE("isResearchOutstanding returns false when the category is registered but no instances are", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);

			REQUIRE_FALSE(package.service.isResearchOutstanding(Definitions::ResearchCategory_WorkerMovementSpeed));
		}

		TEST_CASE("isResearchOutstanding returns true when the category is registered and an instance is", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			package.service.registerResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed, {});

			REQUIRE(package.service.isResearchOutstanding(Definitions::ResearchCategory_WorkerMovementSpeed));
		}

		TEST_CASE("getOutstandingResearchInstance returns the registered instance if it is the only one", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			ResearchInstance& instance = package.data.categories[0].instances.emplace_back();

			REQUIRE(&instance == &package.service.getOutstandingResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed));
		}

		TEST_CASE("getOutstandingResearchInstance returns thefirst registered instance if there are multiple", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			package.data.categories[0].instances.emplace_back();
			package.data.categories[0].instances.emplace_back();
			package.data.categories[0].instances.emplace_back();
			package.data.categories[0].instances.emplace_back();

			const ResearchInstance& instance = package.data.categories[0].instances.front();

			REQUIRE(&instance == &package.service.getOutstandingResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed));
		}

		TEST_CASE("research removes the instance", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			package.service.registerResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed, {});

			package.service.research(Definitions::ResearchCategory_WorkerMovementSpeed);

			REQUIRE(package.data.categories[0].instances.empty());
		}

		TEST_CASE("research removes only one instance", "[Driller][Services][ResearchServiceTests]") {
			Package package{};

			package.service.registerResearchCategory(Definitions::ResearchCategory_WorkerMovementSpeed);
			package.service.registerResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed, {});
			package.service.registerResearchInstance(Definitions::ResearchCategory_WorkerMovementSpeed, {});

			package.service.research(Definitions::ResearchCategory_WorkerMovementSpeed);

			REQUIRE(1 == package.data.categories[0].instances.size());
		}

		// Research Categories
		//	-	Modify resource from ResourceService
		//		-	Max width/depth
		//	-	Modify multiplier
		//	-	Modify base stat?
		//	-	Increase prototype stat?

		// TODO: Actual Research
		// Unlock building
		//	-	Refinery
		//	-	Non-crucial need
		// Decrease base work time 
		//	-	Building buildings
		//	-	Working buildings
		//	-	Digging tiles
		// Increase number of workers per building
		//	-	Bunks ( 1 -> 2 -> 3 -> 4)
		//	-	Refiner (1 -> 2)
		//	-	Research (1 -> 2 -> 3)
		// Improve worker speed
		// Improve max allowed depth
		// Improve max allowed width
		// Improve shuttle 
		// Improve need retention rate
		// Improve building reliability
	}
}
