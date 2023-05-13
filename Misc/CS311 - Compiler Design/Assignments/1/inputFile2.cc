
/* Function to find the product of two integers. */
int product(int x, int y){
    return x*y;
}

/* Function the evaluates the absolute value of an integer. */
int absolute(int x){
    if (x < 0){   /* If x is negative, We will return negative value of x.*/
        return -x;
    }
    else if (x == 0){
        return 0;
    }
    else{
        return x;
    }
}

/* Divides the number by 2 and takes floor.*/
int div2(int x){
    return (x/2);
}

int main(){
    int ans1 = absolute(5);
    int ans2 = absolute(-77);
    int ans3 = product(ans1, ans2);
    int ans4 = div2(ans3); 
    return 0;
}
