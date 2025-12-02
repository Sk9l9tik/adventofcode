#include <bits/stdc++.h>

void part1(){
    int cur{50}, ans{};
    std::string s;
    while(std::cin >> s){
        if (s[0] == 'R'){
            int p = stoi(s.substr(1));
            p = p % 100;
            cur = (cur + p) % 100;
        }
        else{
            int p = stoi(s.substr(1));
            p = p % 100;
            cur = (cur - p) % 100;
            if (cur < 0) cur = (cur + 100) % 100;
        }
        std::cout << cur << '\n';
        if (cur == 0)
            ++ans;
    }
    std::cout << ans << '\n';
}

int findz(int l, int r){
    if (l > r) std::swap(l, r);

    return std::max<int>(0, (int)std::floor(r/100.0) - (int)std::ceil(l/100.0) + 1);
}

void part2(){
    int cur{50}, ans{};
    std::string s;

    while (std::cin >> s) {
        int old = cur;
        int t{};

        if (s[0] == 'R') {
            int p = stoi(s.substr(1));

            int next = cur + p;

            t = findz(cur+1, next);

            next %= 100;
            if (next < 0) next += 100;
            ans+=t;
            cur=next;
        }
        else {
            int p = stoi(s.substr(1));

            int next = cur - p;

            t = findz(cur-1, next);

            next %= 100;
            if (next < 0) next += 100;
            ans+=t;
            cur=next;
        }

        // if (cur == 0)
        //     ans++;             // попадание в 0 по завершению

        std::cout << cur << '\n';
    }
    std::cout << ans << '\n';
}

int main(){
    part2();
    return 0;
}
