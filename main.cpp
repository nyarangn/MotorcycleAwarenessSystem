#include "MotorcycleAwarenessSystem.hpp"
#include "MotorcycleAwarenessSystemTypes.hpp"

#ifdef MAS_DEBUG
#include <iostream>
#endif
#include <string>
#include <unistd.h>

int main( void )
{
    // Define mock signals
    TurnSignal_t* motorcycleTurnSignal = new TurnSignal_t;
    TurnSignal_t* carTurnSignal = new TurnSignal_t;
    RadarSignal_t* motorcycleRadarSignal = new RadarSignal_t;
    GpsSignal_t* motorcycleGpsSignal = new GpsSignal_t;
    GpsSignal_t* carGpsSignal = new GpsSignal_t;;

    // Instantiate the Motorcycle Awareness System (MAS) for the motorcycle
    MotorcycleAwarenessSystem MAS_motorcycle( MOTORCYCLE );
    // Initialize the car MAS
    MAS_motorcycle.Initialize( motorcycleTurnSignal, (TurnSignal_t*)NULL, motorcycleRadarSignal,
                                          motorcycleGpsSignal, carGpsSignal );

    // Instantiate the Motorcycle Awareness System (MAS) for the car
    MotorcycleAwarenessSystem MAS_car( CAR );
    // Initialize the car MAS
    MAS_car.Initialize( (TurnSignal_t*)NULL, carTurnSignal, motorcycleRadarSignal,
                                          motorcycleGpsSignal, carGpsSignal );

    // Run the MAS systems for the car & motorcycle
    while ( true )
    {
        MAS_motorcycle.MonitorConditions();
        MAS_car.MonitorConditions();
        usleep(250);

#ifdef MAS_DEBUG
        std::cout << "The MAS is running" << std::endl;
#endif
    }

    return 0;
}
