# Makefile complet pour le module cjson
# Auteur : [Votre nom]
# Date : $(shell date)

# ================= CONFIGURATION =================
PYTHON := python3
PYTHON_VERSION := $(shell $(PYTHON) -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")
PIP := pip3
MODULE_NAME := cjson
BUILD_DIR := build
DIST_DIR := dist
EGG_INFO := *.egg-info
VENV_DIR := venv_cjson

# Couleurs pour les messages
GREEN := \033[0;32m
YELLOW := \033[1;33m
RED := \033[0;31m
BLUE := \033[0;34m
NC := \033[0m

# ================= CIBLES PRINCIPALES =================
.PHONY: all help deps check build install test clean uninstall

# Cible par défaut
all: deps check build test
	@echo "$(GREEN)✓ Toutes les étapes terminées avec succès$(NC)"

# Aide
help:
	@echo "$(BLUE)=== AIDE - Makefile pour cjson ===$(NC)"
	@echo "Cibles disponibles:"
	@echo "  $(GREEN)make deps$(NC)     - Installe les dépendances système (nécessite sudo)"
	@echo "  $(GREEN)make check$(NC)    - Vérifie les dépendances"
	@echo "  $(GREEN)make build$(NC)    - Compile le module"
	@echo "  $(GREEN)make install$(NC)  - Installe le module"
	@echo "  $(GREEN)make test$(NC)     - Exécute les tests"
	@echo "  $(GREEN)make clean$(NC)    - Nettoie les fichiers générés"
	@echo "  $(GREEN)make all$(NC)      - Exécute check, build, test"
	@echo "  $(GREEN)make venv$(NC)     - Crée un environnement virtuel"
	@echo ""
	@echo "Détails:"
	@echo "  Python: $(PYTHON_VERSION)"
	@echo "  Module: $(MODULE_NAME)"

# ================= INSTALLATION DES DÉPENDANCES =================
deps:
	@echo "$(YELLOW)Installation des dépendances système... (nécessite sudo)$(NC)"
	sudo apt-get update
	sudo apt-get install -y \
		python3 \
		python3-dev \
		python3-pip \
		python3-venv \
		build-essential \
		gcc \
		make \
		pkg-config
	@echo "$(GREEN)✓ Dépendances système installées$(NC)"
	@echo "$(YELLOW)Installation des dépendances Python...$(NC)"
	$(PIP) install --user --upgrade pip setuptools wheel
	@echo "$(GREEN)✓ Dépendances Python installées$(NC)"

# ================= VÉRIFICATION DES DÉPENDANCES =================
check:
	@echo "$(YELLOW)Vérification des dépendances...$(NC)"
	
	# Vérifier Python 3
	@command -v $(PYTHON) >/dev/null 2>&1 || \
		{ echo "$(RED)✗ Python3 non installé$(NC)"; exit 1; }
	@echo "$(GREEN)✓ Python3 trouvé$(NC)"
	
	# Vérifier gcc
	@command -v gcc >/dev/null 2>&1 || \
		{ echo "$(RED)✗ GCC non installé$(NC)"; exit 1; }
	@echo "$(GREEN)✓ GCC trouvé$(NC)"
	
	# Vérifier make
	@command -v make >/dev/null 2>&1 || \
		{ echo "$(RED)✗ make non installé$(NC)"; exit 1; }
	@echo "$(GREEN)✓ make trouvé$(NC)"
	
	# Vérifier Python.h
	@$(PYTHON) -c "import sysconfig; import os; path = sysconfig.get_path('include'); print(f'Include: {path}'); assert os.path.exists(os.path.join(path, 'Python.h')), 'Python.h non trouvé'" && \
		echo "$(GREEN)✓ Python.h trouvé$(NC)" || \
		{ echo "$(RED)✗ Python.h non trouvé - installez python3-dev$(NC)"; exit 1; }
	
	# Vérifier pip
	@command -v $(PIP) >/dev/null 2>&1 || \
		{ echo "$(RED)✗ pip3 non installé$(NC)"; exit 1; }
	@echo "$(GREEN)✓ pip3 trouvé$(NC)"
	
	@echo "$(GREEN)✓ Toutes les dépendances sont satisfaites$(NC)"

# ================= ENVIRONNEMENT VIRTUEL =================
venv: $(VENV_DIR)

$(VENV_DIR):
	@echo "$(YELLOW)Création de l'environnement virtuel...$(NC)"
	$(PYTHON) -m venv $(VENV_DIR)
	@echo "$(GREEN)✓ Environnement virtuel créé$(NC)"
	@echo "Pour l'activer: source $(VENV_DIR)/bin/activate"

# ================= COMPILATION =================
build: check
	@echo "$(YELLOW)Compilation du module cjson...$(NC)"
	
	# Méthode 1: Avec setup.py (recommandée)
	@echo "$(BLUE)Méthode 1: Compilation avec setup.py$(NC)"
	$(PYTHON) setup.py build_ext --inplace
	
	# Vérifier que le module a été créé
	@if ls $(MODULE_NAME)*.so >/dev/null 2>&1; then \
		echo "$(GREEN)✓ Module compilé avec succès$(NC)"; \
		echo "   Fichier: $$(ls $(MODULE_NAME)*.so | head -1)"; \
	else \
		# Méthode 2: Compilation manuelle de secours
		@echo "$(BLUE)Méthode 2: Compilation manuelle$(NC)"; \
		INCLUDE_PATH=$$($(PYTHON) -c "import sysconfig; print(sysconfig.get_path('include'))"); \
		echo "Chemin d'inclusion: $$INCLUDE_PATH"; \
		gcc -c -fPIC -I"$$INCLUDE_PATH" cjson.c -o cjson.o && \
		SUFFIX=$$($(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))") && \
		gcc -shared cjson.o -o $(MODULE_NAME)$$SUFFIX && \
		echo "$(GREEN)✓ Module compilé manuellement$(NC)" || \
		{ echo "$(RED)✗ Échec de la compilation$(NC)"; exit 1; } \
	fi
	
	# Tester l'import rapide
	@$(PYTHON) -c "import sys; sys.path.insert(0, '.'); import $(MODULE_NAME); print('$(GREEN)✓ Module importable$(NC)')" || \
		{ echo "$(RED)✗ Erreur lors de l'import$(NC)"; exit 1; }

# ================= INSTALLATION =================
install: build
	@echo "$(YELLOW)Installation du module...$(NC)"
	
	# Option 1: Installation système (nécessite sudo)
	# sudo $(PYTHON) setup.py install
	
	# Option 2: Installation utilisateur (recommandée)
	$(PYTHON) setup.py install --user
	
	@echo "$(GREEN)✓ Module installé$(NC)"
	@echo "Utilisation: $(PYTHON) -c 'import $(MODULE_NAME); print($(MODULE_NAME).__file__)'"

# ================= TESTS =================
test: build
	@echo "$(YELLOW)Exécution des tests...$(NC)"
	
	# Test 1: Importation
	@echo "$(BLUE)1. Test d'importation...$(NC)"
	@$(PYTHON) -c "import sys; sys.path.insert(0, '.'); import $(MODULE_NAME); print('$(GREEN)  ✓ Module importé$(NC)')"
	
	# Test 2: Test basique
	@echo "$(BLUE)2. Test basique...$(NC)"
	@$(PYTHON) -c "import sys; sys.path.insert(0, '.'); import $(MODULE_NAME); \
		result = $(MODULE_NAME).loads('{\"test\": 123}'); \
		print('  ✓ Test loads:', result); \
		json_str = $(MODULE_NAME).dumps({'hello': 'world'}); \
		print('  ✓ Test dumps:', json_str)" || \
		{ echo "$(RED)  ✗ Test basique échoué$(NC)"; exit 1; }
	
	# Test 3: Tests unitaires complets (si le fichier existe)
	@if [ -f "test_cjson.py" ]; then \
		echo "$(BLUE)3. Tests unitaires complets...$(NC)"; \
		$(PYTHON) test_cjson.py && \
		echo "$(GREEN)  ✓ Tests unitaires passés$(NC)" || \
		{ echo "$(RED)  ✗ Tests unitaires échoués$(NC)"; exit 1; }; \
	else \
		echo "$(YELLOW)  ℹ Fichier test_cjson.py non trouvé$(NC)"; \
	fi
	
	# Test 4: Tests de performance (si le fichier existe)
	@if [ -f "test_performance.py" ]; then \
		echo "$(BLUE)4. Tests de performance...$(NC)"; \
		$(PYTHON) test_performance.py && \
		echo "$(GREEN)  ✓ Tests de performance passés$(NC)" || \
		{ echo "$(RED)  ✗ Tests de performance échoués$(NC)"; exit 1; }; \
	else \
		echo "$(YELLOW)  ℹ Fichier test_performance.py non trouvé$(NC)"; \
	fi
	
	@echo "$(GREEN)✓ Tous les tests sont passés$(NC)"

# ================= NETTOYAGE =================
clean:
	@echo "$(YELLOW)Nettoyage des fichiers générés...$(NC)"
	
	# Fichiers de compilation
	rm -f *.o *.so $(MODULE_NAME)*.so
	rm -f cjson.cpython-*.so
	
	# Fichiers Python
	rm -rf __pycache__/
	rm -f *.pyc
	
	# Build directories
	rm -rf $(BUILD_DIR)/
	rm -rf $(DIST_DIR)/
	rm -rf $(EGG_INFO)
	
	# Fichiers temporaires
	rm -f temp.json test_data.json
	
	# Environnement virtuel
	@if [ -d "$(VENV_DIR)" ]; then \
		echo "  Suppression de $(VENV_DIR)"; \
		rm -rf $(VENV_DIR); \
	fi
	
	@echo "$(GREEN)✓ Nettoyage terminé$(NC)"

# ================= DÉSINSTALLATION =================
uninstall:
	@echo "$(YELLOW)Désinstallation du module...$(NC)"
	
	# Essayer via pip d'abord
	@if $(PIP) show $(MODULE_NAME) >/dev/null 2>&1; then \
		$(PIP) uninstall -y $(MODULE_NAME) && \
		echo "$(GREEN)✓ Module désinstallé via pip$(NC)"; \
	else \
		echo "$(YELLOW)Module non installé via pip$(NC)"; \
	fi
	
	# Supprimer les fichiers manuellement
	@for dir in $$($(PYTHON) -c "import sys; print('\n'.join(sys.path))"); do \
		if [ -d "$$dir" ]; then \
			rm -f "$$dir/$(MODULE_NAME)*.so" 2>/dev/null; \
			rm -rf "$$dir/$(MODULE_NAME)-*.egg-info" 2>/dev/null; \
		fi; \
	done
	
	@echo "$(GREEN)✓ Désinstallation terminée$(NC)"

# ================= COMMANDES SPÉCIALES =================
# Génère un fichier de test JSON
test-data:
	@echo "$(YELLOW)Génération de données de test...$(NC)"
	@echo '{"test": 123, "hello": "world", "list": [1, 2, 3], "nested": {"key": "value"}}' > test_data.json
	@echo "$(GREEN)✓ Données de test créées: test_data.json$(NC)"

# Vérifie l'environnement en détail
debug:
	@echo "$(BLUE)=== DEBUG - Informations système ===$(NC)"
	@echo "Python: $$($(PYTHON) --version 2>&1)"
	@echo "Python path: $$(which $(PYTHON))"
	@echo "Python include: $$($(PYTHON) -c 'import sysconfig; print(sysconfig.get_path(\"include\"))')"
	@echo "GCC: $$(gcc --version | head -1)"
	@echo "Make: $$(make --version | head -1)"
	@echo "Architecture: $$(uname -m)"
	@echo "OS: $$(lsb_release -d 2>/dev/null || echo 'Non disponible')"

# Compilation rapide (sans tests)
quick: check
	@$(PYTHON) setup.py build_ext --inplace > /dev/null 2>&1
	@echo "$(GREEN)✓ Compilation rapide terminée$(NC)"

# ================= RECETTES INTERNES =================
# Règle pour afficher la version
version:
	@echo "Module: $(MODULE_NAME)"
	@echo "Python: $(PYTHON_VERSION)"
	@echo "Build: $$(date)"

# ================= ALIAS =================
# Alias courants
compile: build
check-deps: check
unit-test: test
bench: test-perf
full: deps build test

# ================= DOCUMENTATION =================
README:
	@echo "$(YELLOW)Génération du README...$(NC)"
	@echo "# Module $(MODULE_NAME)" > README.md
	@echo "" >> README.md
	@echo "## Installation" >> README.md
	@echo '```bash' >> README.md
	@echo "make deps     # Installer les dépendances (sudo)" >> README.md
	@echo "make build    # Compiler le module" >> README.md
	@echo "make install  # Installer le module" >> README.md
	@echo '```' >> README.md
	@echo "" >> README.md
	@echo "## Utilisation" >> README.md
	@echo '```python' >> README.md
	@echo "import $(MODULE_NAME)" >> README.md
	@echo 'data = $(MODULE_NAME).loads(\'{"test": 123}\')' >> README.md
	@echo 'print(data)' >> README.md
	@echo '```' >> README.md
	@echo "" >> README.md
	@echo "## Tests" >> README.md
	@echo '```bash' >> README.md
	@echo "make test    # Exécuter tous les tests" >> README.md
	@echo '```' >> README.md
	@echo "$(GREEN)✓ README.md généré$(NC)"