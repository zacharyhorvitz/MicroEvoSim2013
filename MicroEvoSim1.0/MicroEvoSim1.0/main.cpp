#pragma region about

//Simplistic MicroEvolution Sim 1.75
//Zachary Horvitz
//Final Project:
//BIOEE 2070
//7/26/2013
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

#pragma endregion about

#pragma region includes
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <math.h>
#pragma endregion includes

#pragma region namespace
using namespace std;
#pragma endregion namespace

#pragma region agentclass
class Agent   //this is the agent class that defines the properties of each organism
{
public:
	int position[2];
	int energy;
	int energy1;
	int life;
	int life1;
	int food;
	bool alive;
	Agent(int, int, int, int, int, bool);
	~Agent();
	int organismmovex(int posx)
	{
		int x = (rand() % 3) - 1;
		posx = posx + x;
		return posx;
	}
	int organismmovey(int posy)
	{
		int y = (rand() % 3) - 1;
		posy = posy + y;
		return posy;
	}
};
Agent::Agent (int a, int b, int c, int d, int e, bool f)
{
	position[0] = a;
	position[1] = b;
	life1 = c;
	life = life1;
	food = d;
	energy1 = e;
	energy = energy1;
	alive = f;
};
#pragma endregion

#pragma region globals

const WORD colors[5] = {0x1A,0x2B,0x3C,0x4D,0x5E};
HANDLE in;
HANDLE out;
bool energydisp = false;
bool lifedisp = false;
bool fooddisp = false;


int displaytimer = 0;
int seed;
bool mapping = false; //used for displaying location of resources
bool gainenergy = false; //will probabably be changed: used to know when agent gains energy
bool showagent; //used for displaying location of resources
bool agentalive = true; 
int map;
int numagents = 1;
int numalive = 1;
int previousnumagents = 1;
int mappos[4][100001];// generates food positions.
int locat = 60;
Agent* agent1;
int doom;
int doom1;
int mutat;
int drain;
int inili;
int inieng;
int inifood;
char showmap;
std::vector<Agent *> myriad;

ofstream SaveFile("&distribution.csv");
#pragma endregion globals

void userinput()
{
	#pragma region user input

	
	cout<<"Enter seed for random world generation: "<<endl;
	cout<<"Recommended Seeds: 566565575, 10"<<endl;
	cin>>seed;


	SaveFile<<"Seed: "<<seed<<endl;
	system("cls");
	cout<<"Enter mutation rate per standard deviation (1-3 recommended):"<<endl;
	cin>>mutat;

	SaveFile<<"Mutation Rate: "<<mutat<<endl;
	system("cls");
	cout<<"Enter organism's drain on resources (2-5 recommended): "<<endl;
	cin>>drain;

	SaveFile<<"Resource Drain: "<<drain<<endl;
	system("cls");

	cout<<"Enter number of iterations until environmental change (15-150 recommended): "<<endl;
	cin>>doom;
	doom1 = doom;
	SaveFile<<"Change Date: "<<doom<<endl;
	system("cls");


	cout<<"Show world? (y/n)(Warning: may result in slow running): "<<endl;
	cin>>showmap;

	system("cls");



	cout<<"Initial Traits: "<<endl;
	cout<<endl;
	cout<<"Enter organism's longevity (10-26 recommended): "<<endl;
	cin>>inili;
	SaveFile<<"Longevity of First Organism: "<<inili<<endl;
	cout<<"Enter organism's energy storage (5-18 recommended): "<<endl;
	cin>>inieng;
	SaveFile<<"Energy of First Organism:  "<<inieng<<endl;
	cout<<"Enter organism's food (3-7 recommended): "<<endl;
	cin>>inifood;
	SaveFile<<"Food of First Organism: "<<inifood<<endl;
	SaveFile<<endl;
	SaveFile<<"Trait Distributions:"<<endl;
	SaveFile<<endl;

#pragma endregion
}

void initialgenerate()
{
	#pragma region generate food positions
	for(int w = 0; w < 200; w++)
	{
		for(int j = 0; j<2; j++)
		{
			mappos[j][w] = rand()% 21;

		}
		mappos[2][w] = 4;
		mappos[3][w] = 5;
	}
#pragma endregion generate food positions 
}

void color()
{

	in = GetStdHandle( STD_INPUT_HANDLE );
	out = GetStdHandle( STD_OUTPUT_HANDLE );
	


}

