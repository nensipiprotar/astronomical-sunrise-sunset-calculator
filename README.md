# Astronomical Sunrise–Sunset Calculator (C)

# Project Overview

This project implements an astronomical algorithm in C to calculate accurate Sunrise and Sunset times for a given date and geographical location (latitude and longitude).

The system uses solar geometry principles including Solar Declination, Hour Angle, Equation of Time, and Longitude correction to compute time in IST (Indian Standard Time).

The implementation is designed to be mathematically accurate, logically structured, and easily portable to embedded systems such as ESP32 or STM32.

# Objective

To design a computation engine capable of determining daily Sunrise and Sunset timings using astronomical formulas, with potential use in automation systems such as:

- Astronomical Time Switch
- Smart Street Lighting
- Solar-based Automation
- Embedded Relay Control Systems

# Engineering Concepts Used

- Earth axial tilt modeling (23.45°)
- Day-of-Year calculation with leap year handling  
- Solar Declination calculation  
- Spherical trigonometry (Hour Angle derivation)  
- Equation of Time correction  
- Longitude-based time zone adjustment  
- 24-hour time normalization
  
# Mathematical Model

- Solar Declination
δ = 23.45 × sin[(360/365) × (N − 81)]

Where:
N = Day of Year

- Hour Angle
cos(H) = (sin(h₀) − sin(lat) × sin(δ)) / (cos(lat) × cos(δ))

Where:
H = Hour Angle  
h₀ = -0.83° (Sun altitude including refraction)

- Equation of Time
EoT = 9.87sin(2B) − 7.53cos(B) − 1.5sin(B)

B = (360/365) × (N − 81)

- Final Sunrise / Sunset (IST)

Sunrise = 12 − (H/15) + Longitude Correction − (EoT/60)

Sunset  = 12 + (H/15) + Longitude Correction − (EoT/60)

# Program Features 

- Leap year validation  
- Accurate Day-of-Year computation  
- Solar altitude correction (-0.83°)  
- IST standard meridian adjustment (82.5°)  
- Edge case handling (Polar conditions)  
- Floating-point precision calculations  
