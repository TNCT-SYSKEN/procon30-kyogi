#include"JsonOption.h"
JsonOption* JsonOption::Option = nullptr;

JsonOption* JsonOption::getJsonOption() {
	if (Option == nullptr) {
		Option == new JsonOption;
	}
}