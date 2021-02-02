//# Burnside lemma intuition
//
//
//A lemma that helps with counting stuff.
//
//Assume you have a set **X** (lowercase **x** are elements that belong to ***X***). We will want to count some elements inside this ***X*** but with a caveat that will be explained later.
//
//
//Also assume you have a set (or more formally a group) of functions (operations) that you can apply on elements of ***X***. Call this set of functions ***G***. I will denote apply a certain function ***g*** from ***G*** on an element ***x*** as ***g(x)***.
//
//Remember: function composition ***g1*** o ***g2*** produces a new function ***g*** such that ***g(x)*** = ***g1(g2(x))*** for all x
//
//For the rest of the article, we will assume that ***G*** satisfies certain requirements.
//1) Identity: ***G*** must contain an identity element ***e***. such that ***e*** o ***g*** = ***g***, and ***e(x)*** = ***x***
//2) Inverse: each element in ***G*** must have a unique inverse that belongs to ***G***. such that ***g*** o ***ginv*** = ***e***, and ***g***(***ginv***(x)) = ***ginv***(***g***(x)) = ***x***
//3) Associativity: (g1 o g2) o ***g3*** = ***g1*** o (***g2*** o ***g3***). Also, (***g1*** o ***g2***)(***g3***(x)) = ***g1***((***g2*** o ***g3***)(x)).
//4) (Not sure 100% if this is required in this lemma, but I think it is). if g1, g2 are in ***G*** then ***g1*** o ***g2*** must be in ***G***
//Note:
//- Commutativity is NOT is no the requirements, g1 o g2 does not have to be equal to g2 o g1.
//- We are gonna refer to this set of functions as "symmetry group" from now on.
//
//
//After we stated these notations and assumptions, let's go back to what we want to count with a concrete example.
//Count number of arrays of size ***n*** with integer elements ***[1, m]***, but two arrays are considered equal if one can be obtained from the other by doing a left rotation. e.g. [1, 2, 3] = [2, 3, 1] = [3, 2, 1].
//
//Our set ***X*** is gonna be set of all possible arrays. There are ***m^n*** elements in this set (Yes, some of which we consider duplicates with our definition of equality between 2 arrays).
//
//Our symmetry group (remember the set of functions) will be the set of all functions that rotates an array of size ***n*** to the left by a certain amount.
//e.g. our set is gonna contain g_0, g_1, ... g_{n - 1}.
//g_0([1, 2, 3]) = [1, 2, 3]
//g_1([1, 2, 3]) = [2, 3, 1]
//
//We actually called this group of functions a "symmetry" group since applying one of them on an element ***x*** produces a symmetrical element ***y*** = ***g(x)***.
//Informal meaning of symmetric: x, and y are actually 2 distinct elements in set ***X***, but they are equal in our definition of equality. We will use symmetric to refer to this relation between 2 elements.
//e.g. [1, 2, 3] is not equal and not symmetric to [1, 3, 2]
//[1, 2, 3] is not equal but is symmetric to [2, 3, 1]
//[1, 2, 3] is equal and symmetric to [1, 2, 3]
//
//Unimportant note: Remember that a set contains only distinct elements. Also remember that a function is nothing more than a mapping between input and output. So ***G*** will contain only ***n*** distinct functions. we don't have g_n in our group for example since g_0 does the same mapping as g_n.
//This is important if, for example, in the problem it allowed left and right rotations. Our group is still gonna have only ***n*** function since left_x does the same mapping as right_n - x.
//So remember to define the set of your operations carefully. Include distinct behaviours. Different function names (left, right, etc..) may have the same behaviour.
//
//
//More definitions:
//- orbit(x) is the set of all elements ***y*** (***y*** in ***X*** too) such that x can reach ***y*** by applying an operation ***g*** from ***G*** on ***x***.
//orbit(x) = {y : g(x) = y, g in G and y in X}
//- stabilizer(x) is the set of all functions ***g*** such that ***g*** does not change ***x***. stabilizer(x) = {g : g(x) = x, g in G}
//
//the multiplication of the sizes of the orbit(x) and stabilizer(x) actually gives size of G, the total number of operations we have. This is not trivial but explained here: https://www.youtube.com/watch?v=BfgMdi0OkPU&list=PLDcSwjT2BF_VuNbn8HiHZKKy59SgnIAeO&index=2&ab_channel=Mathemaniac (I did not understand it 100%).
//|orbit(x)| * |stabilizier(x)| = |G|.
//
//
//The above stuff is taken from random sources and not 100% accurate and is just my intuition on all this group stuff fuckery. The rest of this is explained with much better visualizations here (it uses some of the stuff we discussed above): https://www.youtube.com/watch?v=6kfbotHL0fs&ab_channel=Mathemaniac
//
//We need to see 2 important facts:
//- orbit(x) is the exact same for all elements in orbit(x)
//- If you can reach y from x (x -> y) using an operation, and you can reach z from y (y -> z) using an operation then you can reach z from x (x -> z) using an operation. (since the composition of any two operations are indeed in G)
//- If you can reach y from x (x -> y) using an operation, and z from x (x- > z) using an operation, then you can reach z from y (y -> z) using an operation (since the inverse is indeed in G and the composition of the inverse and whatever is in G too).
//- These come from the assumptions/requirements we put on the symmetry group above.
//- |stabilizer(x)| is the same for all x in orbit(x) (Note the size of stabilizer not the stabilizer set itself, I'm not sure if it is the same too). this comes from |orbit(x)| * |stabilizer(x)| = |G|. |G| is a constant and |orbit(x)| is also the same from the point above.
//
//2 elements x, y in the same orbit are symmetric (they can be reached from one another by applying an operation).
//2 elements x, y that are not in the same orbit are NOT symmetric (they can't be reached from one another by applying an operation).
//So what we actually want to count is the number of distinct orbits.
//
//Now what we're gonna do is to count *SOMETHING* in 2 different ways such that one of them is easy to calculate and the other one contains numberOfOrbits term in it so we can deduce numberOfOrbits.
//
//this ***SOMETHING*** is gonna be the summation of |stabilizer(x)| for all x in ***X***.
//
//consider this visualization, all elements in the same orbit are denoted with same letter.
//x x | y y y | z z
//
//We have 3 orbits. any 2 elements with same letter have same orbit and same |stabilizer()|.
//So the summation can be expressed as follows:
//For each orbit:
//SOMETHING += |stabilizer(x)| * |orbit(x)|
//this is actually equal to |G|
//
//so the SOMETHING is actually numberOfOrbits * |G|.
//
//Now let's count it from another prespective.
//Go over each ***g*** in ***G*** and see how many x's is g in stabilizer(x).
//It's the same thing but instead of grouping by x's we are grouping by g's.
//
//This will probably be counted adhoc-ally depending on the problem.
//
//In this problem we will go over each g (Here different g is gonna be left rotation by a different amount). and count number of x's that it doesn't change.
//e.g. count number of arrays of size n with elements [1, m] that do not change by a left rotation of size r.
//
//now you're gonna have numberOfOrbits * |G| = SOMETHING (remember, you calculated SOMETHING adhocally) and you can get numberofOrbits easily.
//
//
//Now to the adhoc problem,
//the condition can be seen as count number of arrays such that a[i] = a[(i + r)%n] for all i.
//This will divide the array to a number of groups, each group must be equal, the number of groups is gonna be gcd(n, r), and of course the number of elements in each group is gonna be n/gcd(n, r). you've previously proved this in the drive notes.

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif

