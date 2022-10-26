#include "memorystack.hpp"

using namespace std;

int main() {

	mems* _stack = create_memory_stack(4);
	init_memory_stack(*_stack);
	stud* s1 = (stud*)alloc_memory(*_stack);
	init_struct(*s1);
	

	stud* s2 = (stud*)alloc_memory(*_stack);
	init_struct(*s2);
	stud* s3 = (stud*)alloc_memory(*_stack);
	init_struct(*s3);
	stud* s4 = (stud*)alloc_memory(*_stack);
	init_struct(*s4);

	cout << s1 << endl;
	cout << s2 << endl; 
	cout << s3 << endl; 
	cout << s4 << endl;

	int id = 201, year = 3;
	string dep = "CS", name = "Tom";
	set_struct_data(*s1, id, year, name, dep);
	cout << s1 << endl;
	/*stud* s5 = (stud*)alloc_memory(*_stack);
	init_struct(*s5);*/

	return_memory(s1, *_stack);
	cout << s1 << endl;

	return 0;
}