void reproduce()
{
	#pragma region reproduce
		for(int i = 0; i < numagents;i++)
		{
			for(int w = 0; w < locat; w++)
			{ 
				int eat = abs(mappos[3][w] - myriad[i]->food);//difference between organism's food type and resources
				if(myriad[i]->position[0] == mappos[0][w] && myriad[i]->position[1] == mappos[1][w] && mappos[2][w] > 0 && myriad[i]->energy > 0) 
				{

					myriad[i]->energy = myriad[i]->energy1/(1 + eat/2);  //the farther away the organism's food type from the resource, the less energy the organism will gain
				
					
					//mutation rates:

					int distribution1 = rand()% 101 + 1;
					int distribution2 = rand()% 101 + 1;
					int distribution3 = rand()% 101 + 1;

					int life1 = myriad[i]->life1;
					int energy1 = myriad[i]->energy;
					int food = myriad[i]->food;

					if(distribution2 <= 2)
					{
						energy1 = energy1-mutat;
					}
					if(distribution2 <= 15)
					{
						energy1 = energy1-mutat;
					} 
					if(distribution2 >= 84)
					{
						energy1 = energy1+mutat;
					}
					if(distribution2 >= 98)
					{
						energy1 = energy1+mutat;
					} 			

					if(distribution1 <= 2)
					{
						life1 = life1-mutat;
					}
					if(distribution1 <= 15)
					{
						life1 = life1-mutat;
					} 
					if(distribution1 >= 84)
					{
						life1 = life1+mutat;
					}
					if(distribution1 >= 98)
					{
						life1 = life1+mutat;
					} 				 


					if(distribution3 <= 2)
					{
						food = food-mutat;
					}
					if(distribution3 <= 15)
					{
						food = food-mutat;
					} 
					if(distribution3 >= 84)
					{
						food = food+mutat;
					}
					if(distribution3 >= 98)
					{
						food = food+mutat;
					} 				 

					Agent* agent = new Agent(myriad[i]->position[0],myriad[i]->position[1], life1,food, energy1,true);
					myriad.push_back(agent);
					previousnumagents++;
					mappos[2][w] = mappos[2][w]-drain; 
					numalive++;
				}
			}
		}
		numagents = previousnumagents;
#pragma endregion reproduce
}

void death()
{
	#pragma region death
		for(int i = 0; i < numagents; i++)
		{
			bool alivepre = myriad[i]->alive;
			if(myriad[i]->energy >0 && myriad[i]->life > 0)
			{myriad[i]->energy--;
			myriad[i]->life--;
			}
			else
			{
				myriad[i]->alive = false;	
				if(myriad[i]->alive != alivepre)
				{
					numalive--;
				}
			}
		}
#pragma endregion death
}

void generateworld()
{
	#pragma region generateworld
		if(showmap == 'y')
		{
			for(int y = 0; y<20; y++)
			{
				for(int x = 0; x<20; x++)
				{
					mapping = false;
					showagent = false;
					agentalive = true;
					int firstenergy;
					int firstfood;
					int firstlife;

					
					SetConsoleTextAttribute( out, colors[4]);	
					for(int i = 0; i<numagents; i++)
					{	
						if(myriad[i]->position[0] == x && myriad[i]->position[1] == y && myriad[i]->alive == true)
						{ 
							firstenergy = myriad[i]->energy;
							firstlife = myriad[i]->life;
							firstfood = myriad[i]->food;

							showagent = true;
						}

					}

					for(int w = 0; w<locat; w++)
					{
						if(mappos[0][w] == x && mappos[1][w]== y && mappos[2][w] > 0 )
						{ 
							map = mappos[3][w];
							mapping = true;
						}
					}
					if(showagent == true && fooddisp)
					{
						
						cout<<" "<<firstfood<<" "; 
				
					}
					else if(showagent == true && energydisp)
					{
						cout<<" "<<firstenergy<<" ";
						
					}
					else if(showagent == true && lifedisp)
					{
						cout<<" "<<firstlife<<" ";
					
					}
					else if(showagent)
					{
						cout<< " & ";
					}
					else if(mapping == true)
					{
						SetConsoleTextAttribute( out, colors[1]);
						cout<<" $ ";//map
							
						
					}
					else
					{
						cout<<"   ";
					}
						
				}
			
	
				cout<<endl;
			}
		}
	
#pragma endregion generateworld
}

