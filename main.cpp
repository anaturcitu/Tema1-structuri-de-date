#include <fstream>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;

ifstream f("citire.in");
ofstream g("afisare.out");

int lungime_elem_max(std::vector<long long> v, long long n)
{
    long long x, k=0, max1=-1, i;
    for(i = 0; i<n; i++)
    {
        x = v[i];
        k=0;
        while(x>0)
        {
            k++;
            x = x/10;
        }
        if(k>max1)
            max1 = k;
    }

    return max1;
}

void radix_sort(std::vector<long long> &v, long long n)
{
    long long a, x, k, p=1, i, j;
    std::queue<long long> q[10];

    int lmax = lungime_elem_max(v, n);

    for(i=1; i<=lmax; i++)
    {
        for(j=0; j<n; j++)
        {
            a = (v[j]/p)%10;
            q[a].push(v[j]);
        }

        k=0;
        for(j=0; j<=9; j++)
        {

            while(!q[j].empty())
            {
                x = q[j].front();
                v[k]=x;
                q[j].pop();
                k++;
            }
        }
        p = p*10;
    }
}


void merge_sort2(std::vector<long long> &v, long long st, long long dr)
{
    if(v[st] > v[dr])
        swap(v[st], v[dr]);
}

void merge_sort3(std::vector<long long> &v, long long st, long long dr, long long m)
{
    long long i, j, i1, j1, k=0;
    std::vector<long long> c;
    i = st;
    j = m+1;

    while(i<=m && j<=dr)
    {
        if(v[i] < v[j])
        {
            c.push_back(v[i]);
            i++;
            k++;
        }
        else
        {
            c.push_back(v[j]);
            j++;
            k++;
        }
    }

    for(i1=i; i1<=m; i1++)
    {
        c.push_back(v[i1]);
        k++;
    }

    for(j1=j; j1<=dr; j1++)
    {
        c.push_back(v[j1]);
        k++;
    }

    k=0;
    for(i=st; i<=dr; i++)
    {
        v[i]=c[k];
        k++;
    }
}

void merge_sort1(std::vector<long long> &v, long long st, long long dr)
{
    long long m;
    m = (st + dr)/2;

    if(dr - st < 1)
        merge_sort2(v, st, dr);

    else
    {
        merge_sort1(v, st, m);
        merge_sort1(v, m+1, dr);

        merge_sort3(v, st, dr, m);
    }
}

void merge_sort(std::vector<long long> &v, long long n)
{
    long long st = 0, dr = n-1;
    merge_sort1(v, st, dr);
}

void shell_sort(std::vector<long long> &v, long long n)
{
    long long k, i, t, j;
    for(k=n/2; k>0; k=k/2)
    {
        for(i=k; i<n; i++)
        {
            t = v[i];

            for(j=i; j>=k && v[j-k]>t; j-=k)
                v[j] = v[j-k];

            v[j] = t;
        }
    }
}

void counting_sort(std::vector<long long> &v, long long n)
{
    std::vector<long long> fv(100000);
    long long i, max1=-1, k=0;
    for(i=0; i<n; i++)
    {
        fv[v[i]]++;
        if(v[i] > max1)
            max1 = v[i];
    }

    for(i=0; i<=max1; i++)
        while(fv[i]>0)
        {
            v[k] = i;
            fv[i]--;
            k++;
        }
}

void insertion_sort(std::vector<long long> &v, long long n)
{
    long long i, j;
    for(i=1; i<n; i++)
        for(j=i; j>0; j--)
        {
            if(v[j] < v[j-1])
                swap(v[j-1], v[j]);
        }
}

void algoritm_sortare_nativ(std::vector<long long> &v)
{
    sort(v.begin(), v.end());
}

void afisare(std::vector<long long> v, long long n, clock_t start, clock_t stop, int k1)
{
    if(k1==1)
        g<<"RadixSort:"<<'\n';
    else if(k1==2)
        g<<"MergeSort:"<<'\n';
    else if(k1==3)
        g<<"ShellSort:"<<'\n';
    else if(k1==4)
        g<<"CountingSort:"<<'\n';
    else if(k1==5)
        g<<"InsertionSort:"<<'\n';
    else
        g<<"Algoritm de sortare nativ:"<<'\n';

    g<<"Numerele sortate:"<<'\n';

    for(long long i=0; i<n; i++)
        g<<v[i]<<' ';

    g<<'\n'<<"Timpul de executie: ";

    g<<fixed<<(double)(stop-start)/CLOCKS_PER_SEC;
    g<<" secunde"<<'\n'<<'\n';
}

int main()
{
    long long n, nr_teste, x, i, k, MAX;
    clock_t start, stop;
    std::vector <long long> v;
    std::vector <long long> v1;

    f>>nr_teste;
    for(k=1; k<=nr_teste; k++)
    {
        f>>n;
        f>>MAX;

        srand(time(0));
        for(i=0; i<n; i++)
        {
            x = rand()%MAX;

            v.push_back(x);
            v1.push_back(x);
        }

        g<<"Testul "<<k<<":"<<'\n';

        for(int k1=1; k1<=6; k1++)
        {
            v = v1;

            start = clock();

            if(k1==1)
                radix_sort(v, n);
            else if(k1==2)
                merge_sort(v, n);
            else if(k1==3)
                shell_sort(v, n);
            else if(k1==4)
                counting_sort(v,n);
            else if(k1==5)
                insertion_sort(v, n);
            else
                algoritm_sortare_nativ(v);

            stop = clock();
            afisare(v, n, start, stop, k1);
        }
        g<<'\n';
    }
    return 0;
}
