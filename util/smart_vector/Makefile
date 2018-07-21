CFLAGS    := -DCHECK_INTERFACE -DDEBUG -Wall -Wextra -Werror -O2 -g
BUILD_DIR := .

define run_test
	@printf "\033[1;31m"${2}"\033[0m\n"
	g++ -DVERSION_TO_TEST=${1} ${CFLAGS} -o ${BUILD_DIR}/test smart_vector_test.cpp
	${BUILD_DIR}/test
	rm ${BUILD_DIR}/test
endef

.PHONY: test
test: test_linear test_sqrt test_log

.PHONY: test_linear
test_linear:
	$(call run_test,1,"O(n) version")

.PHONY: test_sqrt
test_sqrt:
	$(call run_test,2,"O(sqrt(n)) version")

.PHONY: test_log
test_log:
	$(call run_test,3,"O(log(n)) version")
