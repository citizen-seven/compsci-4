#include <iostream>
#include <cstdlib>

using namespace std;

class Arithmetic{
  unsigned char* digit;
  int n;
  
public:
   Arithmetic();
   Arithmetic(const char*); 
   ~Arithmetic();
   Arithmetic( const Arithmetic&);
   Arithmetic& operator=(const Arithmetic&);
   Arithmetic& operator=(int n);
   void print();
};


Arithmetic::Arithmetic(){
   n = 1;
   digit = new unsigned char;
   digit[0] = 0;
   cout<<"Constructor\n";
};

Arithmetic::Arithmetic(const char* s){
    int i;
    int len = strlen(s);
    n = ( len % 2 )? (len >> 1) + 1: len >> 1;
    digit = new unsigned char[n];
    len--;
    
    for(i = 0;i < n;i++){
      digit[i] = s[ len-- ] - '0';
      if( len < 0 )
       break;
      digit[ i ] += ( s[ len-- ] - '0' ) * 10;
   }
};

void Arithmetic::print(){
   int i;
   cout<<"len="<<n<<endl;      
   for(i=0;i<n; i++){
     cout<<(int)digit[i]<<' ';
   }
   cout<<endl;
};

Arithmetic::Arithmetic(const Arithmetic& a){
   digit = new unsigned char[ a.n];
   n=a.n;
   memcpy(digit,a.digit, sizeof(unsigned char)*n); 
};

Arithmetic::~Arithmetic(){
  delete[] digit;
  cout<<"Dectructor!!\n";
};

Arithmetic& Arithmetic::operator=(const Arithmetic& a){
   delete[] digit;
    digit = new unsigned char[ a.n ];
   n = a.n;
   cout<<"размер: "<<sizeof( unsigned char)*n<<endl;
   memcpy( digit, a.digit, sizeof( unsigned char)*n ); 
    return *this;
};

Arithmetic& Arithmetic::operator=(int a){
   delete[] digit;
   digit = new unsigned char;
   n = 1;
   digit[0] = a;
   return *this;
};
