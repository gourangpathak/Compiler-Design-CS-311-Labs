/* Divides the number by 2 and takes floor.*/
float div2(float x){
    float two = 2;
    return (x/two);
}

/* Function the evaluates the absolute value of an integer. */
int absolute(int x){
    if (x <= 0){   /* If x is negative, We will return negative value of x.*/
        return -x;
    }
    else{
        return x;
    }
}

int main(){
    int ans1 = absolute(5);
    int ans2 = absolute(-77);
    float _ans3 = div2(400.78);
    float ans4 = div2(-333.5); 
    ans4 += 4;
    return 0;
}