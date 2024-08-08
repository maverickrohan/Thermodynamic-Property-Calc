# Thermodynamic-Property-Calc
This C++ program is a thermodynamic property table interpolator that allows users to find specific properties (such as specific volume, internal energy, enthalpy, or entropy) of a substance given two known thermodynamic properties (temperature, pressure, specific volume, internal energy, enthalpy, or entropy).

#Features
Interpolates properties from saturated state and compressed liquid state tables
Supports linear interpolation for properties not found in the tables
User-friendly input interface for specifying known properties and desired output property
Error handling for invalid input and out-of-range pressures
Usage
Initialize the saturated state table (saturatedTable) and compressed liquid state table (compressedTable) with the desired entries from Tables B-1 and B-4, respectively.
Compile and run the program.
Follow the prompts to enter two known thermodynamic properties and the desired output property.
The program will output the interpolated result.
Note
This program assumes that the input tables are correctly formatted and contain the necessary data for interpolation. Additionally, the program does not perform any unit conversions, so ensure that the input values are in the correct units (Kelvin, kPa, m^3/kg, kJ/kg, kJ/kg·K).
