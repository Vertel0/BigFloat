#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
vector<char> int_plus(const vector<char>& a, const vector<char>& b){
    vector<char> res(max(a.size(), b.size()));
    char as = a.size(), bs = b.size(), m = max(a.size(), b.size());

    for(int i = 0; i < m; i++){
        if(i >= m - as){
            res[i]+=a[i - (m - as)];
        }
        if(i >=  m - bs){
            res[i]+=b[i - (m - bs)];
        }
    }
    for(int i = res.size()-1; i > 0; i--){
        if(res[i] >= 10){
            res[i]-=10;
            res[i-1]++;
        }
    }
    if(res[0] >= 10){
            res[0]-=10;
            res.push_back(0);
            for(int j = res.size()-1; j > 0; j--){
                res[j] = res[j-1];
            }
            res[0] = 1;
        }
        return res;
}


vector<char> bin_minus(const vector<char>& a, const vector<char>& b){

    vector<char> res;
    if(a.size() == b.size()){
        for(int i = a.size()-1; i >= 0; i--){
            res.push_back(a[i]-b[i]);
        }
        for(int i = 0; i < a.size()-1; i++){
            if(res[i] < 0){
                res[i]+=2;
                res[i+1]--;
            }
        }
        vector<char> res2;
        bool flag = 1;
        for(int i = res.size()-1; i >= 0; i--){
            if(flag == 1 && res[i] != 0){
                flag = 0;
            }
            if(!flag){
                res2.push_back(res[i]);
            }
        }
        return res2;
    }else{
        int j = a.size()-1;
        for(int i = b.size()-1; i >= 0; i--){
            res.push_back(a[j]-b[i]);
            j--;
        }
        res.push_back(1);

        for(int i = 0; i < res.size()-1; i++){
            if(res[i] < 0){
                res[i]+=2;
                res[i+1]--;
            }
        }

        vector<char> res2;
        bool flag = 1;
        for(int i = res.size()-1; i >= 0; i--){
            if(flag == 1 && res[i] != 0){
                flag = 0;
            }
            if(!flag){
                res2.push_back(res[i]);
            }
        }
        return res2;
    }
}


vector<char> frac_plus(const vector<char>& a, const vector<char>& b){
    vector<char> res(max(a.size(), b.size()));
    for(int i = 0; i < a.size(); i++){
        res[i] += a[i];
    }
    for(int i = 0; i < b.size(); i++){
        res[i] += b[i];
    }
    for(int i = res.size() - 1; i > 0; i--){
        if(res[i] >= 10){
            res[i]-=10;
            res[i-1]++;
        }
    }
    return res;
}
        vector<char> convert_integer(vector<char> digten){
             vector<char>digtwo;
            int i = digten.size()-1;
            while(1){
                digtwo.push_back(digten[i]%2);
                if(digten[i] % 2 != 0){
                    digten[i]--;
                }

            for(int j = i; j >= 0; j--){
                bool f = 0;
                if(digten[j] == 1){
                    f = 1;
                }
                if(digten[j] % 2 != 0){
                    digten[j]/=2;
                    digten[j+1] += 5;
                }else{
                    digten[j]/=2;
                }
                if(f){
                    digten[j] == 0;
                }
            }
            bool w = 0;
            for(int j = 0; j < digten.size(); j++){
                if(digten[j] != 0){
                    w = 1;
                }
            }
            if(!w){
                break;
            }
        }
        reverse(digtwo.begin(), digtwo.end());
        return digtwo;
    }

    vector<char> convert_frac(vector<char>digten, int num_dig){
        vector<char> digtwo;
        while(num_dig--){
            int f = 0;
            int extra = 0;
            for(int i = digten.size()-1; i >= 0; i--){
                digten[i] *= 2;
                digten[i] += extra;
                extra = 0;
                if(digten[i] > 9){
                    digten[i] -= 10;
                    if(i != 0){
                        extra = 1;
                    }else{
                        f = 1;
                    }
                }
            }
            digtwo.push_back(f);
        }
        return digtwo;
    }


