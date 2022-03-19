#include <bits/stdc++.h>
using namespace std;

struct fraction {
    int64_t licz, mian;
    fraction() = default;
    fraction(int64_t licz, int64_t mian) : licz(licz), mian(mian) {normalize();}
    void normalize() {
        int64_t gc = __gcd(abs(licz), abs(mian));
        licz /= gc;
        mian /= gc;
        if (mian < 0) {
            licz *= -1;
            mian *= -1;
        }
    }
    fraction operator*=(const fraction &other) {
        licz *= other.licz;
        mian *= other.mian;
        normalize();
        return *this;
    }
    fraction operator/=(const fraction &other) {
        licz *= other.mian;
        mian *= other.licz;
        normalize();
        return *this;
    }
    fraction operator+=(const fraction &other) {
        licz *= other.mian;
        licz += mian * other.licz;
        mian *= other.mian;
        normalize();
        return *this;
    }
    fraction operator-=(const fraction &other) {
        licz *= other.mian;
        licz -= mian * other.licz;
        mian *= other.mian;
        normalize();
        return *this;
    }
    fraction operator*(const fraction &other) const {
        return fraction(*this) *= other;
    }
    fraction operator/(const fraction &other) const {
        return fraction(*this) /= other;
    }
    fraction operator+(const fraction &other) const {
        return fraction(*this) += other;
    }
    fraction operator-(const fraction &other) const {
        return fraction(*this) -= other;
    }
    bool operator==(const fraction &other) const {
        return licz == other.licz && mian == other.mian;
    }
    bool operator!=(const fraction &other) const {
        return !(*this == other);
    }
    // 0iq
    /* fraction operator-() { */
    /*     licz *= -1; */
    /*     return *this; */
    /* } */
    fraction operator-() {
        fraction nwfrac = fraction(*this);
        nwfrac.licz *= -1;
        return nwfrac;
    }
};

istream &operator>>(istream &is, fraction &f) {
    string tmp;
    is >> tmp;
    size_t dv = tmp.find('/');
    if (dv == tmp.npos) {
        f = fraction(stoll(tmp), 1);
    }
    else {
        f = fraction(stoll(tmp.substr(0, dv)), stoll(tmp.substr(dv + 1)));
    }
    return is;
}

/* ostream &operator<<(ostream &os, const fraction &f) { */
/*     os << f.licz; */
/*     if (f.mian != 1) { */
/*         os << '/' << f.mian; */
/*     } */
/*     return os; */
/* } */

ostream &operator<<(ostream &os, const fraction &f) {
    // lol
    /* if (f.mian != 1) { */
    if (f.mian == 1) {
        os << f.licz;
    }
    else {
        if (f.licz >= 0)
            os << "\\frac{" << f.licz << "}{" << f.mian << "}";
        else
            os << "-\\frac{" << -f.licz << "}{" << f.mian << "}";
    }
    return os;
}

