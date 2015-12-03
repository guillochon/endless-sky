/* System.h
Copyright (c) 2014 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Point.h"
#include "Set.h"
#include "StellarObject.h"

#include <string>
#include <vector>

class DataNode;
class Date;
class Fleet;
class Government;
class Planet;



// Class representing a star system. This includes characteristics like what
// ships enter that system, what asteroids are present, who owns the system, and
// what prices the trade goods have in that system. It also includes the stellar
// objects in each system, and the hyperspace links between systems.
class System {
public:
	class Asteroid {
	public:
		Asteroid(const std::string &name, int count, double energy);
		
		const std::string &Name() const;
		int Count() const;
		double Energy() const;
		
	private:
		std::string name;
		int count;
		double energy;
	};
	
	class FleetProbability {
	public:
		FleetProbability(const Fleet *fleet, int period);
		
		const Fleet *Get() const;
		int Period() const;
		
	private:
		const Fleet *fleet;
		int period;
	};
	
	
public:
	// Load a system's description.
	void Load(const DataNode &node, Set<Planet> &planets);
	// Once the star map is fully loaded, figure out which stars are "neighbors"
	// of this one, i.e. close enough to see or to reach via jump drive.
	void UpdateNeighbors(const Set<System> &systems);
	
	// Modify a system's links.
	void Link(System *other);
	void Unlink(System *other);
	
	// Get this system's name and position (in the star map).
	const std::string &Name() const;
	const Point &Position() const;
	// Get this system's government.
	const Government *GetGovernment() const;
	
	// Get a list of systems you can travel to through hyperspace from here.
	const std::vector<const System *> &Links() const;
	// Get a list of systems you can "see" from here, whether or not there is a
	// direct hyperspace link to them. This is also the set of systems that you
	// can travel to from here via the jump drive.
	const std::vector<const System *> &Neighbors() const;
	
	// Move the stellar objects to their positions on the given date.
	void SetDate(const Date &date);
	// Get the stellar object locations on the most recently set date.
	const std::vector<StellarObject> &Objects() const;
	// Get the habitable zone's center.
	double HabitableZone() const;
	// Check if this system is inhabited.
	bool IsInhabited() const;
	// Check whether you can buy or sell ships in this system.
	bool HasShipyard() const;
	// Check whether you can buy or sell ship outfits in this system.
	bool HasOutfitter() const;
	
	// Get the specification of how many asteroids of each type there are.
	const std::vector<Asteroid> &Asteroids() const;
	
	// Get the price of the given commodity in this system.
	int Trade(const std::string &commodity, int64_t quantity = 0) const;
	
	// Get the production rate of the given commodity in this system.
	int Production(const std::string &commodity) const;
	
	// Get the consumition rate of the given commodity in this system.
	int Consumption(const std::string &commodity) const;
	
	// Get the rate of interstellar trade of a given commodity in this system.
	int Trading(const std::string &commodity) const;
	
	// Randomly destroy a large fraction of a system's commodity.
	int Disaster(const std::string &commodity) const;
	
	// Return the amount of a given commodity in this system.
	int64_t Reserves(const std::string &commodity) const;
	
	// Get the price of the given commodity in this system.
	int64_t InitialReserves(const std::string &commodity) const;
	
	// Adjust the amount of a given commodity recently transcated by the player
	// in this system.
	void AdjustReserves(const std::string &commodity, int64_t adjustment) const;
	
	// Set the amount of a given commodity recently transcated by the player
	// in this system.
	void SetReserves(const std::string &commodity, int64_t adjustment) const;
	
	// Get the probabilities of various fleets entering this system.
	const std::vector<FleetProbability> &Fleets() const;
	
	
private:
	void LoadObject(const DataNode &node, Set<Planet> &planets, int parent = -1);
	
	
private:
	// Name and position (within the star map) of this system.
	std::string name;
	Point position;
	const Government *government = nullptr;
	// Hyperspace links to other systems.
	std::vector<const System *> links;
	std::vector<const System *> neighbors;
	
	// Stellar objects, listed in such an order that an object's parents are
	// guaranteed to appear before it (so that if we traverse the vector in
	// order, updating positions, an object's parents will already be at the
	// proper position before that object is updated).
	std::vector<StellarObject> objects;
	std::vector<Asteroid> asteroids;
	std::vector<FleetProbability> fleets;
	double habitable = 1000.;
	
	// Commodity prices.
	std::map<std::string, int> trade;
};



#endif
