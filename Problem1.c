#include <stdio.h>

struct product{
    int quantity;
    int price;
    int code;
};

int main(void){

    int nNumber=0, total=0, payment=0, change=0, i=0;
    struct product item[256]; // max 256 items

    printf("Enter number of items you want to purchase: ");
    scanf("%d", &nNumber);

    for(i=0; i<nNumber; i++){
        printf("\nProduct #%d\n", i+1);
        printf("Enter product code: ");
        scanf("%d", &item[i].code);

        printf("Enter price: ");
        scanf("%d", &item[i].price);

        printf("Enter quantity: ");
        scanf("%d", &item[i].quantity);
    }


    for(i=0; i<nNumber; i++){
        printf("Product Code: %d\nPrice: %d\nQuantity: %d\n\n", item[i].code, item[i].price, item[i].quantity);

        total = total + (item[i].price*item[i].quantity);
    }

    printf("Total: %d\n", total);
    printf("Enter payment: ");
    scanf("%d", &payment);

    if(total>payment)
        printf("Insufficient payment");
    else{
        change = payment-total;
        printf("Change: %d", change);
    }

    return 0;
}