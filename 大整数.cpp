#include<iostream>
#include<queue>
#include<string>
#include<string.h>
using namespace std;
string GetNum(string &a){
	int asize = a.size();
	string temp = "";
	if(a[0] == '-'){
		for(int i = 1; i < asize; i++){
			temp += a[i];
		}
	}
	else{
		for(int i = 0; i < asize; i++){
			temp += a[i];
		}
	}
	return temp;
}
string cheng(string &a, string &b){
	string stra = GetNum(a);
	string strb = GetNum(b);
	int asize = stra.size();
	int bsize = strb.size();
	int isfu = 0;
	if(((a[0] != '-' && b[0] == '-') || (a[0] == '-' && b[0] != '-')) && (a != "0" && b != "0")){
		isfu = 1;
	}
	int *res = new int[asize + bsize];
	memset(res, 0, sizeof(int) * (asize + bsize));
	for(int i = asize - 1; i >= 0; i--){
		for(int j = bsize - 1; j >= 0; j--){
			int k = (stra[i] - '0') * (strb[j] - '0');
			res[i + j + 1] += k;
		}
	}
	for(int i = (asize + bsize- 1); i >= 0; i--){
		if(res[i] >= 10){
			res[i - 1] += res[i] / 10;
			res[i] %= 10;
		}
	}
	string fin = "";
    /*for (int i = 0; i < asize + bsize; ++i) {
        fin += res[i] + '0';
    }
	if(isfu == 1){
		fin = '-' + fin;
	}
	return fin;*/
    int k;
    for(k = 0; k < (asize + bsize) ; k++){
        if(res[k] != 0){
            break;
        }
    }
    if(k == (asize + bsize)){
        fin = "0";
    }
    else{
        for(int i = k; i < (asize + bsize); i++){
            fin += res[i] + '0';
        }
    }
    if(isfu == 1){
		fin = '-' + fin;
	}
    return fin;
}//乘法
string add(string &a, string &b){
	int asize = a.size();
	int bsize = b.size();
	int length = max(asize,bsize) + 1;
    int len = length;
	int *res = new int[length];
    memset(res, 0, sizeof(int) * length);
    string ans;
	if(asize == bsize){
        for(int i = asize - 1; i >= 0; i--){
            res[length - 1] = (a[i] - '0') + (b[i] - '0');
            length--;
        }
    }
    else if(asize > bsize){
        int temp = asize - bsize;
        for(int i = 0; i < temp; i++){
            b = '0' + b;
        }
        for(int i = asize - 1; i >= 0; i--){
            res[length - 1] = (a[i] - '0') + (b[i] - '0');
            length--;
        }
    }
    else if(asize < bsize){
        int temp = bsize - asize;
        for(int i = 0; i < temp; i++){
            a = '0' + a;
        }
        for(int i = bsize - 1; i >= 0; i--){
            res[length - 1] = (a[i] - '0') + (b[i] - '0');
            length--;
        }
    }
    for(int i = len - 1; i >= 0; i--){
        if(res[i] >= 10){
            res[i - 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    int k;
    for(k = 0; k < len ; k++){
        if(res[k] != 0){
            break;
        }
    }
    if(k == len){
        ans = "0";
    }
    else{
        for(int i = k; i < len; i++){
            ans += res[i] + '0';
        }
    }
    return ans;
}
string jian(string &a, string &b){
    int asize = a.size();
    int bsize = b.size();
    int len;
    if(asize == bsize){
        len = asize;
    }
    else if(asize > bsize){
        for(int i = 0; i < asize - bsize; i++){
            b = '0' +b;
        }
        len = asize;
    }
    else if(asize < bsize){
        for(int i = 0; i < bsize - asize; i++){
            a = '0' + a;
        }
        len = bsize;
    }
    int *anum = new int[len];
    int *bnum = new int[len];
    for(int i = 0; i < len; i++){
        anum[i] = a[i] - '0';
        bnum[i] = b[i] - '0';
    }
    int  judge = 0;//判断是否需要退位
    for(int i = len -1; i >= 0; i--){
        if(anum[i] >= bnum[i]){
            judge = 0;
        }
        else{
            judge = 1;
        }
        if(judge == 0){
            bnum[i] = anum[i] - bnum[i];
        }
        else if(judge == 1){//需要借一位
            anum[i - 1]--;
            anum[i] += 10;
            bnum[i] = anum[i] - bnum[i];
        }
    }
    string ans;
    int k;
    for(k = 0; k < len ; k++){
        if(bnum[k] != 0){
            break;
        }
    }
    if(k == len){
        ans = "0";
    }
    else{
        for(int i = k; i < len; i++){
            ans += bnum[i] + '0';
        }
    }
    return ans;
}
bool isPos(const string&str1, const string str2) 
{
	if (str1.size() > str2.size())
		return true;
	if (str1.size() == str2.size())
		return str1 > str2;
	return false;
}
void Cal(queue<string> &q, int n, string &a, string &b){
    string t;
	string s;
	string num1;
    string num2;
	string ans;
    q.push(to_string(0));
    //cout << q.front() << endl;
    q.push(a);
    q.push(b);
	for (int i = 1; i < n; i++) 
	{
        q.push(to_string(0));
		for (int j = 1; j <= i + 2; j++) 
		{
			t = q.front();
			q.pop();
            s = q.front();
            //cout << "t = " << t  << " "<< "s = " << s << endl;
			num1 = cheng(t, b);
			num2 = cheng(s, a);
            //cout << "num1 =" << num1  << " "<< "num2 =" << num2 << endl;
			if (num1[0] != '-' && num2[0] != '-')
				ans = add(num1, num2);
			else if (num1[0] == '-' && num2[0] == '-') 
			{
                string atemp = GetNum(num1);
                string btemp = GetNum(num2);
				ans = add(atemp , btemp);
				ans = '-' + ans;
			}
			if (num1[0] == '-' && num2[0] != '-') 
			{
				num1 = GetNum(num1);
				if (isPos(num2, num1)) 
				{
					ans = jian(num2, num1);
				}
				else 
				{
					ans = '-' + jian(num1, num2);
				}
			}
			if (num1[0] != '-' && num2[0] == '-') 
			{
				num2 = GetNum(num2);
				if (isPos(num1, num2)) 
				{
					ans = jian(num1, num2);
				}
				else 
				{
					ans = '-' + jian(num2, num1);
				}
			}
            //cout << "ans =" << ans << endl;
			q.push(ans);
		}
	}
    q.pop();
}
void showRes(queue<string>& q, int n) 
{
	int k = n;
	int flag = 1;
	while (!q.empty()) 
	{
		if (q.front() == "0" ) 
		{
			q.pop();
			k--;
			flag = 0;
			continue;
		}
		else if (q.front() == "1") 
		{
			if (flag != 0 && k < n){
                cout << '+';
            }
			flag = 1;
		}
		else if (q.front()[0] != '-') 
		{
			if (k < n)cout << '+';
			cout << q.front();
		}
		else if (q.front() == "-1"){
            cout << '-';
        }
		else if (q.front()[0] == '-'){
            cout << q.front();
        }

		if (k == 1) cout << 'x';
		else if (k != 0) cout << "x^" << k;
		if (k == n - 1) cout << 'y';
		else if (k != n) cout << "y^" << n - k;

		q.pop();
		k--;
	}
	cout << endl;
}
int main(){
    int a, b, n;
	cin >> a >> b >> n;
	queue<string>q;
	string str1 = to_string(a);
	string str2 = to_string(b);
	Cal(q, n, str1, str2);
    /*while(!q.empty()){
        cout << q.front() << endl;
        q.pop();
    }*/
    showRes(q, n);
	return 0;
}