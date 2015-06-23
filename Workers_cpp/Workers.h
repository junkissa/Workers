#include<string>
using namespace std;

class Worker
{
private:
	int ID;
	string firstName;
	string lastName;
	double averSalary;
public:
	Worker() {}
	Worker(int ID_, string firstName_, string lastName_, double salary_);
	Worker(int ID_, string firstName_, string lastName_);
	Worker(const Worker & old);
	int getID() const;
	string getFirstName() const;
	string getLastName() const;
	double getAverSalary() const;
	void setAverSalary(double salary_);
	virtual double countSalary() = 0;
};

class WorkerPerHour : public Worker
{
private:
	double hourly_rate;
public:
	WorkerPerHour() {}
	WorkerPerHour(int ID_, string firstName_, string lastName_, double hourly_rate_);
	double countSalary();

};

class WorkerPerMonth : public Worker
{
private:
	double month_rate;
public:
	WorkerPerMonth(){}
	WorkerPerMonth(int ID_, string firstName_, string lastName_, double month_rate_);
	double countSalary();
};