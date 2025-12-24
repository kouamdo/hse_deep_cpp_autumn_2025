# Makefile pour le module cjson
# Auteur : [Votre Nom]
# Cours : [Nom du cours]

PYTHON = python3
PIP = pip3
MODULE_NAME = cjson
SO_FILE = $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))")
MODULE_PATH = $(MODULE_NAME)$(SO_FILE)

# Couleurs pour les messages
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m # No Color

.PHONY: all build clean install uninstall test test-perf benchmark help

all: build

# Construction du module
build: $(MODULE_NAME).c setup.py
	@echo "$(YELLOW)Compilation du module cjson...$(NC)"
	$(PYTHON) setup.py build_ext --inplace
	@if [ -f "$(MODULE_PATH)" ]; then \
		echo "$(GREEN)✓ Module compilé avec succès : $(MODULE_PATH)$(NC)"; \
	else \
		echo "$(RED)✗ Échec de la compilation$(NC)"; \
		exit 1; \
	fi

# Installation du module
install: build
	@echo "$(YELLOW)Installation du module cjson...$(NC)"
	$(PYTHON) setup.py install --user
	@echo "$(GREEN)✓ Module installé avec succès$(NC)"
	@echo "Utilisez 'import cjson' dans Python pour l'utiliser"

# Installation en mode développement (pour les tests)
develop:
	@echo "$(YELLOW)Installation en mode développement...$(NC)"
	$(PIP) install -e . --user
	@echo "$(GREEN)✓ Installation en mode développement terminée$(NC)"

# Nettoyage des fichiers générés
clean:
	@echo "$(YELLOW)Nettoyage des fichiers générés...$(NC)"
	rm -rf build/
	rm -rf dist/
	rm -rf *.egg-info/
	rm -f *.so
	rm -f *.pyd
	rm -f cjson*.so
	rm -f *.o
	rm -f __pycache__/
	rm -f *.pyc
	@echo "$(GREEN)✓ Nettoyage terminé$(NC)"

# Désinstallation du module
uninstall:
	@echo "$(YELLOW)Désinstallation du module cjson...$(NC)"
	$(PIP) uninstall -y $(MODULE_NAME) || true
	@echo "$(GREEN)✓ Module désinstallé$(NC)"

# Exécution des tests unitaires
test: build
	@echo "$(YELLOW)Exécution des tests unitaires...$(NC)"
	$(PYTHON) -m pytest test_cjson.py -v || $(PYTHON) test_cjson.py

# Tests de performance
test-perf: build
	@echo "$(YELLOW)Exécution des tests de performance...$(NC)"
	$(PYTHON) test_performance.py

# Alias pour benchmark
benchmark: test-perf

# Test de validation avec l'exemple donné
validate: build
	@echo "$(YELLOW)Validation avec l'exemple du sujet...$(NC)"
	$(PYTHON) -c "import cjson; json_str = '{\"hello\": 10, \"world\": \"value\"}'; print('Test loads:', cjson.loads(json_str)); print('Test dumps:', cjson.dumps(cjson.loads(json_str)))"


# Règles de dépendance
$(MODULE_NAME).o: $(MODULE_NAME).c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Règle par défaut
.DEFAULT_GOAL := help