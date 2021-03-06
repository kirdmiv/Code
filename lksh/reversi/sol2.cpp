#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAXD = 4; 
const vector<pii> shift = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};
struct Turn{
    vector<pii> d;
    int x, y;
    int who;
};
ofstream heh("heh.out");
double calc(const vector<vector<int>>& fld, const vector<vector<int>>& old_fld, int c){
    double ans = (fld[0][0] == c) * 10.0;
    ans += (fld[0][7] == c) * 10.0;
    ans += (fld[7][0] == c) * 10.0;
    ans += (fld[7][7] == c) * 10.0;
    for (int i = 0; i < 8;i++){
        for (int j = 0; j < 8;j++){
            // cerr << ans << ' ';
            if (fld[i][j] == !c && old_fld[i][j] == c) ans -= 1.4;
            else if (fld[i][j] == !c) ans -= 1;
            if (fld[i][j] == c && old_fld[i][j] == !c) ans += 1.6;
            else if (fld[i][j] == c && old_fld[i][j] == -1) ans += 1.4;
            else if (fld[i][j] == c) ans += 1;
        }
    }
    // cerr << "\nCOLOR " << c << '\n';
    // for (int i = 0;i <8;i++){
    //     for (int j = 0;j < 8;j++){
    //         if (fld[i][j] == -1) cerr << '.';
    //         if (fld[i][j] == 0) cerr << 'W';
    //         if (fld[i][j] == 1) cerr << 'B';
    //         // cerr << fld[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }
    cerr << "FINAL ANS!!!!!!!!!!!! " << ans << '\n'; 
    return ans;
}
vector<Turn> get_turns(const vector<vector<int>>& fld, int c){
    vector<Turn> ret;

    for (int i = 0;i < 8;i++){
        for (int j = 0;j < 8;j++){
            if (fld[i][j] == -1){
                Turn now;
                now.x = i;
                now.y = j;
                now.who = c;
                for (pii s : shift){
                    int i1 = i + s.first, j1 = j + s.second;
                    bool f1 = 0, f2 = 0, f3 = 0;
                    while (i1 >= 0 && i1 < 8 && j1 >= 0 && j1 < 8){
                        if (fld[i1][j1] == -1){
                            f3 = 1;
                            break;
                        }
                        if (fld[i1][j1] == c){
                            f2 = 1;
                            break;
                        }
                        if (fld[i1][j1] == !c){
                            f1 = 1;
                        }
                        i1 += s.first;
                        j1 += s.second;
                    }
                    if (f1 && f2 && !f3){
                        now.d.push_back(s);
                    }
                }
                if (now.d.size()) ret.push_back(now);
            }
        }
    }
    return ret;
}
vector<vector<int>> make_turn(const vector<vector<int>>& fld, Turn turn){
    vector<vector<int>> new_fld = fld;
    new_fld[turn.x][turn.y] = turn.who;
    for (pii s : turn.d){
        int x1 = turn.x + s.first, y1 = turn.y + s.second;
        while (x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && fld[x1][y1] != turn.who){
            new_fld[x1][y1] = turn.who;
            x1 += s.first;
            y1 += s.second;
        }
    }
    return new_fld;
}
double dfs(const vector<vector<int>>& field, int is_mx, double alpha, double beta, int depth, int c,const vector<vector<int>>& old_fld, int original){
    if(depth == MAXD) return calc(field, old_fld, original);
    vector<Turn> turns = get_turns(field, c);
    if (is_mx){
        double value = DBL_MIN;
        for (Turn turn : turns){
            value = max(value, dfs(make_turn(field, turn), 0, alpha, beta, depth + 1, !c, old_fld, original));
            alpha = max(alpha, value);
            if (alpha >= beta) break;
        }
        return value;
    }
    double value = DBL_MAX;
    for (Turn turn : turns){
        value = min(value, dfs(make_turn(field, turn), 1, alpha, beta, depth + 1, !c, old_fld, original));
        beta = min(beta, value);
        if (alpha >= beta) break;
    }
    return value;

}
void move(int a[8][8], const int c, int* row, int* column){
    vector<vector<int>> fld(8, vector<int>(8));
    for (int i = 0;i < 8;i++) for (int j = 0;j < 8;j++) fld[i][j] = a[i][j];
    vector<Turn> turns = get_turns(fld, c);
    // cerr << turns.size() << '\n';
    // for (Turn turn : turns){
    //     cerr << "FROM " << turn.x << ' ' << turn.y << " TURNING " << c <<"\n DIMENS: ";
    //     for (auto i : turn.d){
    //         cerr << i.first << ' ' << i.second << '\n';
    //     }

    // }
    double value = DBL_MIN, alpha = DBL_MIN, beta = DBL_MAX;
    // Turn max_ind = {{}, 0, 0, 0};
    // for (Turn turn : turns){
    //     int gg = dfs(make_turn(fld, turn), 0, alpha, beta, 1, !c, fld, c);
    //     cerr << gg << '\n';
    //     if (gg > value){
    //         max_ind = turn;
    //         value = gg;
    //     }
    //     alpha = max(value, alpha);
    // }
    // make_turn(fld, {{0, 1}, 2, 3});
    *row = turns[0].x;
    *column = turns[0].y;
}

