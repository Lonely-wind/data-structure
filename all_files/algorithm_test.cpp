#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    //max函数
    /*int a,b;
    cin >> a >> b;
    cout << max(a,b);*/

    //abs函数(绝对值)
    /*int a = -1;
    cout << abs(a);*/

    //swap函数
    /*int a = -1,b = -2;
    swap(a,b);
    cout << a;*/

    //对数组的翻转
    /*int a[5] = {1,2,3,4,5};
    reverse(a,a+5);
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/

    //排序函数
    /*int a[5] = {3,6,2,4,5};
    sort(a,a+5);//默认是升序
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/

    //find函数
    /*int a[5] = {3,6,2,4,5};
    cout << find(a,a+5,2) - &a[0];
    //find函数默认传回的是地址，需要经过一定的转化*/

    //fill函数
    /*int a[5] = {3,6,2,4,5};
    fill(a,a+5,0);
    for(int i = 0; i < 5; i++){
        cout << a[i] << " ";
    }*/

    //__gcd求最大公因数
    /*int a = 30;
    int b = 20;
    cout << __gcd(a,b);*/

    //求最小公倍数
    /*int a = 30;
    int b = 20;
    cout << a*b/__gcd(a,b);*/
}