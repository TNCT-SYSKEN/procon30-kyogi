#include"Field.h"

Field* Field::field = nullptr;

Field* Field::getField() {
	if (field == nullptr) {
		field = new Field;
	}
	return field;
}