string header = R"(
    \usepackage{amsmath}
    \usepackage{array}
    \allowdisplaybreaks
    \makeatletter
    \newcounter{elimination@steps}
    \newcolumntype{R}[1]{>{\raggedleft\arraybackslash$}p{#1}<{$}}
    \def\elimination@num@rights{}
    \def\elimination@num@variables{}
    \def\elimination@col@width{}
    \newenvironment{elimination}[4][0]
    {
        \setcounter{elimination@steps}{0}
        \def\elimination@num@rights{#1}
        \def\elimination@num@variables{#2}
        \def\elimination@col@width{#3}
        \renewcommand{\arraystretch}{#4}
        \start@align\@ne\st@rredtrue\m@ne
    }
    {
        \endalign
        \ignorespacesafterend
    }
    \newcommand{\eliminationstep}[2]
    {
        \ifnum\value{elimination@steps}>0\\\Rightarrow\quad\fi
        \left[
            \ifnum\elimination@num@rights>0
                \begin{array}
                {@{}*{\elimination@num@variables}{R{\elimination@col@width}}
                |@{}*{\elimination@num@rights}{R{\elimination@col@width}}}
            \else
                \begin{array}
                {@{}*{\elimination@num@variables}{R{\elimination@col@width}}}
            \fi
                #1
            \end{array}
        \right]
        & \quad
        \begin{array}{l}
            #2
        \end{array}
        \addtocounter{elimination@steps}{1}
    }
    \makeatother
)";

string sample = R"(
3 4
1/2 -1 0 2
0 1 -1 2
-1 0 1/2 1
)";

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,m;
    int xx;
    /* cin >> n >> m; */
    cin >> n >> xx;
    m = n;
    fraction mat[n][m];
    /* int a[n], b[m]; */
    /* int64_t a[n], b[m]; */
    /* for(int i = 0; i < n; ++i) */
    /*     cin >> a[i]; */
    /* for(int i = 0; i < m; ++i) */
    /*     cin >> b[i]; */
    for (int i = 0; i < n; ++i)
        for (int x = 0; x < m; ++x)
            cin >> mat[i][x];
            /* mat[i][x] = fraction(a[i] * b[x],1); */
    /* for(int i = 0; i < n; ++i) */
    /*     mat[i][i] += fraction(xx,1); */
    /* string beg = "\\begin{elimination}{" + to_string(m) +  "}{1.75em}{1.1}"; */
    cout <<  "\\begin{elimination}{" << m << "}{1.75em}{1.1}\n";
    /* for (int i = 0; i < min(n,m); ++i) { */
    for (int i = 0; i < m; ++i) {
        int wh = -1;
        for (int x = 0; x < n; ++x) {
            if (count_if(mat[x], mat[x] + i, [](auto x){return x.licz != 0;}) == 0 && mat[x][i].licz) {
                wh = x;
                break;
            }
        }
        if (wh == -1)
            continue;
        vector<pair<int, fraction>> vec;
        fraction oldmat[n][m];
        memcpy(oldmat, mat, sizeof mat);
        /* for (int x = wh + 1; x < n; ++x) { */
        for (int x = 0; x < n; ++x) {
            /* if (mat[x][i].licz == 0) */
            if (wh == x || mat[x][i].licz == 0)
                continue;
            fraction factor = -mat[x][i] / mat[wh][i];
            for (int j = i; j < m; ++j) {
                mat[x][j] += mat[wh][j] * factor;
            }
            vec.push_back({x, factor});
        }
        if (!vec.empty()) {
            cout << "\t\\eliminationstep\n";
            cout << "\t{\n";
            for (int i = 0; i < n; ++i) {
                cout << "\t\t";
                for (int x = 0; x < m; ++x) {
                    cout << oldmat[i][x];
                    if (x + 1 != m)
                        cout << " & ";
                }
                if (i + 1 != n)
                    cout << " \\\\";
                cout << '\n';
            }
            cout << "\t}\n";
            cout << "\t{\n";
            auto it = vec.begin();
            for (int x = 0; x < n; ++x) {
                cout << "\t\t";
                while (it != vec.end() && it->first < x)
                    ++it;
                if (it != vec.end() && it->first == x) {
                    // 1-indexed conversion
                    // + vs -?
                    /* cout << "R_{" << x + 1 << "} - " << -it->second << " R_{" << wh + 1 << "} "; */
                    // Also, pominięcie factora jak wynosi 1 lub -1 (poza znakiem)
                    if (it->second.licz >= 0) {
                        if (it->second != fraction(1,1))
                            cout << "R_{" << x + 1 << "} + " << it->second << " R_{" << wh + 1 << "} ";
                        else
                            cout << "R_{" << x + 1 << "} + R_{" << wh + 1 << "} ";
                    }
                    else {
                        if (-it->second != fraction(1,1)) {
                            cout << "R_{" << x + 1 << "} - " << -it->second << " R_{" << wh + 1 << "} ";
                        }
                        else {
                            cout << "R_{" << x + 1 << "} - R_{" << wh + 1 << "} ";
                        }
                    }
                }
                cout << "\\\\\n";
            }
            cout << "\t}\n";
        }
        /* for (int i = 0; i < n; ++i) { */
        /*     for (int x = 0; x < m; ++x) */
        /*         cout << mat[i][x] << ' '; */
        /*     cout << '\n'; */
        /* } */
        /* cout << '\n'; */
    }
    {
        vector<pair<int, fraction>> vec;
        fraction oldmat[n][m];
        memcpy(oldmat, mat, sizeof mat);
        for (int i = 0; i < n; ++i) {
            for (int x = 0; x < m; ++x) {
                if (mat[i][x].licz) {
                    fraction factor = fraction(1,1) / mat[i][x];
                    for (int j = x; j < m; ++j) {
                        mat[i][j] *= factor;
                    }
                    vec.push_back({i, factor});
                    break;
                }
            }
        }
        if (!vec.empty()) {
            cout << "\t\\eliminationstep\n";
            cout << "\t{\n";
            for (int i = 0; i < n; ++i) {
                cout << "\t\t";
                for (int x = 0; x < m; ++x) {
                    cout << oldmat[i][x];
                    if (x + 1 != m)
                        cout << " & ";
                }
                if (i + 1 != n)
                    cout << " \\\\";
                cout << '\n';
            }
            cout << "\t}\n";
            cout << "\t{\n";
            auto it = vec.begin();
            for (int x = 0; x < n; ++x) {
                cout << "\t\t";
                while (it != vec.end() && it->first < x)
                    ++it;
                if (it != vec.end() && it->first == x) {
                    // 1-indexed conversion
                    // + vs -?
                    /* cout << "R_{" << x + 1 << "} - " << -it->second << " R_{" << x + 1 << "} "; */
                    if (it->second.licz >= 0) {
                        if (it->second != fraction(1,1))
                            cout << "R_{" << x + 1 << "} + " << it->second << " R_{" << x + 1 << "} ";
                        else
                            cout << "R_{" << x + 1 << "} + R_{" << x + 1 << "} ";
                    }
                    else {
                        if (-it->second != fraction(1,1)) {
                            cout << "R_{" << x + 1 << "} - " << -it->second << " R_{" << x + 1 << "} ";
                        }
                        else {
                            cout << "R_{" << x + 1 << "} - R_{" << x + 1 << "} ";
                        }
                    }
                }
                cout << "\\\\\n";
            }
            cout << "\t}\n";
        }
    }
    {
        cout << "\t\\eliminationstep\n";
        cout << "\t{\n";
        for (int i = 0; i < n; ++i) {
            cout << "\t\t";
            for (int x = 0; x < m; ++x) {
                cout << mat[i][x];
                if (x + 1 != m)
                    cout << " & ";
            }
            if (i + 1 != n)
                cout << " \\\\";
            cout << '\n';
        }
        cout << "\t}\n";
        cout << "\t{\n";
        cout << "\t}\n";
    }
    cout << "\\end{elimination}\n";
    /* for (int i = 0; i < n; ++i) { */
    /*     for (int x = 0; x < m; ++x) */
    /*         cout << mat[i][x] << ' '; */
    /*     cout << '\n'; */
    /* } */
    /* cout << '\n'; */
    // w8, moge wsm od razu all kolumnsy?
    // wsm rowy, nie kolumnsy
    // -> yep, profit
    /* for (int i = m - 1; i >= 0; --i) { */
    /*     int wh = -1; */
    /*     for (int x = n - 1; x >= 0; --x) { */
    /*         if (count_if(mat[x], mat[x] + i, [](auto x){return x.licz != 0;}) == 0 && mat[x][i].licz) { */
    /*             wh = x; */
    /*             break; */
    /*         } */
    /*     } */
    /*     if (wh == -1) */
    /*         continue; */
    /*     for (int x = wh - 1; x >= 0; --x) { */
    /*         if (mat[x][i].licz == 0) */
    /*             continue; */
    /*         fraction factor = -mat[x][i] / mat[wh][i]; */
    /*         whatis(factor) */
    /*         for (int j = i; j < m; ++j) { */
    /*             mat[x][j] += mat[wh][j] * factor; */
    /*         } */
    /*     } */
    /*     for (int i = 0; i < n; ++i) { */
    /*         for (int x = 0; x < m; ++x) */
    /*             cout << mat[i][x] << ' '; */
    /*         cout << '\n'; */
    /*     } */
    /* cout << '\n'; */
    /* } */
}
