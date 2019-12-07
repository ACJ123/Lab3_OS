  
#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
void add (int a, int b);
void subtract (int a, int b);
void multiply (int a, int b);
void divide (int a, int b);
void exitProg (int a, int b);


int main (void)
{
	/* IMPLEMENT ME: Insert your algorithm here */
  int input, a , b;
  //Define 'a' and 'b'
  a = 6;
  b = 3;
  
  printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):");
  scanf("%d", &input);
  
  //function pointer array
  void (*func_ptr_arr[])(int,int) = {add, subtract, multiply, divide, exitProg};
  
  //While user input doesn't equal 4, call each function that correlates to the input number
  while (1){
    for (int i = 0; i == input; i++){
      //call add function with values a & b
      (*func_ptr_arr[input])(a,b);
    }
    for (int i = 1; i == input; i++){
      //call subtract function with values a & b 
      (*func_ptr_arr[input])(a,b);
    }
    for (int i = 2; i == input; i++){
      //call multiply function with values a & b 
      (*func_ptr_arr[input])(a,b);
    }
    for (int i = 3; i == input; i++){
      //call divide function with values a & b
      (*func_ptr_arr[input])(a,b);
    }
      //Call the correlating function when user input == 4
    for (int i = 4; i == input; i++){
      //exit the program
      printf ("Conratz, you exited the program.\n");
      return 0;
    }
    
    //Get next user input value
    printf("Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : exit):");
    scanf("%d", &input);
  }
  

  
	return 0;
}

/* IMPLEMENT ME: Define your functions here */
void add (int a, int b) { 
  printf ("Adding 'a' and 'b' = %d\n", a+b);
}
void subtract (int a, int b) { 
  printf ("Subtracting 'a' and 'b' = %d\n", a-b);  
}
void multiply (int a, int b) { 
  printf ("Multiplying 'a' and 'b' = %d\n", a*b);  
}
void divide (int a, int b) { 
  printf ("Dividing 'a' and 'b' = %d\n", a/b);  
}
void exitProg (int a, int b) { 
  printf ("Exiting program"); 
  exit(0); 
}