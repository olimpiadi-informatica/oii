#if VERSION_TO_TEST == 1
#include "smart_vector_very_slow.hpp"
#elif VERSION_TO_TEST == 2
#include "smart_vector_slow.hpp"
#elif VERSION_TO_TEST == 3
#include "smart_vector_fast.hpp"
#endif

#define smart_vector_abs smart_vector_with_magic
#define smart_vector smart_vector_with_more_magic

#undef ASD_SMART_VECTOR_HPP
#include "smart_vector.hpp"
#undef ASD_SMART_VECTOR_VERY_SLOW_HPP
#include "smart_vector_very_slow.hpp"

#undef smart_vector
#undef smart_vector_abs

namespace testing {
template <typename T>
using smart_vector = ::smart_vector_with_more_magic<T>;
}

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define test(x) if (!(x)) { logError({__FUNCTION__, #x, "", __LINE__}); return; } else { logSuccess(); }
#define test_msg(x, msg) if (!(x)) { logError({__FUNCTION__, #x, msg, __LINE__}); return; } else { logSuccess(); }

struct error {
	std::string test;
	std::string assertation;
	std::string msg;
	int line;
};
std::vector<error> errors;
int test_count = 0;
void logError(error err) {
	errors.push_back(err);
	std::cerr << "F " << err.test << " " << err.msg << " " << err.assertation << std::endl;
	test_count++;
}
void logSuccess() {
	test_count++;
}


typedef smart_vector<int> svi;

svi gen_svi(int size) {
	svi vec;
	for (int i = 0; i < size; i++)
		vec.push_back(i+1);
	return vec;
}

void test_front(svi vec) { test(vec[0] == vec.front()); }
void test_back(svi vec) { test(vec[vec.size()-1] == vec.back()); }
void test_get(svi vec) {
	std::size_t size = vec.size();
	for (int i = 0; i < (int)size; i++)
		test(vec[i] == i+1);
}
void test_push_back(svi vec) {
	std::size_t size = vec.size();
	vec.push_back(-42);
	test(-42 == vec.back());
	test_msg(size+1 == vec.size(), "Size not updated");
}
void test_push_front(svi vec) {
	std::size_t size = vec.size();
	vec.push_front(-42);
	test(-42 == vec.front());
	test_msg(size+1 == vec.size(), "Size not updated");
}
void test_pop_back(svi vec) {
	std::size_t size = vec.size();
	int prev = vec.back();
	test(prev == vec.pop_back());
	test(vec.back() != prev)
	test_msg(size-1 == vec.size(), "Size not updated");
}
void test_pop_front(svi vec) {
	std::size_t size = vec.size();
	int prev = vec.front();
	test(prev == vec.pop_front());
	test(vec.front() != prev)
	test_msg(size-1 == vec.size(), "Size not updated");
}
void test_erase(svi vec) {
	std::size_t size = vec.size();
	int pos = rand() % (size - 1);
	int prev = vec[pos];
	test(prev == vec.erase(pos));
	test(prev != vec[pos]);
	test_msg(size-1 == vec.size(), "Size not updated");
}
void test_erase_front(svi vec) {
	std::size_t size = vec.size();
	int prev = vec.front();
	test(prev == vec.erase(0));
	test(prev != vec.front());
	test_msg(size-1 == vec.size(), "Size not updated");
}
void test_erase_back(svi vec) {
	std::size_t size = vec.size();
	int prev = vec.back();
	test(prev == vec.erase(size-1));
	test(prev != vec.back());
	test_msg(size-1 == vec.size(), "Size not updated");
}
void test_split(svi vec) {
	std::size_t size = vec.size();
	std::size_t pos = rand() % (size-2) + 1;
	svi vec2 = vec.split(pos);
	test_msg(pos == vec.size(), "first chunk has wrong size");
	test_msg((size - pos) == vec2.size(), "second chunk has wrong size");
	for (int i = 0; i < (int)pos; i++)
		test(i+1 == vec[i]);
	for (int i = 0; i < (int)(size - pos); i++)
		test(i+(int)pos+1 == vec2[i]);
}
void test_split_front(svi vec) {
	std::size_t size = vec.size();
	std::size_t pos = 0;
	svi vec2 = vec.split(pos);
	test_msg(pos == vec.size(), "first chunk has wrong size");
	test_msg((size - pos) == vec2.size(), "second chunk has wrong size");
	for (int i = 0; i < (int)pos; i++)
		test(i+1 == vec[i]);
	for (int i = 0; i < (int)(size - pos); i++)
		test(i+(int)pos+1 == vec2[i]);
}
void test_split_back(svi vec) {
	std::size_t size = vec.size();
	std::size_t pos = size;
	svi vec2 = vec.split(pos);
	test_msg(pos == vec.size(), "first chunk has wrong size");
	test_msg((size - pos) == vec2.size(), "second chunk has wrong size");
	for (int i = 0; i < (int)pos; i++)
		test(i+1 == vec[i]);
	for (int i = 0; i < (int)(size - pos); i++)
		test(i+(int)pos+1 == vec2[i]);
}
void test_append(svi vec) {
	const std::size_t OTHER_SIZE = 10;
	std::size_t size = vec.size();
	svi vec2 = gen_svi(OTHER_SIZE);
	vec.append(vec2);
	test_msg(vec.size() == size + OTHER_SIZE, "size not added correctly");
	test_msg(vec2.size() == 0, "other vector is not empty");
	for (int i = 0; i < (int)size; i++)
		test(vec[i] == i+1);
	for (int i = 0; i < (int)OTHER_SIZE; i++)
		test(vec[i+size] == i+1);
}
void test_append_empty(svi vec) {
	std::size_t size = vec.size();
	svi vec2;
	vec.append(vec2);
	test(vec.size() == size);
	test(vec2.size() == 0);
	for (int i = 0; i < (int)size; i++)
		test(vec[i] == i+1);
}
void test_reverse(svi vec) {
	std::size_t size = vec.size();
	vec.reverse();
	test(vec.size() == size);
	for (int i = 0; i < (int)size; i++)
		test(vec[i] == (int)size-i);
}

void process_svi(svi& vec, testing::smart_vector<int>& safe, int deep = 5) {
	if (deep <= 0) return;
	const int OPERATIONS = 10;
	for (int i = 0; i < OPERATIONS; i++) {
		int op = rand() % 100;
		if (op < 10) {
			int val = rand() % 1000000000;
			safe.push_back(val);
			vec.push_back(val);
			test(safe.size() == vec.size());
		} else if (op < 20) {
			int val = rand() % 1000000000;
			safe.push_front(val);
			vec.push_front(val);
			test(safe.size() == vec.size());
		} else if (op < 30) {
			if (safe.size() > 0) {
				safe.pop_back();
				vec.pop_back();
			}
		} else if (op < 40) {
			if (safe.size() > 0) {
				safe.pop_front();
				vec.pop_front();
			}
		} else if (op < 60) {
			if (safe.size() > 0) {
				int index = rand() % (safe.size() + 1);
				auto safe_ret = safe.split(index);
				auto vec_ret = vec.split(index);
				for (int i = 0; i < index; i++)
					test(safe[i] == vec[i]);
				int other_size = safe_ret.size();
				for (int i = 0; i < other_size; i++)
					test(safe_ret[i] == vec_ret[i]);
			}
		} else if (op < 80) {
			const int TAIL_LENGTH = log2(safe.size());
			svi tail1;
			testing::smart_vector<int> tail2;
			for (int i = 0; i < TAIL_LENGTH; i++) {
				int val = rand() % 1000000000;
				tail1.push_back(val);
				tail2.push_back(val);
			}
			process_svi(tail1, tail2, deep-1);
			vec.append(tail1);
			safe.append(tail2);
		} else if (op < 100) {
			vec.reverse();
			safe.reverse();
		}
	}
}

void test_random_ops(svi vec) {
	const int OPERATIONS = 1000;
	testing::smart_vector<int> safe;
	std::size_t size = vec.size();
	for (int i = 0; i < (int)size; i++)
		safe.push_back(vec[i]);

	for (int i = 0; i < OPERATIONS; i++) {
		int op = rand() % 100;
		if (op < 30) {
			if (safe.size() > 0) {
				int index = rand() % safe.size();
				test(safe[index] == vec[index]);
			}
		} else {
			process_svi(vec, safe);
		}
	}
}

std::vector<void(*)(svi)> tests = {
	test_front, test_back, test_get,
	test_push_back, test_push_front,
	test_pop_back, test_pop_front,
	test_erase, test_erase_front, test_erase_back,
	test_split, test_split_front, test_split_back,
	test_append, test_append_empty,
	test_reverse,

	test_random_ops
};
std::vector<int> test_sizes = { 3, 10, 100 };

void run() {
	for (int test_size : test_sizes) {
		std::cerr << "\nTesting size " << test_size << " ";
		for (auto test_func: tests) {
			test_func(gen_svi(test_size));
		}
	}
}

int main() {
	run();
	std::cerr << std::endl;
	std::cerr << (test_count-errors.size()) << "/" << test_count << " asserts passed" << std::endl;
	if (!errors.empty()) {
		std::cerr << "Errors:" << std::endl;
		for (error err : errors) {
			std::cerr << "Test " << err.test << " failed" << std::endl;
			std::cerr << "    " << err.assertation << " at line " << err.line << std::endl;
			if (!err.msg.empty())
				std::cerr << "    " << err.msg << std::endl;
		}
	}
	if (errors.size() == 0)
		return 0;
	return 1;
}
