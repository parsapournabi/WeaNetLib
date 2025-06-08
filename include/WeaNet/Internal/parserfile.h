#ifndef PARSERFILE_H
#define PARSERFILE_H

#include <iostream>
#include <fstream>
#include <QVector>
#include <QVariant>
#include <string>
#include <sstream>
#include <limits.h>
#include <algorithm>
#include <cmath>

class ParserFile {

public:
    static std::vector<std::vector<double>> loadSlowData(QString filePath);

};

#endif // PARSERFILE_H