class big_decimal{
    private:
    public:
        vector <char> dig;
        long long before;
        long long after;
        char sgn = 1;
        big_decimal(vector<char> v, long long b, long long a, char ssgn){
            bool flag = 1;
            int counter = 0;
            for(int i = 0; i < b-1; i++){
                if(flag && v[i] != 0){
                    flag = 0;
                    i--;
                }else if(!flag){
                    dig.push_back(v[i]);
                }else{
                    counter++;
                }
            }
            for(int i = b-1; i < v.size();i++){
                dig.push_back(v[i]);
            }
            before = b-counter;
            after = a;
            sgn = ssgn;
            int k = 0;
            for(int i = dig.size()-1; i > before;i--){
                if(dig[i] == 0){
                    k++;
                }else{
                    break;
                }
            }
            if(k != 0){
            after-=k;
            vector<char>q;
            for(int i = 0 ; i < dig.size()-k;i++){
                q.push_back(dig[i]);
            }
            dig = q;
            }

        }

        big_decimal(int b){

            string a;
            if(b == 0){
                a = "0";
            }
            while(b !=0 ){
                a = (char)((b%10) + '0') + a;
                b/=10;
            }
            after = 1;
            sgn = 1;
            vector<char> dig_int;
            vector<char> dig2_int;
            int point = 0;
            int i = 0;
            if(a[0] == '-'){
                i++;
                sgn = 0;
            }
            while(i < a.size()){
                dig_int.push_back(a[i]-'0');
                i++;
            }
            dig = convert_integer(dig_int);
            dig.push_back(0);
            before = dig.size()-1;
        }

        big_decimal(long double a){
            string b = to_string(a);
            big_decimal q(b, 20);
            dig = q.dig;
            before = q.before;
            after = q.after;
            sgn = q.sgn;
        }


        big_decimal(string a, long long aft = 10){
            after = aft;
            sgn = 1;
            vector<char> dig_int;
            vector<char> dig_frac;
            vector<char> dig2_int;
            vector<char> dig2_frac;
            int point = 0;
            int i = 0;
            if(a[0] == '-'){
                i++;
                sgn = 0;
            }
            while(a[i] != '.'){
                dig_int.push_back(a[i]-'0');
                i++;
            }
            i++;
            while(i < a.size()){
                dig_frac.push_back(a[i]-'0');
                i++;
            }
            dig2_int = convert_integer(dig_int);

            dig2_frac = convert_frac(dig_frac, after);
            for(int i = 0; i < dig2_int.size(); i++){
                dig.push_back(dig2_int[i]);
            }
            int kk = 1;
            for(int i = 1; i < dig2_frac.size(); i++){
                if(dig2_frac[i] != 0){
                    kk = i;
                }
            }
            for(int i = 0; i < kk; i++){
                dig.push_back(dig2_frac[i]);
            }
        after = kk;
        before = dig2_int.size();
        int k = 0;
            for(int i = dig.size()-1; i > before;i--){
                if(dig[i] == 0){
                    k++;
                }else{
                    break;
                }
            }
            if(k != 0){
                    after-=k;
            vector<char>q;
            for(int i = 0 ; i < dig.size()-k;i++){
                q.push_back(dig[i]);
            }
            dig = q;
            }
        }

        friend ostream& operator<<(ostream& out, const big_decimal &a);
        friend big_decimal operator+(const big_decimal &a, const big_decimal &b);
        friend big_decimal operator*(const big_decimal& a, const big_decimal& b);
        friend big_decimal operator-(const big_decimal& a, const big_decimal& b);
        friend big_decimal operator/(const big_decimal& a, const big_decimal& b);
        friend void print(const big_decimal& a);
        friend bool operator>(const big_decimal &a, const big_decimal &b);
        friend bool operator<(const big_decimal &a, const big_decimal &b);
        friend bool operator==(const big_decimal &a, const big_decimal &b);
        friend bool operator!=(const big_decimal &a, const big_decimal &b);
        friend big_decimal pi(int precision);
        big_decimal &operator=(const big_decimal &a) = default;
        big_decimal (const big_decimal &other) = default;
        big_decimal ( big_decimal &&other) = default;

};


ostream& operator<<(ostream& out, const big_decimal &a){
    if(a.sgn == 0){
        out<<"-";
    }
    if(a.before == 0){
        out << "0.";
        for(int i = 1; i < a.dig.size();i++){
            out<<(int)a.dig[i];
        }
        out<<"\n";
    }else{
        for(int i = 0; i < a.before; i++){
            out<<(int)a.dig[i];
        }
        out<<".";
        for(int i = a.before; i < a.dig.size(); i++){
            out<<(int)a.dig[i];
        }
        out<<"\n";
    }
    return out;
}


