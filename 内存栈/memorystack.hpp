#pragma once
#ifndef _MEMORYSTACK_H_
#define _MEMORYSTACK_H_

#include <iostream>
#include <string>
#include <exception>

typedef std::string _string;
typedef int64_t intt;

class MemoryStackException : public std::exception {
private:
	int _EXCEPTION = 0;
	const char* _DEFAULT = "Default EXCEPTION!";
	const char* _STACK_FULL = "Stack is FULL!";							
	const char* _INEXISTENT_MEMORY = "This memory is INEXISTENT!";
public:
	/* param :
	*	exception
	*	0 ：_EXCEPTION		
	*	1 : _STACK_FULL
	*	2 : _INEXISTENT_MEMORY
	*/
	MemoryStackException() {}
	MemoryStackException(int exception_num) { _EXCEPTION = exception_num; }
	const char* what() const {
		switch (_EXCEPTION) {
		case 0: { return _DEFAULT; }
		case 1: { return _STACK_FULL; }
		case 2: { return _INEXISTENT_MEMORY; }
		default: { return "Exception Error!"; }
		}
	}
};

class StructDataException : public std::exception {
private:
	int _EXCEPTION = 0;
	const char* _DEFAULT = "Default EXCEPTION!";
	const char* _NAME_INVALID = "Name is INVALID!";
	const char* _YEAR_INVALID = "Year is INVALID!";
	const char* _DEPART_INVALID = "Depart is INVALID!";
	const char* _ID_INVALID = "ID is INVALID!";
public:
	StructDataException() {}
	StructDataException(int exception_num) { _EXCEPTION = exception_num; }
	const char* what() const {
		switch (_EXCEPTION) {
		case 0: { return _DEFAULT; }
		case 1: { return _NAME_INVALID; }
		case 2: { return _YEAR_INVALID; }
		case 3: { return _DEPART_INVALID; }
		case 4: { return _ID_INVALID; }
		default: { return "Exception Error!"; }
		}
	}
};

struct student {
	intt	s_id = -1;
	intt	s_year = -1;
	_string s_name;
	_string s_depart;
};

struct memoryStack {
	bool is_empty;
	bool is_full;
	student* students;
	intt	 max_size;
	intt	 free_size;
	struct memoryStack* next;
};

typedef student stud;
typedef memoryStack mems;
typedef MemoryStackException _MSE;
typedef StructDataException _SDE;

mems* create_memory_stack(intt);
void init_struct(stud&);
void set_struct_data(stud&, intt, intt, _string, _string);
void init_memory_stack(mems&);
void* find_free_memory(mems&);
void* fetch_memory(mems&);
void* alloc_memory(mems&);
void* find_address(void*, mems&);
void free_struct_data(stud&);
void return_memory(stud*, mems&);
std::ostream& operator<<(std::ostream&, stud&);
std::ostream& operator<<(std::ostream&, stud*);


// 生成内存栈
mems* create_memory_stack(intt q_size) {
	mems* shead = new mems;
	shead->next = NULL;			shead->students = new stud[q_size];
	shead->max_size = q_size;		shead->free_size = q_size;
	shead->is_empty = true;		shead->is_full = false;
	return shead;
}

// 初始化结构体空间
void init_struct(stud& s) {
	s.s_id = -1;		s.s_name = "-1";
	s.s_year = -1;		s.s_depart = "-1";
}

// 填充结构体数据
void set_struct_data(stud& s, intt _id, intt _year, _string _name, _string _depart) throw(...) {
	// 数据合法性检查
	if (_id < 0) throw _SDE(4);
	else if (_year < 1 || _year > 4) throw _SDE(2);
	else if (_name == "") throw _SDE(1);
	else if (_depart == "") throw _SDE(3);
	else {
		s.s_id = _id;		s.s_name = _name;
		s.s_year = _year;	s.s_depart = _depart;
	}
}

// 初始化内存栈空间
void init_memory_stack(mems& s) {
	for (auto i = 0; i < s.max_size; i++) {
		init_struct(s.students[i]);
	}
}

// 查找空地址
void* find_free_memory(mems& s) throw(...) {
	if (s.is_full) throw _MSE(1);
	for (auto i = 0; i < s.max_size; i++) {
		if (s.students[i].s_id == -1) {
			return &(s.students[i]);
		}
	}
	throw _MSE(3);
}

// 从栈中取出空间
void* fetch_memory(mems& s) {
	if (s.is_empty) {
		s.is_empty = !s.is_empty;
	}
	void* fetched_memory = NULL;
	try {
		fetched_memory = find_free_memory(s);
	}
	catch (_MSE& mse) {
		std::cerr << mse.what() << std::endl;
		exit(1);
	}
	if (fetched_memory == NULL) return NULL;
	s.free_size--;
	if (s.free_size == 0) {
		s.is_full = !s.is_full;
	}
	return fetched_memory;
}

// 为新结构体申请空间
void* alloc_memory(mems& s) {
	try {
		if (s.is_full) {
			throw _MSE(1);
		}
		else {
			return fetch_memory(s);
		}
	}
	catch (_MSE& mse) {
		std::cerr << mse.what() << std::endl;
		exit(1);
	}
}

// 查找内存在内存栈中地址
void* find_address(void* address, mems& s) {
	try {
		for (auto i = 0; i < s.max_size; i++) {
			if (address == &s.students[i]) {
				return address;
			}
		}
		throw _MSE(3);
	}
	catch (_MSE& mse) {
		std::cerr << mse.what() << std::endl;
		exit(1);
	}
}

// 释放结构体数据
void free_struct_data(stud& student) {
	init_struct(student);
}

// 释放一个结构体空间内存退回给内存栈
void return_memory(stud* student, mems& s) {
	student = (stud*)find_address(student, s);
	free_struct_data(*student);
	if (s.is_full) s.is_full = !s.is_full;
	s.free_size++;
	if (s.free_size == s.max_size) s.is_empty = !s.is_empty;
}

// 输出结构体
std::ostream& operator<<(std::ostream& os, stud& s) throw(...) {
	int left = 14, right = 3;
	try {
		if (s.s_id < 0) throw _SDE(4);
		else if (s.s_year < 1 || s.s_year > 4) throw _SDE(2);
		else if (s.s_name == "") throw _SDE(1);
		else if (s.s_depart == "") throw _SDE(3);
		else {
			os << "*----*----*----*----*" << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "ID" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s.s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "NAME" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s.s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "DEPARTMENT" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s.s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "YEAR" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s.s_id << std::endl;
			os << "*----*----*----*----*" << std::endl;
		}
	}
	catch (_SDE& sde) {
		std::cerr << sde.what() << std::endl;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, stud* s) throw(...) {
	int left = 14, right = 3;
	try {
		if (s->s_id < 0) throw _SDE(4);
		else if (s->s_year < 1 || s->s_year > 4) throw _SDE(2);
		else if (s->s_name == "") throw _SDE(1);
		else if (s->s_depart == "") throw _SDE(3);
		else {
			os << "*----*----*----*----*" << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "ID" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s->s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "NAME" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s->s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "DEPARTMENT" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s->s_id << std::endl;
			os.flags(std::ios::left);
			os.width(left);
			os << "YEAR" << " : ";
			os.flags(std::ios::right);
			os.width(right);
			os << s->s_id << std::endl;
			os << "*----*----*----*----*" << std::endl;
		}
	}
	catch (_SDE& sde) {
		std::cerr << sde.what() << std::endl;
	}
	return os;
}
#endif