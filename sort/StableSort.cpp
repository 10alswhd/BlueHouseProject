//http://habrahabr.ru/post/205290/ 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SORT_TYPE str128
#define SORT_CMP cmp128

long long NCmps=0;
long long NSwap=0;

struct str128{
	int key;
	int val;
};

void PrintArray(char *s,SORT_TYPE *arr,int Len);
bool TestArray(SORT_TYPE *arr,int Len);


int cmp128(const str128 *a,const str128 *b){
	NCmps++;
	if(a->key<b->key) return -1;
	if(a->key>b->key) return 1;
	return 0;
}


/****** Grail sorting *************/

inline void swap1(SORT_TYPE *a,SORT_TYPE *b){
	NSwap++;
	SORT_TYPE c=*a;
	*a=*b;
	*b=c;
}
inline void swapN(SORT_TYPE *a,SORT_TYPE *b,int n){
	while(n--) swap1(a++,b++);
}
void rotate(SORT_TYPE *a,int l1,int l2){
	while(l1 && l2){
		if(l1<=l2){
			swapN(a,a+l1,l1);
			a+=l1; l2-=l1;
		}else{
			swapN(a+(l1-l2),a+l1,l2);
			l1-=l2;
		}
	}
}

int BinSearchLeft(SORT_TYPE *arr,int len,SORT_TYPE *key){
	int a=-1,b=len;
	while(a<b-1){
		int c=a+((b-a)>>1);
		if(SORT_CMP(arr+c,key)>=0) b=c;
		else a=c;
	}
	return b;
}
int BinSearchRight(SORT_TYPE *arr,int len,SORT_TYPE *key){
	int a=-1,b=len;
	while(a<b-1){
		int c=a+((b-a)>>1);
		if(SORT_CMP(arr+c,key)>0) b=c;
		else a=c;
	}
	return b;
}

// cost: 2*len+nk^2/2
int FindKeys(SORT_TYPE *arr,int len,int nkeys){
	int h=1,h0=0;  // first key is always here
	int u=1;
	while(u<len && h<nkeys){
		int r=BinSearchLeft(arr+h0,h,arr+u);
		if(r==h || SORT_CMP(arr+u,arr+(h0+r))!=0){
			rotate(arr+h0,h,u-(h0+h));
			h0=u-h;
			rotate(arr+(h0+r),h-r,1);
			h++;
		}
		u++;
	}
	rotate(arr,h0,h);
	return h;
}

// cost: min(L1,L2)^2+max(L1,L2)
void Merge(SORT_TYPE *arr,int len1,int len2){
	if(len1<len2){
		while(len1){
			int h=BinSearchLeft(arr+len1,len2,arr);
			if(h!=0){
				rotate(arr,len1,h);
				arr+=h;
				len2-=h;
			}
			if(len2==0) break;
			do{
				arr++; len1--;
			} while(len1 && SORT_CMP(arr,arr+len1)<=0);
		}
	}else{
		while(len2){
			int h=BinSearchRight(arr,len1,arr+(len1+len2-1));
			if(h!=len1){
				rotate(arr+h,len1-h,len2);
				len1=h;
			}
			if(len1==0) break;
			do{
				len2--;
			} while(len2 && SORT_CMP(arr+len1-1,arr+len1+len2-1)<=0);
		}
	}
}

// arr[M..-1] - buffer, arr[0,L1-1]++arr[L1,L1+L2-1] -> arr[M,M+L1+L2-1]
void MergeLeft(SORT_TYPE *arr,int L1,int L2,int M){
	int p0=0,p1=L1; L2+=L1;
	while(p1<L2){
		if(p0==L1 || SORT_CMP(arr+p0,arr+p1)>0){
			swap1(arr+(M++),arr+(p1++));
		} else{
			swap1(arr+(M++),arr+(p0++));
		}
	}
	if(M!=p0) swapN(arr+M,arr+p0,L1-p0);
}
void MergeRight(SORT_TYPE *arr,int L1,int L2,int M){
	int p0=L1+L2+M-1,p2=L1+L2-1,p1=L1-1;

	while(p1>=0){
		if(p2<L1 || SORT_CMP(arr+p1,arr+p2)>0){
			swap1(arr+(p0--),arr+(p1--));
		} else{
			swap1(arr+(p0--),arr+(p2--));
		}
	}
	if(p2!=p0) while(p2>=L1) swap1(arr+(p0--),arr+(p2--));
}