big_decimal operator+(const big_decimal& a, const big_decimal& b){

    char rsgn = 1;
    if(a.sgn == 0 && b.sgn == 0){
        rsgn = 0;
    }
    if(a.sgn == 0 && b.sgn == 1){
        big_decimal a1(a.dig, a.before, a.after, 1);
        return (b-a1);
    }
    if(a.sgn == 1 && b.sgn == 0){
        big_decimal b1(b.dig, b.before, b.after, 1);
        return (a-b1);
    }
    vector<char> res_dig;
    long long af = max(a.after, b.after);
    long long be = max(b.before, a.before);
    if(a.before >= b.before && a.after >= b.after){
        for(int i = 0; i < a.before - b.before; i++){
            res_dig.push_back(a.dig[i]);
        }
        int j = 0;
        for(int i = a.before-b.before; i < a.before + b.after; i++){
            res_dig.push_back(a.dig[i] + b.dig[j]);
            j++;
        }
        for(int i = a.before + b.after; i < a.before + a.after; i++){
            res_dig.push_back(a.dig[i]);
        }
    }else if(a.before <= b.before && a.after <= b.after){
        for(int i = 0; i < b.before - a.before; i++){
            res_dig.push_back(b.dig[i]);
        }
        int j = 0;
        for(int i = b.before-a.before; i < b.before + a.after; i++){
            res_dig.push_back(b.dig[i] + a.dig[j]);
            j++;
        }
        for(int i = b.before + a.after; i < b.before + b.after; i++){
            res_dig.push_back(b.dig[i]);
        }

    }else if(a.before <= b.before && a.after >= b.after){
        for(int i = 0; i < b.before - a.before; i++){
            res_dig.push_back(b.dig[i]);
        }
        int j = 0;
        for(int i = b.before - a.before; i < b.before + b.after; i++){
            res_dig.push_back(b.dig[i] + a.dig[j]);
            j++;
        }
        for(int i = j; i < a.before + a.after; i++){
            res_dig.push_back(a.dig[i]);
        }

    }else{
        for(int i = 0; i < a.before - b.before; i++){
            res_dig.push_back(a.dig[i]);
        }
        int j = 0;
        for(int i = a.before - b.before; i < a.before + a.after; i++){
            res_dig.push_back(a.dig[i] + b.dig[j]);
            j++;
        }
        for(int i = j; i < b.before + b.after; i++){
            res_dig.push_back(b.dig[i]);
        }
    }
    for(int i = res_dig.size() - 1; i > 0; i--){
        if(res_dig[i] == 2){
            res_dig[i] = 0;
            res_dig[i-1]++;
        }else if(res_dig[i] == 3){
            res_dig[i] = 1;
            res_dig[i-1]++;
        }
    }
    if(res_dig[0] > 1){
        res_dig.push_back(0);
        for(int i = res_dig.size()-1; i > 0; i--){
            res_dig[i] = res_dig[i-1];
        }
        res_dig[1] %= 2;
        res_dig[0] = 1;
        be++;
    }
    big_decimal res(res_dig, be, af, rsgn);
    return res;
}


big_decimal operator*(const big_decimal& a, const big_decimal& b){
    big_decimal result (0);

    long long j = 0;
    for(int i = b.dig.size()-1; i >= 0; i--){
        vector<char> q = a.dig;
        if(b.dig[i] == 1){
            for(int k = 0; k < j; k++){
                q.push_back(0);
        }
            q.push_back(0);
            big_decimal buf(q, q.size()-1, 1, 1);
            result = result + buf;
        }
        j++;
    }
        char rsgn;
        if(a.sgn == b.sgn){
            rsgn = 1;
        }else{
            rsgn = 0;
        }
        long long sz = result.dig.size();
        long long bef = sz - (a.after+b.after+1);
        vector<char>fres;
        while(bef < 1){
            fres.push_back(0);
            bef++;
            sz++;
        }
        for(int i = 0; i < result.dig.size(); i++){
            fres.push_back(result.dig[i]);
        }
        big_decimal fin(fres,bef,sz-bef,  rsgn);
        return fin;
}

