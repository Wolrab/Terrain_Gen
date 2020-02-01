#include "Util.h"

bool getShaderSource(const char* fname, string& src) {
    fstream f(fname, fstream::in);
    bool err = false;

    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            src.append(line);
            src.append("\n");
        }
    }
    else {
        fprintf(stderr, "Could not open file %s\n", fname);
        err = true;
    }
    return err;
}