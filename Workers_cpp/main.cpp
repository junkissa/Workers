#include"fstream"
#include"iostream"
#include"string"
#include"Workers.h"
#include"vector"
#include"memory"
#include "sstream"
using namespace std;

vector<Worker> sortSalary(const vector<Worker> & old);
bool outFile(string fileName, vector<shared_ptr<Worker>> & outWorkers);
bool inFile(string fileName, vector<Worker> & inWorkers);
bool outFile(string fileName, vector<shared_ptr<Worker>> & outWorkers, int N, int fromTop1_or_fromBottom0); 





vector<shared_ptr<Worker>> sortSalary(const vector<shared_ptr<Worker>> & old)
{
	vector<shared_ptr<Worker>> res;
	int N = old.size();
	int place = 0;
	for (int i = 0; i < N; ++i)
	{
		res.push_back(old[i]);
		for (int j = i - 1; j >= 0; --j)
		{

			if (old[i]->getAverSalary() > res[j]->getAverSalary())
			{
				res[j + 1] = res[j];
				place = j;
			}

			else if (old[i]->getAverSalary() < res[j]->getAverSalary())
			{
				place = j + 1;
				break;
			}

			// ñîðòèðîâêà ïî ôàìèëèè
			else if (old[i]->getAverSalary() == res[j]->getAverSalary())
			{
				res[j + 1] = old[i];
				for (int k = 0; k < (old[i]->getLastName()).size() && k < (res[j]->getLastName()).length(); ++k)
				{
					if ((old[i]->getLastName())[k] == (res[j]->getLastName())[k]) // ñîâïàäàþùèå áóêâ³ â íà÷àëå ôàìèëèè
						continue;

					else if ((old[i]->getLastName())[k] >(res[j]->getLastName())[k]) // åñëè ñîðòèðóåìûé îáúåêò ïîçæå â ñïèñêå,
					{
						place = j + 1;
						break;
					}														  // ïðîñòî âûõîäèì òàê êàê ìû åãî óæå ïîñòàâèëè íà ìåñòî j+1

					else if ((old[i]->getLastName())[k] < (res[j]->getLastName())[k]) // åñëè ñîðòèðóåìûé îáúåêò ðàíüøå â ñïèñêå, ïåðåìåùàåì
					{
						res[j + 1] = res[j];
						place = j;
						break;
					}
				}

				break;
			}

		}
		res[place] = old[i];

	}

	return res;
}


bool inFile(string fileName, vector<shared_ptr<Worker>> & inWorkers)
{
	ifstream fi;
	fi.open(fileName);
	if (!fi)
	{
		cout << "Input File Error\n";
		return false;
	}

	char type;
	double tempID;
	string tempFirstName;
	string tempLastName;
	double tempSalary;

	string strLine;
	vector<string> vectorOfLines;

	while (getline(fi, strLine)) // êîïèðóåì ñòðîêè èç ôàéëà â ìàññèâ vectorOfLines
	{
		vectorOfLines.push_back(strLine);
	}

	int N = vectorOfLines.size();
	for (int i = 0; i < N; ++i) // äëÿ êàæäîé ñòðîêè-èíôîðìàöèè ïðî ðàáîòíèêà ñ÷èòûâàåì è ïðîâåðÿåì èíôîðìàöèþ
	{
		string strStream = vectorOfLines[i];
		istringstream iss(strStream);
		if (!(iss >> type))
		{
			"File doesn't consist full information about worker\n";

		}
		if (type != 'H' && type != 'M')
		{
			cout << "Input File Error: Type of worker is wrong, must be H or M\n";
			return false;
		}

		if (!(iss >> tempID))
		{
			cout << "File doesn't consist full information about worker\n";
			return false;
		}

		if (tempID != int(tempID) || tempID < 0)
		{
			cout << "Input File Error: ID is wrong, it must be uint\n";
			return false;
		}

		if (!(iss >> tempFirstName))
		{
			cout << "File doesn't consist full information about worker\n";
			return false;
		}

		if (!(iss >> tempLastName))
		{
			cout << "File doesn't consist full information about worker\n";
			return false;
		}

		if (!(iss >> tempSalary))
		{
			cout << "File doesn't consist full information about worker\n";
			return false;
		}


		if (type == 'H') // äîáàâëÿåì ðàáîòíèêà â êîëëåêöèþ ðàáîòíèêîâ
		{
			shared_ptr<WorkerPerHour> workerH(new WorkerPerHour((int)tempID, tempFirstName, tempLastName, tempSalary));
			shared_ptr<Worker> workerHbase = static_pointer_cast<Worker>(workerH);
			inWorkers.push_back(workerHbase);
		}
		else // type == M
		{
			shared_ptr<WorkerPerMonth> workerM(new WorkerPerMonth((int)tempID, tempFirstName, tempLastName, tempSalary));
			shared_ptr<Worker> workerMbase = static_pointer_cast<Worker>(workerM);
			inWorkers.push_back(workerMbase);
		}
	}
	return true;
}



