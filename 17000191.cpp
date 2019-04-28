#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <fstream>
using namespace std;
const int MAXSUBJECTS = 10;
const int MAXSTUDENTS = 100;
class subject{	
    private:
        string subcode;        
        string studid;
        int mark;
        char grade;
        
    public:
    	subject(string="",string="",int=0,char='\0'){};
		int operator>(subject&);
		subject& operator=(subject&);
        void setinfo(string,string,int);
        void printinfo();
        friend void grades(int,ostream&);
    	friend void displaysub();
    	friend void displaystud();
    	friend void summery();
    	friend void save();
    	friend void sort();
};

subject *arr[MAXSUBJECTS];	
int arrnum[MAXSUBJECTS]={0};
void displaysub();
void displaystud();
void summery();
void grades(int,ostream&);
void save();
void sort();
int strtoint(string);

int strtoint(string str){
	int n=0;
	stringstream s(str);
	s>>n;
	return n;
}

subject& subject::operator=(subject& a){
	subcode=a.subcode;
	studid=a.studid;
	mark=a.mark;
	grade=a.grade;
	return *this;
}

int subject::operator>(subject& a){
	int left=strtoint(studid);
	int right=strtoint(a.studid);
	if(left>right)
		return 1;
	else return 0;
}

void subject::setinfo(string code,string id,int result){
	subcode=code;
	studid=id;
	mark=result;
	if(result>=70)
		grade='A';
	else if(result>=55)
		grade='B';
	else if(result>=40)
		grade='C';
	else if(result>=30)
		grade='D';
	else 
		grade='F';		
}
		
void subject::printinfo(){
	cout<<subcode<<" "<<studid<<" "<<mark<<" "<<grade<<endl;
}
			
int main(){
    int num,i=0,top=0;    
    string str,sub;    
    ifstream myfile;    
    myfile.open("subjdata.txt");    
    if(!myfile.is_open()){
        cout<<"Can't open file"<<endl;
        exit(1);
    }   
    while(myfile >> str >> num){          
        if(str.empty())
        	continue;        	
        if(str.length()==7){ 
			if(num>MAXSTUDENTS){
				cout<<"ERROR"<<endl;
				exit(1);
			}       
        	i=0;
        	sub=str;
        	arr[top]=new subject [num];   
			arrnum[top]=num; 
			top++;			    	
    	}
    	else if(str.length()==8){	       
	       	(arr[top-1]+i)->setinfo(sub,str,num);	       	
	       	i++;
		   }		
}	   
	myfile.close();
    sort();    
    int opt;
    do{
        cout<< "1. Display Subject"<<endl
               << "2. Display Student"<<endl
               << "3. Display Subject Summary"<<endl
               << "4. Save Summaries"<<endl
               << "5. Exit Program"<<endl;
        cout<<"Enter option: ";
        cin>>opt;
        switch(opt){
            case 1:displaysub();break;
            case 2:displaystud();break;
            case 3:summery();break;
            case 4:save();break;
			        }
    }while(opt<5&&opt>0);
    return 0;
}

void sort(){
	int i,j,k;
	for(i=0;i<MAXSUBJECTS;i++){
		if(arrnum[i]==0)
			continue;
		for(j=0;j<arrnum[i];j++){			
			for(k=j+1;k<arrnum[i];k++){
				if(*(arr[i]+j)>*(arr[i]+k)){					
					subject a=*(arr[i]+j);
					*(arr[i]+j)=*(arr[i]+k);
					*(arr[i]+k)=a;
			}
			}
		}
	}	
}

void displaysub(){
	int i,j,flag=0;
	string subjectc;
	cout << "Enter subject code: ";
	cin >> subjectc;
	for(i=0;i<MAXSUBJECTS;i++){
		if(arrnum[i]==0)
			continue;
		if(arr[i]->subcode==subjectc){
			flag=1;
			for(j=0;j<arrnum[i];j++){
				(arr[i]+j)->printinfo();
				}
    		break;
		}
}
    if(!flag)
    	cout<<"Incorrect code"<<endl;	
	system("pause");	
}

void displaystud(){
	int i,j,flag=0;
	string student;
	cout << "Enter student id: ";
	cin >> student;	
	for(i=0;i<MAXSUBJECTS;i++){
		if(arrnum[i]==0)
			continue;
		for(j=0;j<arrnum[i];j++){
			if((arr[i]+j)->studid==student){
				flag=1;
				(arr[i]+j)->printinfo();
				break;
			}
    	}
}
        if(!flag)
        	cout<<"Incorrect code"<<endl;
        system("pause");
}

void summery(){
	int i,j,flag=0;;
	double avg,tot=0.0;
	string subjectc;
	cout << "Enter subject code: ";
	cin >> subjectc;
	for(i=0;i<MAXSUBJECTS;i++){
		if(arrnum[i]==0)
			continue;
		if(arr[i]->subcode==subjectc){
			flag=1;
			for(j=0;j<arrnum[i];j++){					
				tot+=(arr[i]+j)->mark;
				(arr[i]+j)->printinfo();
			}
   			break;
		}
}
    if(!flag)
    	cout<<"Incorrect code"<<endl;
    else{
    	double var=0.0;
    	avg=tot/arrnum[i];
    	cout<<"Average: "<<avg<<endl;
		for(j=0;j<arrnum[i];j++){    				
			var+=pow(((double)((arr[i]+j)->mark))-avg,2);
			}
	    var/=arrnum[i];
	    cout<<"Standard deviation: "<<sqrt(var)<<endl;
	    grades(i,cout);
	}
	system("pause");	
}

void grades(int i,ostream& fout){
	fout<<arr[i]->subcode<<" ";
	int noofg[6]={0},j;
	for(j=0;j<arrnum[i];j++){
		if((arr[i]+j)->grade=='A')
			noofg[0]+=1;
		else if((arr[i]+j)->grade=='B')
			noofg[1]+=1;
		else if((arr[i]+j)->grade=='C')
			noofg[2]+=1;
		else if((arr[i]+j)->grade=='D')
			noofg[3]+=1;
		else if((arr[i]+j)->grade=='E')
			noofg[4]+=1;
		else if((arr[i]+j)->grade=='F')
			noofg[5]+=1;
	}	
	fout<<"A "<<(float)noofg[0]/arrnum[i]*100<<"%"
	<<" B "<<(float)noofg[1]/arrnum[i]*100<<"%"
	<<" C "<<(float)noofg[2]/arrnum[i]*100<<"%"
	<<" D "<<(float)noofg[3]/arrnum[i]*100<<"%"
	<<" E "<<(float)noofg[4]/arrnum[i]*100<<"%"
	<<" F "<<(float)noofg[5]/arrnum[i]*100<<"%"<<endl;	
}

void save(){
	int i;
	char ch;
	ofstream outfile;	
	cout<<"Do you want to overwrite type y or n: ";
	cin>>ch;
	if(ch=='y')
		outfile.open("summdata.txt");
	else
		outfile.open("summdata.txt",ios::app);	
	for(i=0;i<MAXSUBJECTS;i++){
		if(arrnum[i]==0)
			continue;
		grades(i,outfile);
	}
	outfile.close();
	system("pause");
}