vector<string> vec_splitter(string s)
{
    s += ',';
    vector<string> res;
    while (!s.empty())
    {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}

void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM)
{
    cerr << endl;
}

template<typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T)
{
    if (idx > 0)
        cerr << ", ";
    else
        cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

typedef long long ll;
typedef long double ld;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)((x).size())
#define pb push_back
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define X first
#define Y second
//#define debug(x) cerr << #x << " : " << (x) << " "
const long double PI = 3.14159265358979323846;
const long double eps = (1e-15);
enum
{
    LESS, EQUAL, GREATER
};

int dcmp(ld x, ld y, ld EPS = eps)
{
    if (fabs(x - y) <= EPS)
        return EQUAL;
    return x > y ? GREATER : LESS;
}
const int MOD = 1000000007;
// x, y should be modded
int add(int x, int y)
{
    x += y;
    if (x >= MOD)
        x -= MOD;
    if (x < 0)
        x += MOD;
    return x;
}

int mult(int x, int y)
{
    return (1LL * x * y)%MOD;
}

int pwr(int base, int exp)
{
    int ret = 1;
    for (; exp; exp >>= 1, base = mult(base, base))
        if (exp&1)
            ret = mult(ret, base);
    return ret;
}

int modInverse(int x)
{
    return pwr(x, MOD - 2); // x % Phi(m) - 1. exists only if x, MOD are coprime
}

int divide(int a, int b)
{
    return mult(a, modInverse(b));
}


// https://codeforces.com/gym/101873/problem/B
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif
    int wallSize, faces, colors;
    cin >> wallSize >> faces >> colors;
    int options = pwr(colors, wallSize * wallSize);
    int total = pwr(options, faces);
    int sumFix = 0;
    for (int r = 0; r < faces; ++r)
        sumFix = add(sumFix, pwr(options, __gcd(faces, r)));

    int ans = divide(sumFix, faces);
    cout << ans << '\n';
}