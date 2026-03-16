#include "common/IOManager.h"
#include <iostream>
#include <algorithm>

#pragma region Helpers
// Path a seguir
std::filesystem::path IOManager::projectRoot() {
    static std::filesystem::path root =
        std::filesystem::current_path();
    return root;
}

bool IOManager::ensureParentExists(const std::filesystem::path &p) {
    try {
        std::filesystem::path parent = p.parent_path();
        if (parent.empty()) return true;
        if (!std::filesystem::exists(parent)) std::filesystem::create_directories(parent);
        return true;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[IOManager] No se pudo crear directorio: " << e.what() << '\n';
        return false;
    }
}

// si p es un path absoluto lo usamos tal cual
// caso contrario devolvemos el abosulto entre la root y el path de origin
std::filesystem::path IOManager::resolveInputPath(const std::string &candidate) {
    std::filesystem::path p(candidate);
    auto root = projectRoot();

    try {
        if (p.is_absolute()) {
            return p;
        }

        return std::filesystem::absolute(root / p);

    } catch (...) {
        return std::filesystem::path(candidate);
    }
}

//  Genera el path para el output
std::filesystem::path IOManager::resolveOutputBase(const std::string &candidate, const std::filesystem::path &inputPath) {
    std::filesystem::path c(candidate);
    std::filesystem::path stem;
    auto root = projectRoot();
    if (c.has_filename() && !c.filename().empty()) {
        // tomar el stem del candidate si el usuario pasó un nombre; si pasó ruta con carpeta, usamos filename
        stem = c.stem();
        if (stem.empty()) {
            // fallback: usar el stem del input
            stem = inputPath.stem();
        }
    } else {
        // fallback al stem del input
        stem = inputPath.stem();
    }
    return  root / "Files" / "output" / stem;
}
#pragma endregion

#pragma region verificadores
// Verificamos la existencia del path
bool IOManager::VeryfiExistencePath(const std::string &path) {
    try {
        std::filesystem::path p = std::filesystem::absolute(path);
        if (!std::filesystem::exists(p)) {
            std::cerr << "[IOManager] Ruta inexistente: " << p.string() << '\n';
            return false;
        }
        if (!std::filesystem::is_regular_file(p)) {
            std::cerr << "[IOManager] No es un archivo regular: " << p.string() << '\n';
            return false;
        }
        return true;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[IOManager] Error filesystem: " << e.what() << '\n';
        return false;
    }
}

//Verificamos si son equivalente
bool IOManager::AreEquivalent(const std::string &path1, const std::string &path2) {
    try {
        std::filesystem::path p1 = std::filesystem::absolute(path1);
        std::filesystem::path p2 = std::filesystem::absolute(path2);
        if (!std::filesystem::exists(p1) || !std::filesystem::exists(p2)) return false;
        return std::filesystem::equivalent(p1, p2);
    } catch (const std::filesystem::filesystem_error &e) {
        // si equivalent lanza, asumimos no-equivalencia para no bloquear
        std::cerr << "[IOManager] Error comprobando equivalencia (se asume distinto): " << e.what() << '\n';
        return false;
    }
}

// Esta función sustituye la ruta dada por la ruta en carpeta hardcodeada y con la ext esperada.
// Si el usuario pasó una ruta completa, solo usamos el filename.
void IOManager::ChangePath(std::string &path, bool isBin) {
    
    std::filesystem::path inputCandidate(path);
    std::filesystem::path outBase = resolveOutputBase(path, inputCandidate); // usa inputCandidate sólo si necesario

    std::filesystem::path outBin = outBase;
    outBin.replace_extension(isBin ? ".bin" : ".txt");

    // Aseguramos carpeta
    if (!ensureParentExists(outBin)) {
        std::cerr << "[IOManager] No se pudo crear carpeta para ChangePath\n";
        return;
    }

    path = std::filesystem::absolute(outBin).string(); // actualizamos con ruta absoluta al archivo final
}
#pragma endregion


#pragma region Generadores
// Genera el cambio de los path necesario del Generator Data Manager introducido
bool IOManager::GeneratorDataManager(GeneratorData &gd) {
    try {
        std::filesystem::path candidate(gd.filePath);
        auto root = projectRoot();

        std::filesystem::path stem;

        if (candidate.has_filename())
            stem = candidate.stem();
        else
            stem = "generated";

        // 🔹 siempre generar en Files/input
        std::filesystem::path outBin =
            root / "Files" / "input" / stem;

        outBin.replace_extension(".bin");

        if (!ensureParentExists(outBin))
            return false;

        gd.filePath = std::filesystem::absolute(outBin).string();

        return true;
    }
    catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[IOManager] Error en GeneratorDataManager: "
                  << e.what() << '\n';
        return false;
    }
}

//Genera el cambio de los path necesario del Sorter Data Manager introducido
bool IOManager::SorterDataManager(SorterData &sd) {
    try {
        // Resolver input
        std::filesystem::path inputResolved = resolveInputPath(sd.inputFilePath);

        if (!std::filesystem::exists(inputResolved)) {
            std::cerr << "[IOManager] Input no existe: " << inputResolved << '\n';
            std::cerr << "[DEBUG] CWD: " << std::filesystem::current_path() << "\n";
            std::cerr << "[DEBUG] checking input path: '" << sd.inputFilePath << "\n";

            return false;
        }
        if(!std::filesystem::is_regular_file(inputResolved)){
            std::cerr << "[IOManager] Inputno es archivo: " << inputResolved <<'\n';
            return false;
        }
        // Resolver base de salida"
        std::filesystem::path base = resolveOutputBase(sd.outputFilePathBin.empty() ? inputResolved.stem().string() : sd.outputFilePathBin, inputResolved);

        // formamos rutas finales
        std::filesystem::path outBin = base; outBin.replace_extension(".bin");
        std::filesystem::path outTxt = base; outTxt.replace_extension(".txt");

        // Crear carpeta de output si no existe
        if (!ensureParentExists(outBin) || !ensureParentExists(outTxt)) return false;

        // Evitar sobrescribir input: si outBin equivale a input, añadimos sufijo _sorted
        bool equiv = false;
        try {
            if (std::filesystem::exists(outBin)) equiv = std::filesystem::equivalent(inputResolved, outBin);
        } catch (...) { equiv = false; }

        if (equiv) {
            // Añadimos sufijo y recalculamos
            std::string stem = outBin.stem().string() + "_sorted";
            std::filesystem::path parent = outBin.parent_path();
            outBin = parent / (stem + ".bin");
            outTxt = parent / (stem + ".txt");
            // Aseguramos parent por si acaso
            if (!ensureParentExists(outBin) || !ensureParentExists(outTxt)) return false;
        }

        // Actualizar struct con rutas absolutas resueltas
        sd.inputFilePath = std::filesystem::absolute(inputResolved).string();
        sd.outputFilePathBin = std::filesystem::absolute(outBin).string();
        sd.outputFilePathTxt = std::filesystem::absolute(outTxt).string();

        return true;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "[IOManager] Error en SorterDataManager: " << e.what() << '\n';
        return false;
    }
}
#pragma endregion