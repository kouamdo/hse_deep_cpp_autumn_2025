#!/usr/bin/env python3
"""
Vérifie que toutes les dépendances sont installées
"""
import sys
import subprocess
import os

def check_command(cmd, package):
    """Vérifie si une commande existe"""
    try:
        subprocess.run(cmd, shell=True, check=True, 
                      stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        return True
    except:
        print(f"❌ {package} n'est pas installé")
        return False

def main():
    print("Vérification des dépendances...")
    
    # Vérifier python3
    if not check_command("python3 --version", "Python 3"):
        print("Installez Python 3:")
        print("  Ubuntu: sudo apt install python3")
        print("  Fedora: sudo dnf install python3")
        sys.exit(1)
    
    # Vérifier python3-dev
    if sys.platform.startswith('linux'):
        if not os.path.exists('/usr/include/python3.8/Python.h'):
            print("❌ python3-dev n'est pas installé")
            print("\nInstallez les headers de développement Python:")
            print("  Ubuntu/Debian: sudo apt install python3-dev")
            print("  Fedora: sudo dnf install python3-devel")
            print("  Arch: sudo pacman -S python")
            sys.exit(1)
    
    # Vérifier gcc
    if not check_command("gcc --version", "GCC"):
        print("Installez le compilateur C:")
        print("  Ubuntu: sudo apt install build-essential")
        print("  Fedora: sudo dnf install gcc")
    
    print("✅ Toutes les dépendances sont installées")
    print("\nPour compiler: make")
    print("Pour tester: make test")

if __name__ == "__main__":
    main()