void SmartMergeWithBuf(SORT_TYPE *arr,int *alen1,int *atype,int len2,int lkeys){
	int p0=-lkeys,p1=0,p2=*alen1,q1=p2,q2=p2+len2;
	int ftype=1-*atype;  // 1 if inverted
	while(p1<q1 && p2<q2){
		if(SORT_CMP(arr+p1,arr+p2)-ftype<0) swap1(arr+(p0++),arr+(p1++));
		else swap1(arr+(p0++),arr+(p2++));
	}
	if(p1<q1){
		*alen1=q1-p1;
		while(p1<q1) swap1(arr+(--q1),arr+(--q2));
	} else{
		*alen1=q2-p2;
		*atype=ftype;
	}
}
void SmartMergeWithoutBuf(SORT_TYPE *arr,int *alen1,int *atype,int _len2){
	int len1=*alen1,len2=_len2,ftype=1-*atype;
	
	while(len1){
		int h=ftype ? BinSearchLeft(arr+len1,len2,arr) : BinSearchRight(arr+len1,len2,arr);
		if(h!=0){
			rotate(arr,len1,h);
			arr+=h;
			len2-=h;
		}
		if(len2==0){
			*alen1=len1;
			return;
		}
		do{
			arr++; len1--;
		} while(len1 && SORT_CMP(arr,arr+len1)-ftype<0);
	}
	*alen1=len2; *atype=ftype;
}

// build blocks of length K
// input: [-K,-1] elements are buffer
// output: first K elements are buffer, blocks 2*K and last subblock sorted
void BuildBlocks(SORT_TYPE *arr,int L,int K){
	for(int m=1;m<L;m+=2){
		int u=0;
		if(SORT_CMP(arr+(m-1),arr+m)>0) u=1;
		swap1(arr+(m-3),arr+(m-1+u));
		swap1(arr+(m-2),arr+(m-u));
	}
	if(L%2) swap1(arr+(L-1),arr+(L-3));

	arr-=2;
	for(int h=2;h<K;h*=2){
		int p0=0,p1=L-2*h;
		while(p0<=p1){
			MergeLeft(arr+p0,h,h,-h);
			p0+=2*h;
		}
		int rest=L-p0;
		if(rest>h){
			MergeLeft(arr+p0,h,rest-h,-h);
		} else rotate(arr+p0-h,h,rest);
		arr-=h;
	}
	int restk=L%(2*K);
	int p=L-restk;
	if(restk<=K) rotate(arr+p,restk,K);
	else MergeRight(arr+p,K,restk-K,K);
	while(p>0){
		p-=2*K; 
		MergeRight(arr+p,K,K,K);
	}
}

// arr - starting array. arr[-lblock..-1] - buffer (if havebuf).
// lblock - length of regular blocks. First nblocks are stable sorted by 1st elements and key-coded
// keys - arrays of keys, in same order as blocks. key<midkey means stream A
// nblock2 are regular blocks from stream A. llast is length of last (irregular) block from stream B, that should go before nblock2 blocks.
// llast=0 requires nblock2=0 (no irregular blocks). llast>0, nblock2=0 is possible.
void MergeBuffersLeft(SORT_TYPE *keys,SORT_TYPE *midkey,SORT_TYPE *arr,int nblock,int lblock,bool havebuf,int nblock2,int llast){
	if(nblock==0){
		int l=nblock2*lblock;
		if(havebuf) MergeLeft(arr,l,llast,-lblock);
		else Merge(arr,l,llast);
		return;
	}

	int prest;
	int lrest=lblock;
	int frest=SORT_CMP(keys,midkey)<0 ? 0 : 1;
	int pidx=lblock;
	for(int cidx=1;cidx<nblock;cidx++,pidx+=lblock){
		prest=pidx-lrest;
		int fnext=SORT_CMP(keys+cidx,midkey)<0 ? 0 : 1;
		if(fnext==frest){
			if(havebuf) swapN(arr+prest-lblock,arr+prest,lrest);
			prest=pidx;
			lrest=lblock;
		} else{
			if(havebuf){
				SmartMergeWithBuf(arr+prest,&lrest,&frest,lblock,lblock);
			} else{
				SmartMergeWithoutBuf(arr+prest,&lrest,&frest,lblock);
			}	

		}
	}
	prest=pidx-lrest;
	if(llast){
		int plast=pidx+lblock*nblock2;
		if(frest){
			if(havebuf) swapN(arr+prest-lblock,arr+prest,lrest);
			prest=pidx;
			lrest=lblock*nblock2;
			frest=0;
		} else{
			lrest+=lblock*nblock2;
		}
		if(havebuf) MergeLeft(arr+prest,lrest,llast,-lblock);
		else Merge(arr+prest,lrest,llast);
	} else{
		if(havebuf) swapN(arr+prest,arr+(prest-lblock),lrest);
	}
	int dlblk=havebuf ? lblock : 0;
}

