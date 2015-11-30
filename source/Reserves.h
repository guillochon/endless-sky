/* Reserves.h
 Copyright (c) 2014 by Michael Zahniser
 
 Endless Sky is free software: you can redistribute it and/or modify it under the
 terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or (at your option) any later version.
 
 Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 */

#ifndef RESERVES_H_
#define RESERVES_H_

#include <map>
#include <set>
#include <string>

class Planet;
class PlayerInfo;
class Ship;
class System;



// This class represents the current state of relationships between governments
// in the game, and in particular the relationship of each government to the
// player. The player has a reputation with each government, which is affected
// by what they do for a government or its allies or enemies.
class Reserves {
public:
	// Reset to the initial political state defined in the game data.
	void Reset();
	
	// Get or set your reputation with the given government.
	int64_t Amounts(const System *sys, const std::string &commodity) const;
	int64_t RecentActivity(const System *sys, const std::string &commodity) const;
	void AdjustAmounts(const System *sys, const std::string &commodity, int64_t adjustment, bool recent);
	void SetAmounts(const System *sys, const std::string &commodity, int64_t adjustment, int64_t recent);
	void ReduceRecent(const System *sys, const std::string &commodity);
	
	void EvolveDaily();
	
private:
	// attitude[target][other] stores how much an action toward the given target
	// government will affect your reputation with the given other government.
	// The relationships need not be perfectly symmetrical. For example, just
	// because Republic ships will help a merchant under attack does not mean
	// that merchants will come to the aid of Republic ships.
	std::map<const System *, std::map<std::string, int64_t>> amounts;
	std::map<const System *, std::map<std::string, int64_t>> recentActivity;
};



#endif
