// ******************************************
// * Baah Box Arduino : Sensor BTLE gateway *
// ******************************************

// Copyright (C) 2017 – 2019 Orange SA

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

#include "scheduler.hpp"
#include <arduino.h>

//*********************************************
//*
//*       Constructor
//*
//*********************************************
Scheduler::Scheduler(unsigned long loopTimestamp, unsigned long refreshDelay)
{
  this->loopTimestamp = loopTimestamp;
  this->refreshDelay = refreshDelay;
}

//*********************************************
//*
//*       Constructor
//*
//*********************************************
Scheduler::Scheduler()
{
}

//*********************************************
//*
//*       needToBeExecuted
//*
//*********************************************
bool Scheduler::needToBeExecuted(void)
{
  displayLoopDelay = millis() - loopTimestamp;

  if (displayLoopDelay >= refreshDelay)
  {
    loopTimestamp = millis();
    return true;
  }
  return false;
}
