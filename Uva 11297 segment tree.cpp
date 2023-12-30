#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 2000 + 10;

int Max[maxn][maxn], Min[maxn][maxn], n;
int xo, xleaf, x1, y1, x2, y2, x, y, v, vmax, vmin;
	
void build1D(int o, int l, int r){
	if(l == r){
		if(xleaf){
			scanf("%d", &v);
			Max[xo][o] = Min[xo][o] = v;
			return;
		}
		Max[xo][o] = max(Max[xo*2][o], Max[xo*2+1][o]);
		Min[xo][o] = min(Min[xo*2][o], Min[xo*2+1][o]);
	}
	else{
		int mid = (l+r) / 2;
		build1D(o*2, l, mid);
		build1D(o*2+1, mid+1, r);
		Max[xo][o] = max(Max[xo][o*2], Max[xo][o*2+1]);
		Min[xo][o] = min(Min[xo][o*2], Min[xo][o*2+1]);
	}
}
	
void build2D(int o, int l, int r){
	if(l == r){
		xleaf = 1;
		xo = o;
		build1D(1, 1, n);
	}
	else{
		int mid = (l+r) / 2;
		build2D(o*2, l, mid);
		build2D(o*2+1, mid+1, r);
		xleaf = 0;
		xo = o;
		build1D(1, 1, n);
	}
}

void query1D(int o, int l, int r){
	if(y1 <= l && r <= y2){
		vmax = max(vmax, Max[xo][o]);
		vmin = min(vmin, Min[xo][o]);
	}		
	else{
		int mid = (l+r) / 2;
		if(y1 <= mid){
			query1D(o*2, l, mid);
		}
		if(mid < y2){
			query1D(o*2+1, mid+1, r);
		}
	}
}

void query2D(int o, int l, int r){
	if(x1 <= l && r <= x2){
		xo = o;
		query1D(1, 1, n);
	}
	else{
		int mid = (l+r) / 2;
		if(x1 <= mid){
			query2D(o*2, l, mid);
		}
		if(mid < x2){
			query2D(o*2+1, mid+1, r);
		}
	}
}

void modify1D(int o, int l, int r){
	if(l == r){
		if(xleaf){
			Max[xo][o] = Min[xo][o] = v;
			return;
		}
		Max[xo][o] = max(Max[xo*2][o], Max[xo*2+1][o]);
		Min[xo][o] = min(Min[xo*2][o], Min[xo*2+1][o]);
	}
	else{
		int mid = (l+r) / 2;
		if(y <= mid){
			modify1D(o*2, l, mid);
		}
		else{
			modify1D(o*2+1, mid+1, r);
		} 
		Max[xo][o] = max(Max[xo][o*2], Max[xo][o*2+1]);
		Min[xo][o] = min(Min[xo][o*2], Min[xo][o*2+1]);
	}
}

void modify2D(int o, int l, int r){
	if(l == r){
		xleaf = 1;
		xo = o;
		modify1D(1, 1, n);
	}
	else{
		int mid = (l+r) / 2;
		if(x <= mid){
			modify2D(o*2, l, mid);
		}
		else{
			modify2D(o*2+1, mid+1, r);
		}
		xleaf = 0;
		xo = o;
		modify1D(1, 1, n);
	}
}

int main()
{
	scanf("%d", &n);
	build2D(1, 1, n);
	
	int Q;
	char op[10];
	scanf("%d", &Q);
	while(Q--)
	{
		scanf("%s", op);
		if(op[0] == 'q'){
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			vmin = INF, vmax = -INF;
			query2D(1, 1, n);
			printf("%d %d\n", vmax, vmin);
		}
		else{
			scanf("%d %d %d", &x, &y, &v);
			modify2D(1, 1, n);
		}
	}
}
