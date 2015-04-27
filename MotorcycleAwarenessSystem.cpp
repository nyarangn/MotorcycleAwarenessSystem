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

/////////////////////////////////////////////////////////////////////////
/// Method to initialize the MAS system
///
/// @param[in] motorcycleTurnSignal  Motorcycle turn signal
/// @param[in] carTurnSignal         Car turn signal
/// @param[in] motorcycleRadarSignal Motorcycle radar signal
/// @param[in] motorcycleGpsSignal   Motorcycle GPS signal
/// @param[in] carGpsSignal          Car GPS signal
///
/// @return    Pass fail status of the initialization
///
/// @retval    true
/// @retval    false
/////////////////////////////////////////////////////////////////////////
bool MotorcycleAwarenessSystem::Initialize( TurnSignal_t* motorcycleTurnSignal, TurnSignal_t* carTurnSignal,
                                            RadarSignal_t* motorcycleRadarSignal, GpsSignal_t* motorcycleGpsSignal,
                                            GpsSignal_t* carGpsSignal  )
{
    // Initialize the initialization state
    bool isSuccess = false;

    if ( motorcycleTurnSignal != (TurnSignal_t*)NULL &&
         carTurnSignal != (TurnSignal_t*)NULL &&
         motorcycleRadarSignal != (RadarSignal_t*)NULL &&
         motorcycleGpsSignal != (GpsSignal_t*)NULL &&
         carGpsSignal != (GpsSignal_t*)NULL )
    {
        // Initialize the motorcycle radar signal
        this->motorcycleRadarSignal = motorcycleRadarSignal;

        // Initialize the turn signal map
        turnSignal[MOTORCYCLE] = motorcycleTurnSignal;
        turnSignal[CAR] = carTurnSignal;

        // Initialize the GPS signals
        this->motorcycleGpsSignal = motorcycleGpsSignal;
        this->carGpsSignal = carGpsSignal;

        isSuccess = true;
    }

    return isSuccess;
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
            // Warn the motorcycle operator
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
    bool isBlinkerOn = false;

    if ( this->turnSignal[vehicleType]->isRightBlinkerOn ||
         this->turnSignal[vehicleType]->isLeftBlinkerOn )
    {
        isBlinkerOn = true;
    }

    return isBlinkerOn;
}

/// Method to determine whether the motorcycle is within the car's range
bool MotorcycleAwarenessSystem::IsMotorcycleInRange( void )
{
    bool isInRange = false;

    // Determine where the motorcycle is relative to the car using the GPS signals
    if ( abs( (this->carGpsSignal->x) - (this->motorcycleGpsSignal->x) ) <= SAFETY_ZONE &&
         abs( (this->carGpsSignal->y) - (this->motorcycleGpsSignal->y) ) <= SAFETY_ZONE )
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

/// Method to determine whether a hazard is within the motorcycle's safety zone.
/// An object within the safety zone is of potential danger to the motorcycle rider.
bool MotorcycleAwarenessSystem::IsHazardPresent( void )
{
    bool isHazardPresent = false;

    if ( abs( this->motorcycleRadarSignal->objectDistance ) <= SAFETY_ZONE )
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

/// Method to relay a warning to operator via bluetooth connectivity
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