bool outFile(string fileName, vector<shared_ptr<Worker>> & outWorkers)
{
	ofstream fo;
	fo.open(fileName);
	int N = outWorkers.size();
	if (!fo)
	{
		cout << "Output File Error\n";
		return false;
	}
	fo.setf(ios::left);
	fo.width(8);	fo << "ID";
	fo.width(12);   fo << "First Name";
	fo.width(16);	fo << "Last Name";
	fo.width(10);   fo << "Salary";
	fo << endl;

	for (int i = 0; i < N; ++i)
	{
		fo.setf(ios::left);
		fo.width(8);	fo << outWorkers[i]->getID();
		fo.width(12);   fo << outWorkers[i]->getFirstName();
		fo.width(16);	fo << outWorkers[i]->getLastName();
		fo.width(10);   fo << outWorkers[i]->getAverSalary();
		fo << endl;
	}
	cout << "Output File is OK\n";
	fo.close();
	return true;
}



bool outFile(string fileName, vector<shared_ptr<Worker>> & outWorkers, int N, int fromTop1_or_fromBottom0)
{
	// âûâåñòè â ôàéë N ïåðâûõ (ïàðàìåòð == 1) èëè ïîñëåäíèõ (ïàðàìåòð == 0) ñîòðóäíèêîâ
	ofstream fo;
	fo.open(fileName);
	if (N > outWorkers.size())
		N = outWorkers.size();
	int NofVector = outWorkers.size();

	if (!fo)
	{
		cout << "Output File Error\n";
		return false;
	}
	fo.setf(ios::left);
	fo.width(8);	fo << "ID";
	fo.width(12);   fo << "First Name";
	fo.width(16);	fo << "Last Name";
	fo.width(10);   fo << "Salary";
	fo << endl;
	if (fromTop1_or_fromBottom0 == 1)
	{
		for (int i = 0; i < N; ++i)
		{
			fo.width(8);	fo << outWorkers[i]->getID();
			fo.width(12);   fo << outWorkers[i]->getFirstName();
			fo.width(16);	fo << outWorkers[i]->getLastName();
			fo.width(10);   fo << outWorkers[i]->getAverSalary();
			fo << endl;
		}
	}
	else if (fromTop1_or_fromBottom0 == 0)
	{
		for (int i = NofVector - 1; i >= NofVector - N; --i)
		{
			fo.width(8);	fo << outWorkers[i]->getID();
			fo.width(12);   fo << outWorkers[i]->getFirstName();
			fo.width(16);	fo << outWorkers[i]->getLastName();
			fo.width(10);   fo << outWorkers[i]->getAverSalary();
			fo << endl;

		}
	}
	else
	{
		cout << "Wrong parameter for outFile - fromTop1_or_fromBottom0 must be 1 or 0\n";
		return false;
	}
	cout << "Output File is OK\n";
	fo.close();
	return true;

}

int main()
{
	string outFcopy = "outCopy.txt";
	string outFsorted = "outSorted.txt";
	string outFromTop = "outFromTop.txt";
	string outFromBottom = "outFromBottom.txt";

	string inF = "in.txt";

	vector<shared_ptr<Worker>> workers;
	if (inFile(inF, workers))
		outFile(outFcopy, workers);
	vector<shared_ptr<Worker>> sorted;
	sorted = sortSalary(workers);
	outFile(outFsorted, sorted);
	outFile(outFromTop, sorted, 5, 1);
	outFile(outFromBottom, sorted, 5, 0);


	system("pause");
	return 0;
}

