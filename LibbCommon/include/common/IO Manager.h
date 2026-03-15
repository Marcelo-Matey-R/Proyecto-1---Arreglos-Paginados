#include <iostream>
#include <string>
#include "common\Structs.h"

#ifndef IOMANAGER_H
#define IOMANAGER_H

class IOManager{
    public:
    bool GeneratorDataManager(GeneratorData &gd);
    bool SorterDataManager(SorterData &gd);
    private:
    bool VeryfiExistencePath(const std::string &path);
    bool AreEquivalent(const std::string &path1, const std::string &path2);
    void ChangePath(const std::string &path);

};

#endif