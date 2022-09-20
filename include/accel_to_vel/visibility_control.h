#ifndef ACCEL_TO_VEL__VISIBILITY_CONTROL_H_
#define ACCEL_TO_VEL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ACCEL_TO_VEL_EXPORT __attribute__ ((dllexport))
    #define ACCEL_TO_VEL_IMPORT __attribute__ ((dllimport))
  #else
    #define ACCEL_TO_VEL_EXPORT __declspec(dllexport)
    #define ACCEL_TO_VEL_IMPORT __declspec(dllimport)
  #endif
  #ifdef ACCEL_TO_VEL_BUILDING_LIBRARY
    #define ACCEL_TO_VEL_PUBLIC ACCEL_TO_VEL_EXPORT
  #else
    #define ACCEL_TO_VEL_PUBLIC ACCEL_TO_VEL_IMPORT
  #endif
  #define ACCEL_TO_VEL_PUBLIC_TYPE ACCEL_TO_VEL_PUBLIC
  #define ACCEL_TO_VEL_LOCAL
#else
  #define ACCEL_TO_VEL_EXPORT __attribute__ ((visibility("default")))
  #define ACCEL_TO_VEL_IMPORT
  #if __GNUC__ >= 4
    #define ACCEL_TO_VEL_PUBLIC __attribute__ ((visibility("default")))
    #define ACCEL_TO_VEL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ACCEL_TO_VEL_PUBLIC
    #define ACCEL_TO_VEL_LOCAL
  #endif
  #define ACCEL_TO_VEL_PUBLIC_TYPE
#endif
#endif  // ACCEL_TO_VEL__VISIBILITY_CONTROL_H_
// Generated 20-Sep-2022 15:30:51
// Copyright 2019-2020 The MathWorks, Inc.