void print(const big_decimal& a){

    if(a.sgn == 0){
        cout<<"-";
    }
    vector<char> dig2_int;
    vector<char> dig2_frac;
    for(int i = 0; i < a.before; i++){
        dig2_int.push_back(a.dig[i]);
    }
    for(int i = a.before; i < a.after + a.before; i++){
        dig2_frac.push_back(a.dig[i]);
    }
    vector<char> res{0}, two{2};

    if(dig2_int.size() != 0){
    if(dig2_int[dig2_int.size()-1] == 1){
        res[0] = 1;
    }
    }
    for(int i = dig2_int.size() - 2; i >= 0; i--){

        if(dig2_int[i] == 1){
            res = int_plus(res, two);
        }
        for(int j = two.size()-1; j >= 0 ; j--){
            two[j]*=2;
        }

        for(int j = two.size()-1; j > 0 ; j--){
            if(two[j] >= 10){
                two[j]-=10;
                two[j-1]++;
            }
        }

        if(two[0] >= 10){
            two[0]-=10;
            two.push_back(0);
            for(int j = two.size()-1; j > 0; j--){
                two[j] = two[j-1];
            }
            two[0] = 1;
        }

    }

    for(int i = 0; i < res.size(); i++){
       cout<<(int)res[i];
    }


    res = {0}, two = {5};

    for(int i = 0; i < dig2_frac.size(); i++){

        if(dig2_frac[i] == 1){
            res = frac_plus(res, two);
        }
        bool prev_was_bad = 0;
        for(int j = 0; j < two.size(); j++){
            if(prev_was_bad){
                if(two[j] % 2 == 0){
                   prev_was_bad = 0;
                }
                two[j]/=2;
                two[j]+=5;
            }else{
                if(two[j] % 2 == 1){
                    prev_was_bad = 1;
                }
                two[j]/=2;
            }
        }
        if(prev_was_bad){
            two.push_back(5);
        }
    }
    cout<<".";
    for(int i = 0; i < res.size(); i++){
       cout<<(int)res[i];
    }
    cout<<"\n";
}


bool operator>(const big_decimal &a, const big_decimal &b){
    if(a.sgn < b.sgn){
        return 0;
    }else if(a.sgn > b.sgn){
        return 1;
    }
    if(a.before > b.before){
        return 1;
    }else if(a.before < b.before){
        return 0;
    }else{
        for(int i = 0; i < min(a.dig.size(), b.dig.size()); i++){
            if(a.dig[i] > b.dig[i]){
                return 1;
            }else if(a.dig[i] < b.dig[i]){
                return 0;
            }
        }
        if(a.after > b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < a.dig.size(); i++){
            if(a.dig[i] != 0){
                return 1;
            }
        }
    }else if(a.after < b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < b.dig.size(); i++){
            if(b.dig[i] != 0){
                return 1;
            }
        }
    }
    }
    return 0;
}


bool operator<(const big_decimal &a, const big_decimal &b){
    if(a.sgn < b.sgn){
        return 1;
    }else if(a.sgn > b.sgn){
        return 0;
    }
    if(a.before < b.before){
        return 1;
    }else if(a.before < b.before){
        return 0;
    }else{
        for(int i = 0; i < min(a.dig.size(), b.dig.size()); i++){
            if(a.dig[i] < b.dig[i]){
                return 1;
            }else if(a.dig[i] > b.dig[i]){
                return 0;
            }
        }

        if(a.after > b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < a.dig.size(); i++){
            if(a.dig[i] != 0){
                return 0;
            }
        }
    }else if(a.after < b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < b.dig.size(); i++){
            if(b.dig[i] != 0){
                return 0;
            }
        }
    }
    }
    return 1;
}


bool operator==(const big_decimal &a, const big_decimal &b){
    if(a.before != b.before || a.sgn != b.sgn){
        return 0;
    }
    for(int i = 0 ; i < min(a.dig.size(), b.dig.size()); i++){
        if(a.dig[i] != b.dig[i]){
            return 0;
        }
    }
    if(a.after > b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < a.dig.size(); i++){
            if(a.dig[i] != 0){
                return 0;
            }
        }
    }else if(a.after < b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < b.dig.size(); i++){
            if(b.dig[i] != 0){
                return 0;
            }
        }
    }
    return 1;
}


bool operator!=(const big_decimal &a, const big_decimal &b){
    if(a == b){
        return 0;
    }
    return 1;
}


