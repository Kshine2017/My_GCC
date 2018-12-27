
#include "stdafx.h"
#include "student.h"
#include "stucontrol.h"
#include <stdlib.h>
int main(void)
{
	StuLink* head = (StuLink*)calloc(1,sizeof(StuLink));
	f_load_student_message(head);
	main_menu_control(head);
	return 0;
}
