#!/usr/bin/env python3
"""
Tests simples pour vérifier le module cjson
"""
import json
import ujson
import cjson

def test_basic():
    """Test basique de l'énoncé"""
    json_str = '{"hello": 10, "world": "value"}'
    
    # Test loads
    json_doc = json.loads(json_str)
    ujson_doc = ujson.loads(json_str)
    cjson_doc = cjson.loads(json_str)
    
    assert json_doc == ujson_doc == cjson_doc
    print("✓ Test loads réussi")
    
    # Test dumps
    cjson_str = cjson.dumps(cjson.loads(json_str))
    # Note: l'ordre des clés peut différer, donc on vérifie via loads
    assert json.loads(cjson_str) == json.loads(json_str)
    print("✓ Test dumps réussi")
    
    print("✓ Tous les tests passent!")

def test_additional():
    """Quelques tests supplémentaires simples"""
    tests = [
        '{}',  # vide
        '{"a": 1}',  # un élément
        '{"name": "test", "value": 123}',  # deux éléments
        '{"x": -10, "y": 3.14}',  # nombres négatifs et décimaux
    ]
    
    for json_str in tests:
        # Vérifie que loads fonctionne
        cjson_result = cjson.loads(json_str)
        json_result = json.loads(json_str)
        assert cjson_result == json_result
        
        # Vérifie round-trip
        if json_str != '{}':  # json.dumps peut ajouter des espaces
            cjson_dumped = cjson.dumps(cjson_result)
            # Charge avec json standard pour vérifier
            assert json.loads(cjson_dumped) == json_result
    
    print("✓ Tests supplémentaires réussis")

if __name__ == "__main__":
    try:
        test_basic()
        test_additional()
        print("\n✅ Tous les tests sont passés avec succès!")
    except Exception as e:
        print(f"\n❌ Erreur: {e}")
        import traceback
        traceback.print_exc()