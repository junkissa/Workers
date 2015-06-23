#include"Workers.h"
#include"string"
using namespace std;



Worker::Worker(int ID_, string firstName_, string lastName_, double salary_) : ID(ID_), firstName(firstName_), lastName(lastName_), averSalary(salary_){}

Worker::Worker(int ID_, string firstName_, string lastName_) : ID(ID_), firstName(firstName_), lastName(lastName_) { averSalary = 0; }

Worker::Worker(const Worker & old) : ID(old.ID), firstName(old.firstName), lastName(old.lastName){}

int Worker::getID() const { return ID; }

string Worker::getFirstName() const { return firstName; }

string Worker::getLastName() const { return lastName; }

double Worker::getAverSalary() const { return averSalary; }

void::Worker::setAverSalary(double salary_) { averSalary = salary_; }


WorkerPerHour::WorkerPerHour(int ID_, string firstName_, string lastName_, double hourly_rate_) : Worker(ID_, firstName_, lastName_), hourly_rate(hourly_rate_){ setAverSalary(countSalary()); }

double WorkerPerHour::countSalary()
{
		return 20.8 * 8 * hourly_rate;
}


WorkerPerMonth::WorkerPerMonth(int ID_, string firstName_, string lastName_, double month_rate_) : Worker(ID_, firstName_, lastName_), month_rate(month_rate_){ setAverSalary(countSalary()); }

double WorkerPerMonth::countSalary()
{
		return month_rate;
}