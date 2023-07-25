/*
Name: Miguel Santoscoy
Class: CS 216, Wed 5:40
  */

#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <locale>  //for formatting currrency.

using namespace std;



//_______Function Protos____________
void populateSales(string st, string* stPtr);
void writeFile(ofstream& outFile, string* st, float* num);
//__________________________________

ifstream salesP("Sales Person Dat.txt");
string salesPerson ="Sales Person Dat.txt";
int const salesPeopleTotal = 6;

int main() {

	string fileName{ "Data for Project 7.txt" }, line;
	ifstream inFile(fileName); //File contains sales datda.
	getline(inFile, line);    //Skip the first line of the file inFile.
	line = "";

	  //Sales Person data
	getline(salesP, line);    //Skip the first line of the file salesP.
	line = "";
  
	ofstream outFile("Output for Project 7.txt");  //Create an output file.

	const size_t num{ 10 };
	string salesName[num];
	string* salesPtr;
	salesPtr = salesName;	//Pointer to the array salesName[].

	//Populate the array salesName;
	getline(salesP, line);    //Remove the first line of the file inFile.
	line = "";

	/////////////////////////////////////////////////////////////////////////////////////
	//HERE IS THE populateSales FUNCTION
	/////////////////////////////////////////////////////////////////////////////////////

 populateSales(salesPerson, salesPtr);
  
	double ttlUnt{ 0 }, ttlAmt{ 0 }, ttlProf{ 0 }, ttlCom{ 0 }, ttlNCom{ 0 }, ttlSal{ 0 };

	if (inFile.is_open())
	{
		cout << "\n" << setw(15) << "Date" << setw(15) << "Unit Type" << setw(15)
			<< "Sales Person" << setw(15) << "Units Sold" << setw(15) << "Cost/Unit"
			<< setw(15) << "Sales Total" << setw(15) << "Profits" << endl;

		outFile << "\n" << setw(15) << "Date" << setw(15) << "Unit Type" << setw(15)
			<< "Sales Person" << setw(15) << "Units Sold" << setw(15) << "Cost/Unit"
			<< setw(15) << "Sales Total" << setw(15) << "Profits" << endl;

		float ttlUnt{ 0 };	//Total number of units sold.
int const ValNumMax = 7;
		while (getline(inFile, line))     //Parse data from the Data  for Project 7.txt file
		{
			string val[ValNumMax];
			float num[ValNumMax];
			stringstream inputString(line);

string* ptrVal = val;
float* ptrNum = num;

			getline(inputString, val[0], ',');
			getline(inputString, val[1], ',');

for(int i=0; i< salesPeopleTotal ; i++)
  {
  string emplNum = to_string(i);
  if(val[1]== emplNum)
  {
  val[1] = *(salesPtr+ i);
  }
  }


			getline(inputString, val[2], ',');
			num[2] = atof(val[2].c_str());
			getline(inputString, val[3], ',');
			num[3] = atof(val[3].c_str());
			getline(inputString, val[4], ',');
			num[4] = atof(val[4].c_str());
			getline(inputString, val[5], ',');
			num[5] = atof(val[5].c_str());
			getline(inputString, val[6], ' ');
			num[6] = atof(val[6].c_str());

			ttlUnt += num[3];  //get total units sold.

			//Get total amount sold and profits.
			if (num[3] * num[4] > 1000) {
				ttlAmt += num[3] * num[4] - (num[3] * num[4]) * 0.10;
				ttlProf += num[3] * num[4] - ((num[3] * num[4]) * 0.10) * 0.25;
			}
			else {
				ttlAmt += num[3] * num[4];
				ttlProf += num[3] * num[4] * 0.25;
			}

			if (val[1] == "0")      //Find total Commercial sales
				ttlCom += num[3];
			if (val[1] == "1")       //Find total NonCommercial sales
				ttlNCom += num[3];

			//Data for column 6 and column 7.
			if (num[3] * num[4] > 10000) {       //Discount for any purchase that is more than $10,000.
				num[5] = num[3] * num[4] - (num[3] * num[4]) * 0.10;			//Total sales minus 10% discount.
				num[6] = (num[3] * num[4] - num[3] * num[4] * 0.10) * 0.25;    //.Total profits.
			}
			else {   //No discount for any purchase < $10,000.
				num[5] = num[3] * num[4];
				num[6] = num[3] * num[4] * 0.25;
			}

			cout << setw(15) << val[0] << setw(15) << val[2] << setw(15) << val[1] << setw(15) << num[3] <<
				setw(15) << num[4] << setw(15) << num[5] << setw(15) << num[6] << endl;

      for(int i=0; i< ValNumMax; i++)
        {
          *(ptrVal+i)= val[i];
          *(ptrNum + i)=num[i];
        }
			if (outFile.is_open())
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////
        //HERE IS THE writeFile FUNCTION
       writeFile(outFile, ptrVal, ptrNum);
			}
			line = "";
		}//END of WHILE
//	}//END of IF

	//For currency formatting
		cout.imbue(locale("ENGLISH_US"));  //Set up for currency formatting, indicating that the locale is U.S.
		cout << showbase;
		cout << fixed << showpoint << setprecision(2);  //Set 2 decimals precision.
		cout << endl;
		cout << setw(15) << "==========" << setw(15) << "==========" << setw(15) << "==========" << setw(15) << "==========" << setw(15) << "==========" << setw(15) << "==========" << setw(15) << "==========" << endl;

		cout.imbue(locale("ENGLISH_US"));  //Set up for currency formatting, indicating that the locale is U.S.
		cout << showbase;

		cout << fixed << showpoint << setprecision(2);  //Set 2 decimals precision.
		cout << setw(45) << " " << setw(15) << ttlUnt << setw(15) << "" << setw(15) << put_money(ttlAmt * 100) << setw(15) << put_money(ttlProf * 100) << endl;
	}//END of IF

	outFile.close();
	return 0;
}

//______Function Definitions_________

//parses through data, assigns names if salespeople to pointers
void populateSales(string st, string* stPtr)
{
  string line;
  ifstream salesP(st);  //Sales Person data
	getline(salesP, line);    //Skip the first line of the file salesP.
	line = "";

  int lineCount = 0;
while (!salesP.eof())
  {
string salesNameInfo;
  getline(salesP, salesNameInfo);
  unsigned first = salesNameInfo.find(' ');
unsigned last = salesNameInfo.rfind(',');
string name = salesNameInfo.substr(first, last-first);

   
    *(stPtr + lineCount) = name;
 
    lineCount++;
     
  }

}

//takes pointers, writes the value stored in pointer to file
void writeFile(ofstream& outFile, string* st, float* num)
{
  outFile << setw(15) << *st << setw(15) << *(st+2) <<
					setw(15) << *(st+1) << setw(15) << *(num+3) <<
					setw(15) << *(num+4) << setw(15) << *(num+5)
					<< setw(15) <<*(num+6) << endl;

}