bool cmp_abs(const big_decimal &a, const big_decimal &b){
    if(a.before > b.before){
        return 1;
    }else if(a.before < b.before){
        return 0;
    }else{
        for(int i = 0; i < min(a.dig.size(), b.dig.size()); i++){
            if(a.dig[i] > b.dig[i]){
                return 1;
            }else if(a.dig[i] < b.dig[i]){
                return 0;
            }
        }
        if(a.after > b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < a.dig.size(); i++){
            if(a.dig[i] != 0){
                return 1;
            }
        }
    }else if(a.after < b.after){
        for(int i = min(a.dig.size(), b.dig.size()); i < b.dig.size(); i++){
            if(b.dig[i] != 0){
                return 1;
            }
        }
    }
    }
    return 0;
}


big_decimal operator-(const big_decimal& a, const big_decimal& b){
    if(a.sgn == 1 && b.sgn == 0){
        big_decimal b1(b.dig, b.before, b.after, (b.sgn + 1)%2);
        return (a+b1);
    }
    if(a.sgn == 0 && b.sgn == 1){
        big_decimal b1(b.dig, b.before, b.after, (b.sgn + 1)%2);
        return (a + b1);
    }
    if(a.sgn == 0 && b.sgn == 0){
        big_decimal b1(b.dig, b.before, b.after, 1), a1(a.dig, a.before, a.after, 1);
        return (b1 - a1);
    }
    char res_sgn = 1;
    long long prev_before = a.before;
    vector<int> res;
    if(cmp_abs(a, b)){
    long long as = a.before, bs = b.before;
    for(int i = 0; i < as; i++){
        res.push_back(a.dig[i]);
        if(i >= as - bs){
            res[i]-=b.dig[i - (as - bs)];
        }
    }
    int j = bs, ii = as;
    for(int i = as; j < bs + b.after; i++){
        if(i >= as + a.after){
            res.push_back(-b.dig[j]);
        }else{
            res.push_back(a.dig[i]-b.dig[j]);
        }
        ii++;
        j++;
    }
    for(int i = ii; i < as+a.after; i++){
        res.push_back(a.dig[i]);
    }

    for(int i = res.size()-1; i > 0; i--){
        if(res[i] < 0){
            res[i]+=2;
            res[i-1]--;
        }
    }
    }else{
        prev_before = b.before;
        res_sgn = 0;
       long long as = a.before, bs = b.before;
    for(int i = 0; i < bs; i++){
        res.push_back(b.dig[i]);
        if(i >= bs - as){
            res[i]-=a.dig[i - (bs - as)];
        }
    }
    int j = as, ii = bs;
    for(int i = bs; j < as + a.after; i++){
        if(i >= bs + b.after){
            res.push_back(-a.dig[j]);
        }else{
            res.push_back(b.dig[i]-a.dig[j]);
        }
        ii++;
        j++;
    }
    for(int i = ii; i < bs+b.after; i++){
        res.push_back(b.dig[i]);
    }

    for(int i = res.size()-1; i > 0; i--){
        if(res[i] < 0){
            res[i]+=2;
            res[i-1]--;
        }
    }
    }
    long long after = 0, before = prev_before;

    for(int i = prev_before; i < res.size(); i++){
        if(res[i] != 0){
            after = i+1 - prev_before;
        }
    }
    vector<char> final_res;
    int k = 0;
    int jj = 0;
    while(res[k] == 0 && k < prev_before-1){
        k++;

    }
    for(int i = k; i < prev_before + after; i++){

        final_res.push_back((char)res[i]);
    }
    before-=k;

    big_decimal bob(final_res, before, after, res_sgn);
    return bob;
}


bool div_cmp(const vector<char>& aa,const vector<char>& bb ){
    vector<char> a;
    vector<char> b;
    bool flag = 1;
    for(int i = 0; i < aa.size();i++){
        if(flag && aa[i] != 0){
            flag = 0;
        }
        if(!flag){
            a.push_back(aa[i]);
        }
    }
    flag = 1;
    for(int i = 0; i < bb.size();i++){
        if(flag && bb[i] != 0){
            flag = 0;
        }
        if(!flag){
            b.push_back(bb[i]);
        }
    }
    if(a.size() > b.size()){
        return 1;
    }
    if(a.size() < b.size()){
        return 0;
    }
    for(int i = 0 ; i < a.size();i++){
        if(a[i] < b[i]){
            return 0;
        }
        if(a[i] > b[i]){
            return 1;
        }
    }
    return 1;
}


