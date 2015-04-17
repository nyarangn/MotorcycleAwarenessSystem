/////////////////////////////////////////////////////////////////////////
/// Class definition for the Motorcycle Awareness System (MAS).
/// This class processes various signals and interactions to
/// realize the MAS
/////////////////////////////////////////////////////////////////////////
#include "MotorcycleAwarenessSystem.hpp"
#include "MotorcycleAwarenessSystemTypes.hpp"

#include <list>
#include <map>

/// Constructor
MotorcycleAwarenessSystem::MotorcycleAwarenessSystem( VehicleType vehicleType )
    :vehicleType( vehicleType )
{
    // Do nothing
}

/// Destructor
MotorcycleAwarenessSystem::~MotorcycleAwarenessSystem( void )
{
    // Do nothing
}

/// Method to initialize the MAS system
void MotorcycleAwarenessSystem::Initialize( CanSignal_t* motorcycleCanSignal, CanSignal_t* carCanSignal,
                                            RadarSignal_t* motorcycleRadarSignal, GpsSignal_t* motorcycleGpsSignal,
                                            GpsSignal_t* carGpsSignal  )
{
    // Initialize the motorcycle radar signal
    this->motorcycleRadarSignal = motorcycleRadarSignal;

    // Initialize the canSignal map
    canSignal[MOTORCYCLE] = motorcycleCanSignal;
    canSignal[CAR] = carCanSignal;

    // Initialize the GPS signals
    this->motorcycleGpsSignal = motorcycleGpsSignal;
    this->motorcycleGpsSignal = motorcycleGpsSignal;
}

/// Method to continuously monitor the conditions during run-time
void MotorcycleAwarenessSystem::MonitorConditions( void )
{
    if ( MOTORCYCLE == vehicleType )
    {
        // Track the motorcycle
        TrackMotorcycle();
        // Check for hazards
        if ( IsHazardPresent() == true )
        {
            // Warm the motorcycle operator
            RelayWarningToOperator();
        }
    }
    // vehicleType == CAR
    else
    {
        // Check for hazards
        if ( (IsVehicleBlinkerOn() == true) && (IsMotorcycleInRange() == true) )
        {
            // Relay message to the car driver
            RelayWarningToOperator();
        }
    }
}

/// Method to determine whether the car's blinker is ON
bool MotorcycleAwarenessSystem::IsVehicleBlinkerOn( void )
{
    return (this->canSignal[vehicleType])->isBlinkerOn;
}

/// Method to determine whether the motorcycle is within the car's range
bool MotorcycleAwarenessSystem::IsMotorcycleInRange( void )
{
    bool isInRange = false;

    // Determine where the motorcycle is relative to the car using the GPS signals
    if ( ((abs( this->carGpsSignal->x ) + DANGER_ZONE) >= abs( this->motorcycleGpsSignal->x )) ||
         ((abs( this->carGpsSignal->y ) + DANGER_ZONE) >= abs( this->motorcycleGpsSignal->y )))
    {
        isInRange = true;
    }
    else
    {
        // Analyze the V2V data for a threat
        MotorCycleLocation_t motorCycleLocation = GetMotorcycleLocation();
        /// @todo Process the data packet and determine threat
    }

    return isInRange;
}

/// Method to determine whether a hazard is within the danger zone of the motorcycle
bool MotorcycleAwarenessSystem::IsHazardPresent( void )
{
    bool isHazardPresent = false;

    if ( abs( this->motorcycleRadarSignal->distance ) >= DANGER_ZONE )
    {
        isHazardPresent = true;
    }

    return isHazardPresent;
}

/// Method to track the motorcycle using its GPS signal
void MotorcycleAwarenessSystem::TrackMotorcycle( void )
{
    // Push the motorcycle's GPS location onto the list
    motorcycleLocation.push_front( *motorcycleGpsSignal );
}

/// Method to relay a warning to operator via bluetooth
void MotorcycleAwarenessSystem::RelayWarningToOperator( void )
{
    // Assemble the message to be sent
    BlueToothMessage_t blueToothMessage;
    blueToothMessage.isHazardPresent = true;
    // Dummy message
    blueToothMessage.dataBuffer[0] = 0x2015;

    /// @todo Transmit the bluetooth message to the operator
}

// Method to Get motorcycle's location via V2V communication
MotorCycleLocation_t MotorcycleAwarenessSystem::GetMotorcycleLocation( void )
{
    // Dummy motorcycle location from V2V communication
    MotorCycleLocation_t motorCycleLocation;
    /// @todo Acquire the data packet from the motorcycle

    return motorCycleLocation;
}
