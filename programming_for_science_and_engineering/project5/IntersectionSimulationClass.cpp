//program header
//project5:
//tingjie yu
//date: 12/6/2021
//purpose of code: header file for IntersectionSimulationClass
//define IntersectionSimulationClass
//add functions to scheduleArrival
//scheduleLightChange, handleNextEvent



#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{

  if (travelDir == EAST_DIRECTION) {
  //schedule arrival in east direction 
  //add event into sorted eventlist

    int arrivalTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
    EventClass newEvent(currentTime + arrivalTime, EVENT_ARRIVE_EAST);
    eventList.insertValue(newEvent);
    cout << "Time: " << currentTime << 
    " Scheduled Event Type: East-Bound Arrival Time: " << 
    currentTime + arrivalTime << endl;

  }
  else if (travelDir == WEST_DIRECTION) {
  //schedule arrival in west direction 
  //add event into sorted eventlist

    int arrivalTime = getPositiveNormal(westArrivalMean, westArrivalStdDev);
    EventClass newEvent(currentTime + arrivalTime, EVENT_ARRIVE_WEST);
    eventList.insertValue(newEvent);
    cout << "Time: " << currentTime << 
    " Scheduled Event Type: West-Bound Arrival Time: " << 
    currentTime + arrivalTime << endl;

  }
  else if (travelDir == NORTH_DIRECTION) {
  //schedule arrival in north direction 
  //add event into sorted eventlist

    int arrivalTime = getPositiveNormal(northArrivalMean, northArrivalStdDev);
    EventClass newEvent(currentTime + arrivalTime, EVENT_ARRIVE_NORTH);
    eventList.insertValue(newEvent);
    cout << "Time: " << currentTime << 
    " Scheduled Event Type: North-Bound Arrival Time: " 
    << currentTime + arrivalTime << endl;

  }
  else if (travelDir == SOUTH_DIRECTION) {
  //schedule arrival in south direction 
  //add event into sorted eventlist

    int arrivalTime = getPositiveNormal(southArrivalMean, southArrivalStdDev);
    EventClass newEvent(currentTime + arrivalTime, EVENT_ARRIVE_SOUTH);
    eventList.insertValue(newEvent);
    cout << "Time: " << currentTime << 
    " Scheduled Event Type: South-Bound Arrival Time: " 
    << currentTime + arrivalTime << endl;

  }
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{

  if (currentLight == LIGHT_GREEN_EW) {
  //schedule light change into yellow EW
  //add event into sorted eventlist

    EventClass newEvent
    (currentTime + eastWestGreenTime, EVENT_CHANGE_YELLOW_EW);
    eventList.insertValue(newEvent);

    cout << "Time: "
    << currentTime << 
    " Scheduled Event Type: Light Change to EW Yellow Time: "
    << currentTime + eastWestGreenTime << endl;

  }
  else if(currentLight == LIGHT_YELLOW_EW) {
  //schedule light change into green NS
  //add event into sorted eventlist

    EventClass newEvent
    (currentTime + eastWestYellowTime, EVENT_CHANGE_GREEN_NS);
    eventList.insertValue(newEvent);

    cout << "Time: "
    << currentTime << 
    " Scheduled Event Type: Light Change to NS Green Time: "
    << currentTime + eastWestYellowTime << endl;

  }
  else if(currentLight == LIGHT_GREEN_NS) {
  //schedule light change into yellow NS
  //add event into sorted eventlist

    EventClass newEvent
    (currentTime + northSouthGreenTime, EVENT_CHANGE_YELLOW_NS);
    eventList.insertValue(newEvent);

    cout << "Time: "
    << currentTime << 
    " Scheduled Event Type: Light Change to NS Yellow Time: "
    << currentTime + northSouthGreenTime << endl;

  }
  else if(currentLight == LIGHT_YELLOW_NS) {
  //schedule light change into green EW
  //add event into sorted eventlist

    EventClass newEvent
    (currentTime + northSouthYellowTime, EVENT_CHANGE_GREEN_EW);
    eventList.insertValue(newEvent);

    cout << "Time: "
    << currentTime << 
    " Scheduled Event Type: Light Change to EW Green Time: "
    << currentTime + northSouthYellowTime << endl;

  }
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  EventClass curEvent;
  if (eventList.removeFront(curEvent)) {
    if (curEvent.getTimeOccurs() > timeToStopSim) {
    //handle event happens after StopSim

      cout << endl;
      cout << "Next event occurs AFTER the simulation end time (";
      printEventType(curEvent.getType());
      cout << curEvent.getTimeOccurs() << ")!"
      << endl;

      return false;

    }
    else if (curEvent.getType() == EVENT_ARRIVE_EAST) {
    //handle event for car arrives at east
      
      currentTime = curEvent.getTimeOccurs();
      CarClass newCar(EAST_DIRECTION,currentTime);  
      eastQueue.enqueue(newCar);

      //print out handling information
      //update statistics
      cout << endl 
      << "Handling " ;
      printEventType(curEvent.getType());
      cout << currentTime << endl;
      cout << "Time: " << currentTime << " Car #" 
      << newCar.getId() << " arrives east-bound - queue length: "
      << eastQueue.getNumElems() << endl;

      if (eastQueue.getNumElems() > maxEastQueueLength) {

        maxEastQueueLength = eastQueue.getNumElems();

      }

      scheduleArrival(EAST_DIRECTION);

    }
    else if (curEvent.getType() == EVENT_ARRIVE_WEST) {
    //handle event for car arrives at west

      currentTime = curEvent.getTimeOccurs();
      CarClass newCar(WEST_DIRECTION,currentTime);
      westQueue.enqueue(newCar);

      //print out handling information
      //update statistics
      cout << endl 
      << "Handling ";
      printEventType(curEvent.getType());
      cout << currentTime << endl;
      cout << "Time: " << currentTime << " Car #" 
      << newCar.getId() << " arrives west-bound - queue length: "
      << westQueue.getNumElems() << endl;


      if (westQueue.getNumElems() > maxWestQueueLength) {

        maxWestQueueLength = westQueue.getNumElems();

      }

      scheduleArrival(WEST_DIRECTION);

    }
    else if (curEvent.getType() == EVENT_ARRIVE_NORTH) {
    //handle event for car arrives at north

      currentTime = curEvent.getTimeOccurs();
      CarClass newCar(NORTH_DIRECTION,currentTime);
      northQueue.enqueue(newCar);
      
      //print out handling information
      //update statistics
      cout << endl
      << "Handling ";
      printEventType(curEvent.getType());
      cout << currentTime << endl;
      cout << "Time: " << currentTime << " Car #" 
      << newCar.getId() << " arrives north-bound - queue length: "
      << northQueue.getNumElems() << endl;


      if (northQueue.getNumElems() > maxNorthQueueLength) {

        maxNorthQueueLength = northQueue.getNumElems();

      }
      scheduleArrival(NORTH_DIRECTION);

    }
    else if (curEvent.getType() == EVENT_ARRIVE_SOUTH) {
    //handle event for car arrives at south

      currentTime = curEvent.getTimeOccurs();
      CarClass newCar(SOUTH_DIRECTION,currentTime);
      southQueue.enqueue(newCar);

      //print out handling information
      //update statistics
      cout << endl
      << "Handling " ;
      printEventType(curEvent.getType());
      cout << currentTime << endl;
      cout << "Time: " << currentTime << " Car #" 
      << newCar.getId() << " arrives south-bound - queue length: "
      << southQueue.getNumElems() << endl;

      if (southQueue.getNumElems() > maxSouthQueueLength) {

        maxSouthQueueLength = southQueue.getNumElems();

      }
      scheduleArrival(SOUTH_DIRECTION);
  
    }
    else if (curEvent.getType() == EVENT_CHANGE_YELLOW_EW) {
    //handle event for light changes into yellow EW

      cout << endl 
      << "Handling " ;
      printEventType(curEvent.getType()) ;
      cout << curEvent.getTimeOccurs() << endl;
      cout << "Advancing cars on east-west green" << endl;
      int numEastBeforeAdvance = numTotalAdvancedEast;
      int numWestBeforeAdvance = numTotalAdvancedWest;
      int contEW = 0;
      
      //handle cars from east to west
      while (contEW < eastWestGreenTime) {
  
        CarClass movedCar;
        if (eastQueue.dequeue(movedCar)) {

          numTotalAdvancedEast += 1;
          cout << "  Car #" << movedCar.getId() 
          << " advances east-bound" <<endl;

        }

        contEW = contEW + 1;

      }

      //handle cars from west to east
      contEW = 0;
      while (contEW < eastWestGreenTime) {

        CarClass movedCar;
        if (westQueue.dequeue(movedCar)) {

          numTotalAdvancedWest += 1;
          cout << "  Car #" << movedCar.getId() 
          << " advances west-bound" <<endl;

        }

        contEW = contEW + 1;

      }

      //update print information 
      cout << "East-bound cars advanced on green: " 
      << (numTotalAdvancedEast - numEastBeforeAdvance) 
      << " Remaining queue: " << eastQueue.getNumElems() << endl;

      cout << "West-bound cars advanced on green: " 
      << (numTotalAdvancedWest - numWestBeforeAdvance) 
      << " Remaining queue: " << westQueue.getNumElems() << endl; 
      
      currentLight = LIGHT_YELLOW_EW;
      currentTime = curEvent.getTimeOccurs();
      scheduleLightChange();

    }
    else if (curEvent.getType() == EVENT_CHANGE_GREEN_NS) {
    //handle event for light changes into green NS

      cout << endl 
      << "Handling " ;
      printEventType(curEvent.getType()) ;
      cout << curEvent.getTimeOccurs() << endl;
      cout << "Advancing cars on east-west yellow" << endl;
      int numEastBeforeAdvance = numTotalAdvancedEast;
      int numWestBeforeAdvance = numTotalAdvancedWest;
      int contEW = 0;

      //handle cars from east to west during yellow
      while (contEW < eastWestYellowTime) {

        CarClass movedCar;
        if (!eastQueue.getNumElems()) {

          cout << "  No east-bound cars waiting to advance on yellow" 
          << endl;
          contEW = eastWestYellowTime;

        }
        else if (getUniform(0,MAX_PERCENT) <= percentCarsAdvanceOnYellow) {

          if (eastQueue.dequeue(movedCar)) {

            cout << "  Next east-bound car will advance on yellow" << endl;
            numTotalAdvancedEast += 1;
            cout << "  Car #" << movedCar.getId() 
            << " advances east-bound" <<endl;

          }
        }
        else {

          cout << "  Next east-bound car will NOT advance on yellow" 
          << endl;
          contEW = eastWestYellowTime;

        }

        contEW = contEW + 1;

      }

      //handle cars from west to east during yellow
      contEW = 0;
      while (contEW < eastWestYellowTime) {

        if (!westQueue.getNumElems()) {

          cout << "  No west-bound cars waiting to advance on yellow" 
          << endl;
          contEW = eastWestYellowTime;

        }
        else if (getUniform(0,MAX_PERCENT) <= percentCarsAdvanceOnYellow) {

          CarClass movedCar;
          if (westQueue.dequeue(movedCar)) {

            cout << "  Next west-bound car will advance on yellow" << endl;
            numTotalAdvancedWest += 1;
            cout << "  Car #" << movedCar.getId() 
            << " advances west-bound" <<endl;

          }
        }
        else {

          cout << "  Next west-bound car will NOT advance on yellow" 
          << endl;
          contEW = eastWestYellowTime;

        }

        contEW = contEW + 1;

      }
      
      //update print information 
      cout << "East-bound cars advanced on yellow: " 
      << (numTotalAdvancedEast - numEastBeforeAdvance) 
      << " Remaining queue: " << eastQueue.getNumElems() << endl;

      cout << "West-bound cars advanced on yellow: " 
      << (numTotalAdvancedWest - numWestBeforeAdvance) 
      << " Remaining queue: " << westQueue.getNumElems() << endl; 

      currentLight = LIGHT_GREEN_NS;
      currentTime = curEvent.getTimeOccurs();
      scheduleLightChange();

    }
    else if (curEvent.getType() == EVENT_CHANGE_YELLOW_NS) {
    //handle event for light changes into yellow NS

      cout << endl 
      << "Handling ";
      printEventType(curEvent.getType());
      cout << curEvent.getTimeOccurs() << endl;
      cout << "Advancing cars on north-south green" << endl;
      int numNorthBeforeAdvance = numTotalAdvancedNorth;
      int numSouthBeforeAdvance = numTotalAdvancedSouth;
      int contNS = 0;

      //handle cars from north to south
      while (contNS < northSouthGreenTime) {

        CarClass movedCar;
        if (northQueue.dequeue(movedCar)) {

          numTotalAdvancedNorth += 1;
          cout << "  Car #" << movedCar.getId() 
          << " advances north-bound" <<endl;

        }

        contNS = contNS + 1;

      }

      //handle cars from south to north
      contNS = 0;
      while (contNS < northSouthGreenTime) {

        CarClass movedCar;
        if (southQueue.dequeue(movedCar)) {

          numTotalAdvancedSouth += 1;
          cout << "  Car #" << movedCar.getId() 
          << " advances south-bound" <<endl;

        }

        contNS = contNS + 1;

      }
 
      //print out information 
      cout << "North-bound cars advanced on green: " 
      << (numTotalAdvancedNorth - numNorthBeforeAdvance) 
      << " Remaining queue: " << northQueue.getNumElems() << endl;

      cout << "South-bound cars advanced on green: " 
      << ( numTotalAdvancedSouth - numSouthBeforeAdvance) 
      << " Remaining queue: " << southQueue.getNumElems() << endl; 
      
      currentTime = curEvent.getTimeOccurs();
      currentLight = LIGHT_YELLOW_NS;
      scheduleLightChange ();

    }
    else if (curEvent.getType() == EVENT_CHANGE_GREEN_EW) {
    //handle event for light changes into green EW

      cout << endl 
      << "Handling ";
      printEventType(curEvent.getType());
      cout << curEvent.getTimeOccurs() << endl;
      cout << "Advancing cars on north-south yellow" << endl;
      int numNorthBeforeAdvance = numTotalAdvancedNorth;
      int numSouthBeforeAdvance = numTotalAdvancedSouth;
      int contNS = 0;

      //handle cars from north to south
      while (contNS < northSouthYellowTime) {

        if (!northQueue.getNumElems()) {

          cout << "  No north-bound cars waiting to advance on yellow" 
          << endl;
          contNS = northSouthYellowTime;

        }
        else if (getUniform(0,MAX_PERCENT) <= percentCarsAdvanceOnYellow) {

          CarClass movedCar;
          if (northQueue.dequeue(movedCar)) {

            cout << "  Next north-bound car will advance on yellow" << endl;
            numTotalAdvancedNorth += 1;
            cout << "  Car #" << movedCar.getId() 
            << " advances north-bound" <<endl;

          }
        }
        else {

          cout << "  Next north-bound car will NOT advance on yellow" 
          << endl;
          contNS = northSouthYellowTime;

        }

        contNS = contNS + 1;

      }

      //handle cars from south to north
      contNS = 0;
      while (contNS < northSouthYellowTime) {

        if (!southQueue.getNumElems()) {

          cout << "  No south-bound cars waiting to advance on yellow" 
          << endl;
          contNS = northSouthYellowTime;

        }
        else if (getUniform(0,MAX_PERCENT) <= percentCarsAdvanceOnYellow) {

          CarClass movedCar;
          if (southQueue.dequeue(movedCar)) {

            cout << "  Next south-bound car will advance on yellow" << endl;
            numTotalAdvancedSouth += 1;
            cout << "  Car #" << movedCar.getId() 
            << " advances south-bound" <<endl;

          }
        }
        else {
         
          cout << "  Next south-bound car will NOT advance on yellow" << endl;
          contNS = northSouthYellowTime;

        }

       contNS = contNS + 1;

      }

      //print out information 
      cout << "North-bound cars advanced on yellow: " 
      << (numTotalAdvancedNorth - numNorthBeforeAdvance) 
      << " Remaining queue: " << northQueue.getNumElems() << endl;

      cout << "South-bound cars advanced on yellow: " 
      << (numTotalAdvancedSouth - numSouthBeforeAdvance) 
      << " Remaining queue: " << southQueue.getNumElems() << endl; 

      currentLight = LIGHT_GREEN_EW;
      currentTime = curEvent.getTimeOccurs();
      scheduleLightChange ();

    }
    return true;
  }
  else {
    return false;
  }
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}

//to avoid duplicate code by put print event type together 
void IntersectionSimulationClass :: printEventType ( 
     const int EventType 
     ) 
{
  if (EventType == EVENT_ARRIVE_EAST) {

    cout << "Event Type: East-Bound Arrival Time: ";

  }
  else if (EventType == EVENT_ARRIVE_WEST) {

    cout << "Event Type: West-Bound Arrival Time: ";

  }
  else if (EventType == EVENT_ARRIVE_NORTH) {

    cout << "Event Type: North-Bound Arrival Time: ";

  }
  else if (EventType == EVENT_ARRIVE_SOUTH) {

    cout << "Event Type: South-Bound Arrival Time: ";

  }
  else if (EventType == EVENT_CHANGE_GREEN_EW) {

    cout << "Event Type: Light Change to EW Green Time: ";

  }
  else if (EventType == EVENT_CHANGE_YELLOW_EW) {

    cout << "Event Type: Light Change to EW Yellow Time: ";

  }
  else if (EventType == EVENT_CHANGE_GREEN_NS) {

    cout << "Event Type: Light Change to NS Green Time: ";

  }
  else if (EventType == EVENT_CHANGE_YELLOW_NS) {

    cout << "Event Type: Light Change to NS Yellow Time: ";

  }
}
