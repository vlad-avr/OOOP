#include "Dice.h"
#include "doctest.h"

TEST_CASE("auto_ generation and getting faces") {
	Dice dice(4);
	dice.auto_gen(0, 4);
	CHECK(dice.face_count() == 4);
	Dice::Face* face = dice.get_face(0);
	CHECK(face->val >= 0);
	CHECK(face->val <= 4);
	CHECK(face->possib >= 0);
	CHECK(face->possib <= 1);
}