big_decimal operator/(const big_decimal& a, const big_decimal& b){
    big_decimal aa = a, bb = b;
    if(a.after < b.after){
        for(int i = 0; i < b.after - a.after;i++){
            aa.dig.push_back(0);
            aa.after++;
        }
    }else{
    for(int i = 0; i < a.after - b.after;i++){
            bb.dig.push_back(0);
            bb.after++;
        }
    }
    vector<char>temp;
    vector<char> res;
    long long per_a = 0, per_b = 0;
    if(aa.before > 1){
        per_a = aa.before - 1;
    }else if(aa.before >= 0 && aa.dig[0] == 0){
        int i = 1;
        while(aa.dig[i] == 0){
            i++;
            per_a--;
        }
    }
    if(bb.before > 1){
        per_b = bb.before - 1;
    }else if(bb.before >= 0 && bb.dig[0] == 0){

        int i = 1;
        while(bb.dig[i] == 0){
            i++;
            per_b--;
        }
    }
    long long del = 0;
    if(per_b <= 0){
            del += abs(per_b)+1;
        for(int i = 0; i < abs(per_b)+1; i++){
            bb = bb * big_decimal(2);
        }
        per_b = 1;
    }
    long long a_af = aa.after, b_af = bb.after;
    if(a_af < b_af){
        for(int i = 0; i < b_af - a_af;i++){
            aa.dig.push_back(0);
            aa.after++;
        }
    }else{
    for(int i = 0; i < a_af - b_af;i++){
            bb.dig.push_back(0);
            bb.after++;
        }
    }
    long long bef = per_a - per_b;
    if(bef >= 0){
        bef++;
    }else{
        bef = 1;
    }
    long long k = 0;
    for(int i = 0; i < min(bb.dig.size(), aa.dig.size()); i++){
        temp.push_back(aa.dig[i]);
    }
    if(!div_cmp(temp, bb.dig) && temp.size() < aa.dig.size()){
        temp.push_back(aa.dig[temp.size()]);
    }

    for(int i = min(bb.dig.size(), aa.dig.size()); i < bb.dig.size(); i++){
        temp.push_back(0);
        res.push_back(0);
    }

    k = temp.size();
    int kk =0;
    while(res.size() < 336){
         if(temp[0] == 0){
            vector<char> t2;
            for(int i = 1; i < temp.size(); i++){
                t2.push_back(temp[i]);
            }
            temp = t2;
         }
        if(div_cmp(temp, bb.dig)){
            res.push_back(1);
            temp = bin_minus(temp, bb.dig);

            if(k < aa.dig.size()){
                temp.push_back(aa.dig[k]);
                k++;
            }else{
                temp.push_back(0);
            }
        }else{
            res.push_back(0);
            if(k < aa.dig.size()){
                temp.push_back(aa.dig[k]);
                k++;
            }else{
                temp.push_back(0);
            }
        }
    }
    char rsgn;
        if(a.sgn == b.sgn){
            rsgn = 1;
        }else{
            rsgn = 0;
        }
    big_decimal rr(res, max(bef, (long long)1), res.size()-bef, rsgn);
    for(int i = 0; i < del;i++){
        rr = rr * big_decimal(2);
    }
    return rr;
}


big_decimal abs(const big_decimal& a){
    big_decimal b (a.dig, a.before, a.after, 1);
    return b;
}


big_decimal pi(int precision) {
    big_decimal pi("0.0", precision);
    big_decimal sixteen("16.0", precision);
    big_decimal sixteen_pow("1.0", precision);
    big_decimal one("1.0", precision);
    big_decimal two ("2.0", precision);
    big_decimal four ("4.0", precision);
    big_decimal five ("5.0", precision);
    big_decimal six ("6.0", precision);
    big_decimal eight("8.0", precision);

    for (int k = 0; k < precision; ++k) {

        big_decimal term1 = four / ((eight * big_decimal(k)) + one);
        big_decimal term2 = two / ((eight * big_decimal(k)) + four);
        big_decimal term3 = one / ((eight * big_decimal(k)) + five);
        big_decimal term4 = one / ((eight * big_decimal(k)) + six);
        big_decimal term = ((((term1 - term2) - term3) - term4)) / sixteen_pow;
        if(k != precision - 1){
        sixteen_pow = sixteen_pow * sixteen;
        }
        pi = pi + term;
    }


    return pi;
}

int main(){
    big_decimal a = pi(100);
    print(a);
 }
