#include <stdio.h>

int main() {
    
    /* TODO: Implement here */
    int parties, deputies, i, x;
    float votelist[26];
    int count_of_seats[26] = {0};
    char ascii[26] = {'A'};
    scanf("%d %d\n", &parties, &deputies);

    for(i = 0; i<parties; i++){
        scanf("%f", &votelist[i]);
    }

    for(i = 0; i<deputies; i++){
        float quotient[26] = {0};
        int modified_votelist[26] = {0};
        int max_quotient = 0, t;
        for(t = 0; t<parties; t++){
            quotient[t] = votelist[t] / (count_of_seats[t]+1);
        }
        for(t = 0; t < parties; t++){
            modified_votelist[t] = votelist[t];
        }
        for (t = 1; t <= parties; ++t) {
            if (quotient[0] < quotient[t]) {
                quotient[0] = quotient[t];
                modified_votelist[0] = modified_votelist[t];
                max_quotient = t;
            } else if (quotient[0] == quotient[t]){
                if (modified_votelist[0] < modified_votelist[t]){
                    modified_votelist[0] = modified_votelist[t];
                    max_quotient = t;
                }
            }
        }
        count_of_seats[max_quotient]++;
    }
    
    for (i = 0; i < parties; i++){
        ascii[i] = i + 65;
    }
    
    for (i = 0; i < parties; ++i){
        for (x = i + 1; x < parties; ++x){
            int a;
            char b;
            if (count_of_seats[i] >= count_of_seats[x]){
                a =  count_of_seats[i];
                b = ascii[i];
                count_of_seats[i] = count_of_seats[x];
                ascii[i] = ascii[x];
                count_of_seats[x] = a;
                ascii[x] = b;
            } 
        }
    }

    for(x=parties-1; x>=0; x--){
        if (count_of_seats[x] == 0){
            continue;
        }
        printf("%c: %d\n", ascii[x], count_of_seats[x]);
    }
    
    return 0;
}