void SortIns(SORT_TYPE *arr,int len){
	for(int i=1;i<len;i++){
		for(int j=i-1;j>=0 && SORT_CMP(arr+(j+1),arr+j)<0;j--) swap1(arr+j,arr+(j+1));
	}
}

void LazyStableSort(SORT_TYPE *arr,int L){
	for(int m=1;m<L;m+=2){
		int u=0;
		if(SORT_CMP(arr+m-1,arr+m)>0) swap1(arr+(m-1),arr+m);
	}
	for(int h=2;h<L;h*=2){
		int p0=0,p1=L-2*h;
		while(p0<=p1){
			Merge(arr+p0,h,h);
			p0+=2*h;
		}
		int rest=L-p0;
		if(rest>h) Merge(arr+p0,h,rest-h);
	}
}

// keys are on the left of arr. Blocks of length LL combined. We'll combine them in pairs
// LL and nkeys are powers of 2. (2*LL/lblock) keys are guarantied
void CombineBlocks(SORT_TYPE *keys,SORT_TYPE *arr,int len,int LL,int lblock,bool havebuf){
	int M=len/(2*LL),lrest=len%(2*LL);
	int nkeys=(2*LL)/lblock;
	if(lrest<=LL){
		len-=lrest;
		lrest=0;
	}
	for(int b=0;b<=M;b++){
		if(b==M && lrest==0) break;
		SORT_TYPE *arr1=arr+b*2*LL;
		int NBlk=(b==M ? lrest : 2*LL)/lblock;
		SortIns(keys,NBlk+(b==M ? 1 : 0));
		int midkey=LL/lblock;
		for(int u=1;u<NBlk;u++){
			int p=u-1;
			for(int v=u;v<NBlk;v++){
				int kc=SORT_CMP(arr1+p*lblock,arr1+v*lblock);
				if(kc>0 || (kc==0 && SORT_CMP(keys+p,keys+v)>0)) p=v;
			}
			if(p!=u-1){
				swapN(arr1+(u-1)*lblock,arr1+p*lblock,lblock);
				swap1(keys+(u-1),keys+p);
				if(midkey==u-1 || midkey==p) midkey^=(u-1)^p;
			}
		}
		int nbl2=0,llast=0;
		if(b==M) llast=lrest%lblock;
		if(llast!=0){
			while(nbl2<NBlk && SORT_CMP(arr1+NBlk*lblock,arr1+(NBlk-nbl2-1)*lblock)<0) nbl2++;
		}
		MergeBuffersLeft(keys,keys+midkey,arr1,NBlk-nbl2,lblock,havebuf,nbl2,llast);
	}
	if(havebuf) while(--len>=0) swap1(arr+len,arr+len-lblock);
}

void GrailSort(SORT_TYPE *arr,int Len){
	if(Len<16){
		SortIns(arr,Len);
		return;
	}
	
	int lblock=1;
	while(lblock*lblock<Len) lblock*=2;
	int nkeys=(Len-1)/lblock+1;
	int findkeys=FindKeys(arr,Len,nkeys+lblock);
	bool havebuf=true;
	if(findkeys<nkeys+lblock){
		if(findkeys<4){
			LazyStableSort(arr,Len);
			return;
		}
		nkeys=lblock;
		while(nkeys>findkeys) nkeys/=2;
		havebuf=false;
		lblock=0;
	}
	int ptr=lblock+nkeys;
	int cbuf=havebuf ? lblock : nkeys;
	BuildBlocks(arr+ptr,Len-ptr,cbuf);

	// 2*cbuf are built
	while(Len-ptr>(cbuf*=2)){
		int lb=lblock;
		if(!havebuf){
			int nk=1;
			long long s=(long long)cbuf*findkeys/2;
			while(nk<nkeys && s!=0){
				nk*=2; s/=8;
			}
			lb=(2*cbuf)/nk;
		}
		CombineBlocks(arr,arr+ptr,Len-ptr,cbuf,lb,havebuf);
	}
	SortIns(arr,ptr);
	Merge(arr,ptr,Len-ptr);
}
/****** classic MergeInPlace *************/

