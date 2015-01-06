/**
 * @file test.c
 * Fichier source des tests.
 * @author Hector Basset
 * @author Joris Toulmonde
 * @date 10 novembre 2014
 */

#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../source/utility/math.h"

/**
 * Test la fonction tirer_carte, vérifie la validité de la valeur retournée et si chaque carte est bien tirée qu'une seule fois.
 * @test
 */
void test_rand_between() {
	int value;
	value = rand_between(10, 20);
	CU_ASSERT(value >= 10 && value <= 20);
	value = rand_between(0, 5);
	CU_ASSERT(value >= 0 && value <= 5);
	value = rand_between(0, 1);
	CU_ASSERT(value >= 0 && value <= 1);
	CU_ASSERT(rand_between(1, 1) == 1);
}

/**
 * Fonction principale des tests.
 */
int main() {
	CU_pSuite suite_ptr = NULL;//pointeur vers suite de test
	CU_pTest test_ptr = NULL;//pointeur vers test
	if (CU_initialize_registry() == CUE_SUCCESS) {//initialisation
		suite_ptr = CU_add_suite("utilities test", NULL, NULL);//on créé une suite, les deux derniers arguments sont NULL car on ne souhaite pas de fonctions d'initialisation ou de finalisation pour cette suite
		if (suite_ptr != NULL) {//si le pointeur vaut NULL, c'est que la création de la suite de test a échoué
			test_ptr = CU_add_test(suite_ptr, "test rand_between", &test_rand_between);//on créé un test dans la suite,
			if (test_ptr == NULL) {//si le pointeur vaut NULL, c'est que la création du test a échoué
				CU_cleanup_registry();//nettoyage de registre
				return CU_get_error();//on retourne la valeur d'erreur
			}
			CU_basic_run_tests();//tout s'est bien passé, on execute les tests
		}
		CU_cleanup_registry();//nettoyage de registre
	}
	return CU_get_error();//on retourne la valeur d'erreur
}
