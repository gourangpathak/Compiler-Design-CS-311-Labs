int main()
{
    int a, b, c;

    if (a != b){
        a = b + c;
    }
    else if ( a > b || a > c ){ 
        b = b + a; 
    }
    else if( a == b ){ 
        a = a + c; 
        b = b * c; 
    } 
    else{ 
        a = b/c; 
    }

    while( a > b && a < c ){ 
        /*I am inside while loop*/
        a = a+c;
    }
}