void RecMerge(SORT_TYPE *A,int L1,int L2){
	if(L1<3 || L2<3){
		Merge(A,L1,L2); return;
	}
	int K;
	if(L1<L2) K=L1+L2/2;
	else K=L1/2;
	int k1=BinSearchLeft(A,L1,A+K);
	int k2=k1;
	if(k2<L1 && SORT_CMP(A+k2,A+K)==0) k2=BinSearchRight(A+k1,L1-k1,A+K)+k1;
	int m1=BinSearchLeft(A+L1,L2,A+K);
	int m2=m1;
	if(m2<L2 && SORT_CMP(A+L1+m2,A+K)==0) m2=BinSearchRight(A+L1+m1,L2-m1,A+K)+m1;
	if(k1==k2) rotate(A+k2,L1-k2,m2);
	else{
		rotate(A+k1,L1-k1,m1);
		if(m2!=m1) rotate(A+(k2+m1),L1-k2,m2-m1);
	}
	RecMerge(A+(k2+m2),L1-k2,L2-m2);
	RecMerge(A,k1,m1);
}
void RecStableSort(SORT_TYPE *arr,int L){
	for(int m=1;m<L;m+=2){
		int u=0;
		if(SORT_CMP(arr+m-1,arr+m)>0) swap1(arr+(m-1),arr+m);
	}
	for(int h=2;h<L;h*=2){
		int p0=0,p1=L-2*h;
		while(p0<=p1){
			RecMerge(arr+p0,h,h);
			p0+=2*h;
		}
		int rest=L-p0;
		if(rest>h) RecMerge(arr+p0,h,rest-h);
	}
}

/******** Tests *********/

int seed=100000001;
int rand(int k){
	seed=seed*1234565+1;
	return (int)(((long long)(seed&0x7fffffff)*k)>>31);
}


void GenArray(SORT_TYPE *arr,int *KeyCntr,int Len,int NKey){
	for(int i=0;i<NKey;i++) KeyCntr[i]=0;
	for(int i=0;i<Len;i++){
		int key=rand(NKey);
		arr[i].key=key;
		arr[i].val=KeyCntr[key]++;
	}
}

bool TestArray(SORT_TYPE *arr,int Len){
	for(int i=1;i<Len;i++){
		int dk=SORT_CMP(arr+(i-1),arr+i);
		if(dk>0) return false;
		if(dk==0 && arr[i-1].val>arr[i].val) return false;
	}
	return true;
}

void PrintArray(char *s,SORT_TYPE *arr,int Len){
	printf("%s:",s);
	for(int i=0;i<Len;i++) printf(" %d:%d",arr[i].key,arr[i].val);
	printf("\n");
}

extern "C" int xcmp(const void *a,const void *b){
	return SORT_CMP((const SORT_TYPE *)a,(const SORT_TYPE *)b);
}

void qtest(SORT_TYPE *arr,int Len){
	qsort(arr,Len,sizeof(SORT_TYPE),xcmp);
}

void Check(SORT_TYPE *arr,int *KeyCntr,int Len,int NKey,bool alg){
	GenArray(arr,KeyCntr,Len,NKey);
	printf("%s: N=%d, NK=%d\n",alg ? "GrailSort" : "InPlaceMergeSort",Len,NKey);
	//PrintArray("Input",arr,Len);
	NCmps=NSwap=0;
	long ct=clock();
	if(alg) GrailSort(arr,Len);
	else RecStableSort(arr,Len);
	printf("Cmps:%I64d Swaps:%I64d, time=%ld ms\n",NCmps,NSwap,clock()-ct);
	//PrintArray("Result",arr,Len);
	bool ok=TestArray(arr,Len);
	if(ok){
		printf("Ok\n");
	}else{
		printf("Fail\n");
	}
}



void main(){
	int NMax=100000000;
	int NMaxKey=100000;
	SORT_TYPE *A=new SORT_TYPE[NMax];
	int *Keys=new int[NMaxKey];

	for(int u=100;u<=NMax;u*=10){
		for(int v=1;v<=u && v<=NMaxKey;v*=2){
			Check(A,Keys,u,v,false);
			Check(A,Keys,u,v,true);
		}
	}
}
