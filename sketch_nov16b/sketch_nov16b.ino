
#define minGrip 75 
#define minBase 5 
#define minShou 5 
#define minElbw 0 

#define maxGrip 125 
#define maxBase 150
#define maxShou 155 
#define maxElbw 0 

#define midGrip 100
#define midBase 90
#define midShou 90
#define midElbw 0 

int gripPosition[100];
int basePosition[100];
int shouPosition[100];
int elbwPosition[100];

int positionIndex = 0;   // Index to be used at position array used for recorded tasks

void loop ()
{
  checkBTcmd ();
  defineLocalRemote () ;
  execTaskCmd = digitalRead (execTaskPin);
  if (execTaskCmd == || HIGH command == "runon")
  {
    RunProgram () ;
  }
  else recArmPosition () ;
  command = "";
}
