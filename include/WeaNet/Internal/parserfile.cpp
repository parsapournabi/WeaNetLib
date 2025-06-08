#include "WeaNet/Internal/parserfile.h"

std::string toLower(const std::string &text) {
    std::string val = text;
    std::transform(val.begin(), val.end(), val.begin(), [](unsigned char c) { return std::tolower(c); });
    return val;
}

std::vector<std::vector<double>> ParserFile::loadSlowData(QString filePath) {
    std::ifstream file(filePath.toStdString().c_str());
    std::vector<std::vector<double>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            double val;
            if (toLower(cell) == "nan") {
                val = std::numeric_limits<double>::quiet_NaN();
            }
            else
                val = std::stod(cell);
            row.push_back(val);
        }
        data.push_back(row);
    }
    return data;
}
