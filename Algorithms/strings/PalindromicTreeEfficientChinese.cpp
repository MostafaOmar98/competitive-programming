class PalinTree{
public:
    char s[MAXN];
    int head[MAXN],nxt[MAXN],ch[MAXN],m;// 邻接表
    char nx[MAXN];// edge: from u'father to u by adding char nx[u]
    int fail[MAXN],len[MAXN],cnt[MAXN];
    int last,sz,n;
    inline int newnode(int L){
        cnt[sz]=0,len[sz]=L;head[sz]=0;
        return sz++;
    }
    inline void init(){
        m=n=sz=0;last=1;
        newnode(0);newnode(-1);
        s[0]=-1,fail[0]=1;
    }
    inline int GetFail(int v){
        while(s[n-len[v]-1]!=s[n]) v=fail[v];
        return v;
    }
    inline int add(int c){
        s[++n]=c;
        int cur=GetFail(last),i,j;
        for (i=head[cur];i;i=nxt[i]) if (nx[i]==c) break;
        if (!i){// the current node doesn't exist in current tree
            int now=newnode(len[cur]+2);// successfully insert
            int failcur=GetFail(fail[cur]);
            for (j=head[failcur];j;j=nxt[j]) if (nx[j]==c) break;
            if (j) fail[now]=ch[j];else fail[now]=0;
            nxt[++m]=head[cur];
            head[cur]=m;
            nx[m]=c;ch[m]=now;
            cnt[now]=cnt[fail[now]]+1;
            last=now;
        }else last=ch[i];// already inserted
        return cnt[last];
    }
};
PalinTree P;