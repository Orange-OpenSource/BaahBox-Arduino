// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2023 Orange SA

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef __scheduler_hpp
#define __scheduler_hpp

class Scheduler
{
public:
  Scheduler(unsigned long loopTimestamp, unsigned long refreshDelay);
  Scheduler();
  bool needToBeExecuted(void);

private:
  unsigned long displayLoopDelay;
  unsigned long loopTimestamp;
  unsigned long refreshDelay;
};

#endif /* __scheduler_hpp */