void agentmove()
{
	#pragma region agentmmove
		for(int i = 0; i<numagents; i++)
		{
			if(myriad[i]->alive == true)
			{
				myriad[i]->position[0] = myriad[i]->organismmovex(myriad[i]->position[0]);
				myriad[i]->position[1] = myriad[i]->organismmovey(myriad[i]->position[1]);
			}
		}
#pragma endregion 
}

void replenish()
{
	#pragma region replenish resources
		for(int w = 0; w < locat; w++)
		{
			mappos[2][w]++;
		}
#pragma endregion 
}

int main()
{ 
userinput();

#pragma region seed
	srand(seed); //randomly generates a world
	system("cls");		
#pragma endregion seed

#pragma region makevector 
	//makes vector to store agents on
	
	agent1 = new Agent(10,10,inili,inifood,inieng, true);
	myriad.push_back(agent1);
#pragma endregion makevector

	

initialgenerate();

	while(true)
	{
		color();
		reproduce();
		death();
		generateworld();
		agentmove();
		replenish();

#pragma region savedata,delay, enviormental change, andsystemclearing
		SetConsoleTextAttribute( out, colors[3]);
		cout<<"# alive: "<<numalive<<endl;
		cout<<"# alive ever: "<<myriad.size()<<endl;
		displaytimer++;

		if(numalive < 1)
		{
			break;
		}
		int varenergy[100];
		int varlong[100];
		int varfood[100];

		for(int i = 0; i < 100; i++)
		{
			varenergy[i] = 0;
			varlong[i] = 0;
			varfood[i] = 0;

		}
		for(int i = 0; i < numagents; i++)
		{
			if(myriad[i]->alive == true)
			{
				int whichonee = myriad[i]->energy1;
				int whichonel = myriad[i]->life1;
				int whichone2 = myriad[i]->food;
				varenergy[whichonee] = varenergy[whichonee] + 1;
				varlong[whichonel] = varlong[whichonel] + 1;
				varfood[whichone2] = varfood[whichone2] + 1;

			}
		}
		SaveFile<<"Trait Value, Energy, Longevity, Food"<<"Current Food: "<<map<<endl;
		//cout<<"Trait Value, Energy, Longevity, Food"<<endl;

		int winnerfood = 0;
		int winnerfoodi = 0;
		int averagefood = 0;
		int sumfood = 0;
		

		for(int i = 0; i < 100; i++)
		{
			if(varfood[i] > 0)
			{
			sumfood = i*varfood[i] + sumfood;
			}
			int currentdifference = winnerfood - varfood[i];
			if(currentdifference < 0)
			{
				winnerfood = varfood[i];
				winnerfoodi = i;
			}
			SaveFile<< i <<" , "<<varenergy[i]<<" , "<<varlong[i]<< " , "<<varfood[i]<<endl;
			//cout<< i <<" , "<<varenergy[i]<<" , "<<varlong[i]<< " , "<<varfood[i]<<endl;
		}
		averagefood = sumfood/numalive;
		cout<< "Most Common Food Type: "<<winnerfoodi<<endl;
		cout<< "Average Food Type: "<<averagefood<<endl;

		SaveFile<<endl;
		doom--;

		if(doom == 0)
		{
			int random  = rand() % 15 - 7;
		
			for(int i = 0; i < locat; i++)
			{
				if(mappos[3][i] + random >= 1 && mappos[3][i] + random < 99)
				{
					mappos[3][i] = mappos[3][i] + random;
				}
			}
			doom = doom1;

		}

		cout<<"Food: "<<map<<endl;

		system("cls");
		if(displaytimer %10 == 0)
		{
			     energydisp = false;
					lifedisp = false;
					fooddisp = true;
		}
		else if(displaytimer %50 == 0)
		{
			/*lifedisp = true;
			energydisp = false;
			fooddisp = false;*/
		}
		else if(displaytimer %70 == 0)
		{
			/*fooddisp = true;
			energydisp = false;
			lifedisp = false;*/

		}



	}
	Sleep(200);

	system("cls");
	
		//if(energydisp)
		//{
		//	cout<<"Current View: Energy"<<endl;
		//}
		//	if(lifedisp)
		//{
		//	cout<<"Current View: Life"<<endl;
		//}
		//		if(fooddisp)
		//{
		//	cout<<"Current View: Food"<<endl;
		//}


	cout<<"Extinction!"<<endl;
	
	Sleep(400);
	SaveFile.close();

#pragma endregion delayandsystemclearing 

}




	