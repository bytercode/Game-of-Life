#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED
#include "toroidal_array.h"

typedef struct conwaysgol
{
	int survive_rules, born_rules;
	int wrap;
	toroidal_array_2d_t toroidal_array;
} conwaysgol_t;

enum cgol_rules
{
	CGR_ZERO = 1,
	CGR_ONE = 2,
	CGR_TWO = 4,
	CGR_THREE = 8,
	CGR_FOUR = 16,
	CGR_FIVE = 32,
	CGR_SIX = 64,
	CGR_SEVEN = 128,
	CGR_EIGHT = 256
};

enum cgol_predefined_surviverules
{
	CGOL_PDSR_AMOEBA = (int)(CGR_ONE | CGR_THREE | CGR_FIVE | CGR_EIGHT),
	CGPL_PDSR_ASIMILLATION = (int)(CGR_FOUR | CGR_FIVE | CGR_SIX | CGR_SEVEN),
	CGOL_PDSR_COAGULATIONS = (int)(CGR_TWO | CGR_THREE | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_CONWAYS_LIFE = (int)(CGR_TWO | CGR_THREE),
	CGOL_PDSR_CORAL = (int)(CGR_FOUR | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_DAY_AND_NIGHT = (int)(CGR_THREE | CGR_FOUR | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_DUAMOEBA = (int)(CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_FLAKES = (int)(CGR_ZERO | CGR_ONE | CGR_TWO | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_GNARL = (int)(CGR_ONE),
	CGOL_PDSR_HIGH_LIFE = (int)(CGR_TWO | CGR_THREE),
	CGOL_PDSR_INVERSE_LIFE = (int)(CGR_THREE | CGR_FOUR | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_LONG_LIFE = (int)(CGR_FIVE),
	CGOL_PDSR_MAZE = (int)(CGR_ONE | CGR_TWO | CGR_THREE | CGR_FOUR | CGR_FIVE),
	CGOL_PDSR_MAZECTRIC = (int)(CGR_ONE | CGR_TWO | CGR_THREE | CGR_FOUR),
	CGOL_PDSR_MOVE = (int)(CGR_TWO | CGR_FOUR | CGR_FIVE),
	CGOL_PDSR_PSEUDO_LIFE = (int)(CGR_TWO | CGR_THREE | CGR_EIGHT),
	CGOL_PDSR_REPLICATOR = (int)(CGR_ONE | CGR_THREE | CGR_FIVE | CGR_SEVEN),
	CGOL_PDSR_SEEDS = 0,
	CGOL_PDSR_SERVIETTES = 0,
	CGOL_PDSR_STAINS = (int)(CGR_TWO | CGR_THREE | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDSR_WALLED_CITIES = (int)(CGR_TWO | CGR_THREE | CGR_FOUR | CGR_FIVE)
};

enum cgol_predefined_bornrules
{
	CGOL_PDBR_AMOEBA = (int)(CGR_THREE | CGR_FIVE | CGR_SEVEN),
	CGOL_PDBR_ASIMILLATION = (int)(CGR_THREE | CGR_FOUR | CGR_FIVE),
	CGOL_PDBR_COAGULATIONS = (int)(CGR_THREE | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDBR_CONWAYS_LIFE = (int)(CGR_THREE),
	CGOL_PDBR_CORAL = (int)(CGR_THREE),
	CGOL_PDBR_DAY_AND_NIGHT = (int)(CGR_THREE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDBR_DIAMOEBA = (int)(CGR_THREE | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDBR_FLAKES = (int)(CGR_THREE),
	CGOL_PDBR_GNARL = (int)(CGR_ONE),
	CGOL_PDBR_HIGH_LIFE = (int)(CGR_THREE | CGR_SIX),
	CGOL_PDBR_INVERSE_LIFE = (int)(CGR_ZERO | CGR_ONE | CGR_TWO | CGR_THREE | CGR_FOUR | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDBR_LONG_LIFE = (int)(CGR_THREE | CGR_FOUR | CGR_FIVE),
	CGOL_PDBR_MAZE = (int)(CGR_THREE),
	CGOL_PDBR_MAZECTRIC = (int)(CGR_THREE),
	CGOL_PDBR_MOVE = (int)(CGR_THREE | CGR_SIX | CGR_EIGHT),
	CGOL_PDBR_PSEUDO_LIFE = (int)(CGR_THREE | CGR_FIVE | CGR_SEVEN),
	CGOL_PDBR_REPLICATOR = (int)(CGR_ONE | CGR_THREE | CGR_FIVE | CGR_SEVEN),
	CGOL_PDBR_SEEDS = (int)(CGR_TWO),
	CGOL_PDBR_SERVIETTES = (int)(CGR_TWO | CGR_THREE | CGR_FOUR),
	CGOL_PDBR_STAINS = (int)(CGR_THREE | CGR_SIX | CGR_SEVEN | CGR_EIGHT),
	CGOL_PDBR_WALLED_CITIES = (int)(CGR_FOUR | CGR_FIVE | CGR_SIX | CGR_SEVEN | CGR_EIGHT)
};

int cgol_init(conwaysgol_t *cgol, ssize_t width, ssize_t height);
int cgol_resize(conwaysgol_t *cgol, ssize_t new_width, ssize_t new_height, char fill);

void cgol_ssetat(conwaysgol_t *cgol, char setchr, ssize_t x, ssize_t y);
char cgol_sgetat(const conwaysgol_t *cgol, ssize_t x, ssize_t y);

unsigned cgol_get_alive_count_at(const conwaysgol_t *cgol, ssize_t x, ssize_t y);
char cgol_determine_next_state_at(const conwaysgol_t *cgol, ssize_t x, ssize_t y);
char cgol_next_generation_at(conwaysgol_t *cgol, ssize_t x, ssize_t y);
int cgol_get_next_generatin_ta2d(const conwaysgol_t *cgol, toroidal_array_2d_t *nextgen);
int cgol_next_generation(conwaysgol_t *cgol);

int cgol_add_rule_to_int(enum cgol_rules rule, int theint);
int cgol_remove_rule_from_int(enum cgol_rules rule, int theint);
int cgol_rule_contains(int theint, enum cgol_rules rule);

void cgol_destroy(conwaysgol_t *cgol);

#endif
