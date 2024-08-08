#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Structure to represent a thermodynamic property table entry
struct TableEntry {
    double temperature; // in Kelvin
    double pressure;    // in kPa
    double specificVolume; // in m^3/kg
    double specificInternalEnergy; // in kJ/kg
    double specificEnthalpy; // in kJ/kg
    double specificEntropy; // in kJ/kg·K
};

// Function to perform linear interpolation
double interpolate(double x1, double y1, double x2, double y2, double x) {
    return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

// Function to find a property in the saturated state table
double findPropertyInSaturatedTable(const std::vector<TableEntry>& table, double temperature, double pressure, char property) {
    for (const auto& entry : table) {
        if (std::abs(entry.temperature - temperature) < 0.01 && std::abs(entry.pressure - pressure) < 0.01) {
            switch (property) {
                case 'v': return entry.specificVolume;
                case 'u': return entry.specificInternalEnergy;
                case 'h': return entry.specificEnthalpy;
                case 's': return entry.specificEntropy;
                default: std::cerr << "Invalid property." << std::endl; exit(1);
            }
        }
    }
    // If direct value is not found, perform linear interpolation
    for (size_t i = 0; i < table.size() - 1; ++i) {
        if (table[i].temperature <= temperature && temperature <= table[i + 1].temperature) {
            double x1 = table[i].temperature;
            double x2 = table[i + 1].temperature;
            double y1, y2;
            switch (property) {
                case 'v':
                    y1 = table[i].specificVolume;
                    y2 = table[i + 1].specificVolume;
                    break;
                case 'u':
                    y1 = table[i].specificInternalEnergy;
                    y2 = table[i + 1].specificInternalEnergy;
                    break;
                case 'h':
                    y1 = table[i].specificEnthalpy;
                    y2 = table[i + 1].specificEnthalpy;
                    break;
                case 's':
                    y1 = table[i].specificEntropy;
                    y2 = table[i + 1].specificEntropy;
                    break;
                default: std::cerr << "Invalid property." << std::endl; exit(1);
            }
            return interpolate(x1, y1, x2, y2, temperature);
        }
    }
    std::cerr << "Property not found in saturated table." << std::endl; exit(1);
}

// Function to find a property in the compressed liquid state table
double findPropertyInCompressedTable(const std::vector<TableEntry>& table, double temperature, double pressure, char property) {
    for (const auto& entry : table) {
        if (std::abs(entry.temperature - temperature) < 0.01 && std::abs(entry.pressure - pressure) < 0.01) {
            switch (property) {
                case 'v': return entry.specificVolume;
                case 'u': return entry.specificInternalEnergy;
                case 'h': return entry.specificEnthalpy;
                case 's': return entry.specificEntropy;
                default: std::cerr << "Invalid property." << std::endl; exit(1);
            }
        }
    }



int main(){
    // Initialize saturated state table
    std::vector<TableEntry> saturatedTable = {
        // Add entries from Table B-1 here
    };

    // Initialize compressed liquid state table
    std::vector<TableEntry> compressedTable = {
        // Add entries from Table B-4 here
    };

    // Prompt user for input
    double known1, known2, required;
    char property;
    std::cout << "Enter two known thermodynamic properties (temperature, pressure, specific volume, specific internal energy, specific enthalpy, or specific entropy): ";
    std::cin >> known1 >> known2;
    std::cout << "Enter the property you are looking for ('v', 'u', 'h', or 's'): ";
    std::cin >> property;

    // Determine which table to use based on the given pressure
    double pressure;
    if (std::cin.ignore() >> pressure) {
        if (pressure > 22064) {
            std::cerr << "Error: Pressure is out of range." << std::endl;
            return 1;
        }

        if (pressure > 0) {
            // Search compressed liquid state table
            double result = findPropertyInCompressedTable(compressedTable, known1, pressure, property);
            std::cout << "Result: " << result << std::endl;
        } else {
            // Search saturated state table
            double result = findPropertyInSaturatedTable(saturatedTable, known1, pressure, property);
            std::cout << "Result: " << result << std::endl;
        }
    } else {
        std::cerr << "Error: Invalid input." << std::endl;
        return 1;
    }

    return 0;
}