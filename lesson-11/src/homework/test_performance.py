#!/usr/bin/env python3
"""
Test de performance minimal
"""
import time
import json
import cjson

def generate_test_data():
    """Génère des données de test simples"""
    # JSON avec 1000 paires clé-valeur
    data = {}
    for i in range(1000):
        data[f"key_{i}"] = f"value_{i}" if i % 2 == 0 else i
    return json.dumps(data)

def main():
    print("Test de performance cjson vs json\n" + "="*40)
    
    # Préparation des données
    json_str = generate_test_data()
    print(f"Taille des données: {len(json_str)} caractères")
    
    # Test de vitesse de loads
    print("\n1. Test loads (100 itérations):")
    
    # json standard
    start = time.time()
    for _ in range(100):
        json.loads(json_str)
    json_time = time.time() - start
    
    # cjson
    start = time.time()
    for _ in range(100):
        cjson.loads(json_str)
    cjson_time = time.time() - start
    
    print(f"  json:  {json_time:.3f}s")
    print(f"  cjson: {cjson_time:.3f}s")
    
    if cjson_time > 0:
        speedup = json_time / cjson_time
        print(f"  Speedup: {speedup:.2f}x")
    
    # Test de vitesse de dumps
    print("\n2. Test dumps (100 itérations):")
    data = json.loads(json_str)
    
    # json standard
    start = time.time()
    for _ in range(100):
        json.dumps(data)
    json_time = time.time() - start
    
    # cjson
    start = time.time()
    for _ in range(100):
        cjson.dumps(data)
    cjson_time = time.time() - start
    
    print(f"  json:  {json_time:.3f}s")
    print(f"  cjson: {cjson_time:.3f}s")
    
    if cjson_time > 0:
        speedup = json_time / cjson_time
        print(f"  Speedup: {speedup:.2f}x")
    
    # Test avec un très gros JSON pour atteindre 100ms
    print("\n3. Test avec données volumineuses (>100ms):")
    big_data = {}
    for i in range(10000):
        big_data[f"big_key_{i}"] = f"big_value_{i}" * 10
    big_json_str = json.dumps(big_data)
    
    start = time.time()
    result = cjson.loads(big_json_str)
    elapsed = time.time() - start
    
    print(f"  Taille: {len(big_json_str)} caractères")
    print(f"  Temps cjson.loads: {elapsed:.3f}s")
    
    if elapsed >= 0.1:
        print("  ✅ Test >100ms réussi")
    else:
        print(f"  ⚠ Temps: {elapsed*1000:.1f}ms (<100ms)")
        print("  Note: Augmentez la taille pour plus de précision")
    
    print("\n" + "="*40)
    print("Test de performance terminé")

if __name__ == "__main__":
    try:
        import ujson
        print("Note: ujson n'est pas installé, comparaison limitée à json standard")
        print("Installez avec: pip install ujson\n")
    except ImportError:
        pass
    
    main()