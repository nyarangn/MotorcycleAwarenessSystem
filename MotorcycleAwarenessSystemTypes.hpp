#ifndef MOTORCYCLEAWARENESSSYSTEMTYPES_HPP
#define MOTORCYCLEAWARENESSSYSTEMTYPES_HPP

#include <list>
#include <map>

/// Enum for vehicle type
enum VehicleType
{
    MOTORCYCLE,
    CAR
};

/// Structure that emulates a CAN bus signal
struct CanSignal_t
{
    bool isBlinkerOn; ///< Blinker signal
    int busData[16]; ///< Other CAN bus data
};

typedef float Coordinate_t; ///< GPS coordinates
typedef float currentTime_t; ///< Current time for a pair of GPS coordinates
/// Structure that emulates a GPS signal
struct GpsSignal_t
{
    Coordinate_t x; ///< x-axis coordinate
    Coordinate_t y; ///< y-axis coordinate
    currentTime_t currentTime; ///< Current time at coords x & y
};

typedef float ObjectDistance; ///< Distance of an object from a detecting radar sensor
typedef float ObjectVelocity; ///< Velocity of an object detected by a radar sensor
/// Structure that emulates a Radar signal
struct RadarSignal_t
{
    ObjectDistance distance; ///< Distance from sensed object to radar sensor
    ObjectVelocity velocity; ///< Velocity of sensed object
};

/// Struct for bluetooth message
struct BlueToothMessage_t
{
    bool isHazardPresent; ///< Hazard flag
    unsigned int dataBuffer[255]; ///< Bluetooth data buffer
};

typedef int DataPacket_t[255]; ///< Data packet for the V2V communication
/// Struct for the V2V data
struct MotorCycleLocation_t
{
    DataPacket_t dataPacket; ///< V2V communication data packet
};
#endif
