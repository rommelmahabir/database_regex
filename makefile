database: department.o departments.o employee.o employees.o main.o project.o projects.o
		g++ department.o departments.o employee.o employees.o main.o project.o projects.o -o output

department.o: department.cpp department.h
		g++ -c department.cpp department.h

departments.o: departments.cpp departments.h
		g++ -c departments.cpp departments.h

employee.o: employee.cpp employee.h
		g++ -c employee.cpp employee.h

employees.o: employees.cpp employees.h
		g++ -c employees.cpp employees.h

main.o: main.cpp
		g++ -c main.cpp

project.o: project.cpp project.h
		g++ -c project.cpp project.h

projects.o: projects.cpp projects.h
		g++ -c projects.cpp projects.h

run:
		make
		./output

clean:
	 	rm *.gch *.o output
