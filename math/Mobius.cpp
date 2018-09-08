int mob[10000005];
int noprime[10000005];
int P[1000005];
int MAX=10000000;
void Mobius()
{
    std::fill(noprime, noprime + 10000000, 1);
    int pnum = 0;
    mob[1] = 1;
    for(int i = 2; i < MAX; i++)
    {
        if(noprime[i])
        {
            P[pnum ++] = i;
            mob[i] = -1;
        }
        for(int j = 0; j < pnum && i * P[j] < MAX; j++)
        {
            noprime[i * P[j]] = false;
            if(i % P[j] == 0)
            {
                mob[i * P[j]] = 0;
                break;
            }
            mob[i * P[j]] = -mob[i];
        }
    }
}

ll prime[maxn],mob[maxn],vis[maxn],cnt;

void Mobius(){
    memset(prime,0,sizeof(prime));
    memset(mob,0,sizeof(mob));
    memset(vis,0,sizeof(vis));
    mob[1] = 1;
    cnt = 0;
    for(ll i = 2;i < maxn; i++){
        if(!vis[i]){
            prime[cnt++] = i;
            mob[i] = -1;
        }
        for(ll j = 0;j < cnt&&i*prime[j] < maxn;j++){
            vis[i*prime[j]] = 1;
            if(i%prime[j]) mob[i*prime[j]] = -mob[i];
            else{
                mob[i*prime[j]] = 0;
                break;
            }
        }
    }
}
