colorPrint() {
    printf "\x1b[1;$2m$1\n\x1b[0m"
}

errorPrint() {
    printf "\x1b[1;$2m$1\n\x1b[0m"
    exit $3
}

clear
colorPrint "[*] Basicprogrammer10's CMake Build Script [*]" 92
colorPrint "[*] Genarateing Makefile" 36
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" . || errorPrint "[*] Error : /" 31 1
colorPrint "[*] Complete" 32
colorPrint "[*] Starting Build" 36
make || errorPrint "[*] Error : /" 31 1
colorPrint "[*] Build Complete" 32