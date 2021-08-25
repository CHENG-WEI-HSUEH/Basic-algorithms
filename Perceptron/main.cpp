#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
#define DATA_NUMBER 100
#define eta 0.1
typedef struct
{
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;	
	int flower_class;
}iris;
iris raw_data[DATA_NUMBER];


void Get_Dataset(int i, iris* dataset, float data, string str)
{
	switch(i)
	{
		case 0:
			dataset->sepal_length = data;
			break;
		case 1:
			dataset->sepal_width = data;
			break;
		case 2:
			dataset->petal_length = data;
		break;			
		case 3:
			dataset->petal_width = data;
			break;						
		case 4:
			if(str.compare("Iris-setosa") == 0)
				dataset->flower_class = -1;
			else
				dataset->flower_class = 1;
			break;
	}
}

float m_stof(string str)
{
	if(str.empty())
		return 0;
		

	int temp = 0;
	int index = 0;
	int point = 0;
	while(index < str.size())
	{
		
		if(str[index] == 48)
			temp = (temp * 10);
		else if(str[index] > 48 && str[index] < 58)
			temp = (temp * 10) + (str[index] - 48);
		else if(str[index] == 46)
			point = index;
		
		index++;
	}

	double ans = 1;
	point = str.size() - point;
	for(int i = 0; i < point-1; i++)
		ans *= 10;
	ans = temp / ans;
	return ans;
}

void Read_Iris_csv()
{
	ifstream IrisFile;
	IrisFile.open("iris.csv");	
	int index = 0;
	int cell_index = 0;
	while(IrisFile.good())
	{
		string line;
		getline(IrisFile, line, ',');
		
		Get_Dataset(cell_index,&raw_data[index],m_stof(line), line);

		if(cell_index >= 4)
		{
			cell_index = 0;
			index++;	
		}
		else 
			cell_index++;

	}
}

bool perceptron(double* w_n, iris& x_n, double* w_n1)
{
	int hat_y = 0;
	double f = 0;
	
	f += w_n[0] * x_n.sepal_length;
	f += w_n[1] * x_n.sepal_width;
	f += w_n[2] * x_n.petal_length;
	f += w_n[3] * x_n.petal_width;

	hat_y = (f>0)?1:-1;
	
	w_n1[0] = (w_n[0]) + (eta*(x_n.flower_class - hat_y)*x_n.sepal_length);
	w_n1[1] = (w_n[1]) + (eta*(x_n.flower_class - hat_y)*x_n.sepal_width);
	w_n1[2] = (w_n[2]) + (eta*(x_n.flower_class - hat_y)*x_n.petal_length);
	w_n1[3] = (w_n[3]) + (eta*(x_n.flower_class - hat_y)*x_n.petal_width);

	if((x_n.flower_class - hat_y) == 0)
		return true;
	else 
		return false;
}

void Test_function(double* w_n)
{
	float v0 = 0;
	float v1 = 0;
	float v2 = 0;
	float v3 = 0;
	
	printf("sepal_length: ");
	scanf("%f", &v0);
	
	printf("sepal_width: ");
	scanf("%f", &v1);
	
	printf("petal_length: ");
	scanf("%f", &v2);

	printf("petal_width: ");
	scanf("%f", &v3);
	
	float y = w_n[0]*v0 + w_n[1]*v1 + w_n[2]*v2 + w_n[3]*v3;
	y = y>0?1:-1;
	if((int)y == -1)	printf("Iris-setosa\n");
	else	printf("Iris-virginica\n\n\n");
}

int main(int argc, char** argv) {

	Read_Iris_csv();
	double w_n[4] = {0};
	double w_n1[4] = {0};
	int index = 0;
	int accuracy = 0;

  	random_shuffle(std::begin(raw_data), std::end(raw_data));
	  	/*
	for(int i = 0; i < DATA_NUMBER; i++)
	{
		printf("petal_length: %.2f\n", raw_data[i].petal_length);
		printf("petal_width: %.2f\n", raw_data[i].petal_width);
		printf("sepal_length: %.2f\n", raw_data[i].sepal_length);
		printf("sepal_width: %.2f\n", raw_data[i].sepal_width);
		printf("-----------------\n");
	}*/
  	
	while(accuracy<99)
	{
		bool correct = false;
		correct = perceptron(&w_n[0],raw_data[index],&w_n1[0]);
		w_n[0] = w_n1[0];
		w_n[1] = w_n1[1];
		w_n[2] = w_n1[2];
		w_n[3] = w_n1[3];
		
		if(index>=100)
		{
			index = 0;
			
			if(accuracy>99)
				break;
			else
				accuracy = 0;
		}
		else
		{
			index++;
			
			if(correct)
				accuracy++;		
		}
	}
	
	printf("w0:%f, ",w_n[0]);
	printf("w1:%f, ",w_n[1]);
	printf("w2:%f, ",w_n[2]);
	printf("w3:%f, ",w_n[3]);
	printf("accuracy:%d%\n\n\n",accuracy);
	Test_function(w_n);

	return 0;
}
