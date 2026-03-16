#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <filesystem>
#include "common/Structs.h" // ajusta la ruta si tu Structs está en otro lugar

class IOManager {
public:
    IOManager() = delete;

    // Actualiza gd.filePath con la ruta final (output/<name>.bin).
    static bool GeneratorDataManager(GeneratorData &gd);

    // Actualiza sd.inputFilePath, sd.outputFilePathBin, sd.outputFilePathTxt con rutas absolutas.
    static bool SorterDataManager(SorterData &sd);

    // Comprueba existencia de archivo regular
    static bool VeryfiExistencePath(const std::string &path);

    // Devuelve true si path1 y path2 son el mismo archivo (equivalent)
    static bool AreEquivalent(const std::string &path1, const std::string &path2);

    // Cambia la ruta a una con extension .bin o .txt y en la carpeta hardcodeada
    static void ChangePath(std::string &path, bool isBin = true);

private:
    // Carpetas hardcodeadas (puedes cambiarlas aquí)
    static std::filesystem::path projectRoot();

    // Helpers internos
    static std::filesystem::path resolveInputPath(const std::string &candidate);
    static std::filesystem::path resolveOutputBase(const std::string &candidate, const std::filesystem::path &inputPath);
    static bool ensureParentExists(const std::filesystem::path &p);
};

#endif // IOMANAGER_H