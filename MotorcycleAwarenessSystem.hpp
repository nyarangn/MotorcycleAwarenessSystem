/////////////////////////////////////////////////////////////////////////
/// Class declaration for the Motorcycle Awareness System (MAS)
/////////////////////////////////////////////////////////////////////////
#ifndef MOTORCYCLEAWARENESSSYSTEM_HPP
#define MOTORCYCLEAWARENESSSYSTEM_HPP

#include "MotorcycleAwarenessSystemTypes.hpp"

#include <string>
#include <iostream>

class MotorcycleAwarenessSystem
{
    public:
        MotorcycleAwarenessSystem( VehicleType vehicleType );
        ~MotorcycleAwarenessSystem( void );
        void Initialize( CanSignal_t* motorcycleCanSignal, CanSignal_t* carCanSignal,
                         RadarSignal_t* motorcycleRadarSignal, GpsSignal_t* motorcycleGpsSignal,
                         GpsSignal_t* carGpsSignal );
        void MonitorConditions( void );

    private:
        std::list<GpsSignal_t> motorcycleLocation; ///< Container to track the motorcycle's location
        static const unsigned int DANGER_ZONE = 15U; ///< Threat zone in feet
        VehicleType vehicleType; ///< The vehicle type (motorcycle or car)
        std::map<VehicleType, CanSignal_t*> canSignal; ///< Storage for the can signals
        RadarSignal_t* motorcycleRadarSignal; ///< Motorcycle radar signal
        GpsSignal_t* motorcycleGpsSignal; ///< Motorcycle GPS signal
        GpsSignal_t* carGpsSignal; ///< Car GPS signal

        bool IsVehicleBlinkerOn( void );
        bool IsMotorcycleInRange( void );
        bool IsHazardPresent( void );
        void TrackMotorcycle( void );
        void RelayWarningToOperator( void );
        MotorCycleLocation_t GetMotorcycleLocation( void );
};
#endif
