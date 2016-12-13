/***************************************************************************/
/*                               micro-Max,                                */
/* A chess program smaller than 2KB (of non-blank source), by H.G. Muller  */
/***************************************************************************/
/* version 4.0 (1752 characters) features:                                 */
/* - recursive negamax search                                              */
/* - quiescence search with recaptures                                     */
/* - recapture extensions                                                  */
/* - (internal) iterative deepening                                        */
/* - best-move-first 'sorting'                                             */
/* - a hash table storing score and best move                              */
/* - full FIDE rules (expt minor promotion) and move-legality checking     */

/* Rehash sacrificed, simpler retrieval. Some characters squeezed out.     */
/* No hash-table clear, single-call move-legality checking based on K==I   */

#define W while
#define K(A,B) *(int*)(T+A+(B&8)+S*(B&7))
#define J(A) K(y+A,b[y])-K(x+A,u)-K(H+A,t)

#define U (1<<24)
struct _ {int K,V;char X,Y,D;} A[U];           /* hash table, 16M+8 entries*/

int M=136,S=128,I=8e3,C=799,Q,O,K,N;           /* M=0x88                   */

char L,
w[]={0,1,1,3,-1,3,5,9},                        /* relative piece values    */
o[]={-16,-15,-17,0,1,16,0,1,16,15,17,0,14,18,31,33,0, /* step-vector lists */
     7,-1,11,6,8,3,6,                          /* 1st dir. in o[] per piece*/
     6,3,5,7,4,5,3,6},                         /* initial piece setup      */
b[129],                                        /* board: half of 16x8+dummy*/
T[1035],                                       /* hash translation table   */

n[]=".?+nkbrq?*?NKBRQ";                        /* piece symbols on printout*/

D(k,q,l,e,J,Z,E,z,n)    /* recursive minimax search, k=moving side, n=depth*/
int k,q,l,e,J,Z,E,z,n;  /* (q,l)=window, e=current eval. score, E=e.p. sqr.*/
{                       /* e=score, z=prev.dest; J,Z=hashkeys; return score*/
 int j,r,m,v,d,h,i,F,G,s;
 char t,p,u,x,y,X,Y,H,B;
 struct _*a=A+(J+k*E&U-1);                     /* lookup pos. in hash table*/

 q--;                                          /* adj. window: delay bonus */
 d=a->D;m=a->V;X=a->X;Y=a->Y;                  /* resume at stored depth   */
 if(a->K-Z|                                    /* miss: other pos. or empty*/
  !(m<=q|X&8&&m>=l|X&S))                       /*   or window incompatible */
  d=Y=0;                                       /* start iter. from scratch */
 X&=~M;                                        /* start at best-move hint  */

 W(d++<n||                                     /* iterative deepening loop */
   z==8&K==I&&(N<1e6&d<98||                    /* root: deepen upto time   */
   (K=X,L=Y&~M,d=2)))                          /* time's up: go do best    */
 {x=B=X;                                       /* start scan at prev. best */
  h=Y&S;                                       /* request try noncastl. 1st*/
  m=d>1?-I:e;                                  /* unconsidered:static eval */
  N++;                                         /* node count (for timing)  */
  do{u=b[x];                                   /* scan board looking for   */
   if(u&k)                                     /*  own piece (inefficient!)*/
   {r=p=u&7;                                   /* p = piece type (set r>0) */
    j=o[p+16];                                 /* first step vector f.piece*/
    W(r=p>2&r<0?-r:-o[++j])                    /* loop over directions o[] */
    {A:                                        /* resume normal after best */
     y=x;F=G=S;                                /* (x,y)=move, (F,G)=castl.R*/
     do{                                       /* y traverses ray, or:     */
      H=y=h?Y^h:y+r;                           /* sneak in prev. best move */
      if(y&M)break;                            /* board edge hit           */
      m=E-S&b[E]&&y-E<2&E-y<2?I:m;             /* bad castling             */
      if(p<3&y==E)H^=16;                       /* shift capt.sqr. H if e.p.*/
      t=b[H];if(t&k|p<3&!(y-x&7)-!t)break;     /* capt. own, bad pawn mode */
      i=99*w[t&7];                             /* value of capt. piece t   */
      m=i<0?I:m;                               /* K capture                */
      if(m>=l)goto C;                          /* abort on fail high       */

      if(s=d-(y!=z))                           /* remaining depth(-recapt.)*/
      {v=p<6?b[x+8]-b[y+8]:0;                  /* center positional pts.   */
       b[G]=b[H]=b[x]=0;b[y]=u|32;             /* do move, set non-virgin  */
       if(!(G&M))b[F]=k+6,v+=30;               /* castling: put R & score  */
       if(p<3)                                 /* pawns:                   */
       {v-=9*((x-2&M||b[x-2]-u)+               /* structure, undefended    */
              (x+2&M||b[x+2]-u)-1);            /*        squares plus bias */
        if(y+r+1&S)b[y]|=7,i+=C;               /* promote p to Q, add score*/
       }
       v=-D(24-k,-l,m>q?-m:-q,-e-v-i,          /* recursive eval. of reply */
            J+J(0),Z+J(8)+G-S,F,y,s);          /* J,Z: hash keys           */
       if(z&8&&K-I)                            /* move pending: check legal*/
       {if(v+I&&x==K&y==L)                     /*   if move found in root  */
        {Q=-e-i;O=F;return l;}                 /*   & not in check, signal */
        v=m;                                   /* (prevent fail-lows on    */
       }                                       /*   K-capt. replies)       */
       b[G]=k+6;b[F]=b[y]=0;b[x]=u;b[H]=t;     /* undo move,G can be dummy */
       if(v>m)                                 /* new best, update max,best*/
        m=v,X=x,Y=y|S&F;                       /* mark double move with S  */
       if(h){h=0;goto A;}                      /* redo after doing old best*/
      }
      if(x+r-y|u&32|                           /* not 1st step,moved before*/
         p>2&(p-4|j-7||                        /* no P & no lateral K move,*/
         b[G=x+3^r>>1&7]-k-6                   /* no virgin R in corner G, */
         ||b[G^1]|b[G^2])                      /* no 2 empty sq. next to R */
        )t+=p<5;                               /* fake capt. for nonsliding*/
      else F=y;                                /* enable e.p.              */
     }W(!t);                                   /* if not capt. continue ray*/
  }}}W((x=x+9&~M)-B);                          /* next sqr. of board, wrap */
C:if(m>I-M|m<M-I)d=99;                         /* mate holds to any depth  */
  m=m+I?m:-D(24-k,-I,I,0,J,Z,S,S,1);           /* best loses K: (stale)mate*/
  a->K=Z;a->V=m;a->D=d;                        /* always store in hash tab */
  a->X=X|8*(m>q)|S*(m<l);a->Y=Y;               /* move, type (bound/exact),*/
/*if(z==8)printf("%2d ply, %9d searched, score=%6d by %c%c%c%c\n",d-1,N-S,m,
     'a'+(X&7),'8'-(X>>4),'a'+(Y&7),'8'-(Y>>4&7)); /* uncomment for Kibitz */
 }                                             /*    encoded in X S,8 bits */
 return m+=m<e;                                /* delayed-loss bonus       */
}

main()
{
 int j,k=8,*p,c[9];

 K=8;W(K--)
 {b[K]=(b[K+112]=o[K+24]+8)+8;b[K+16]=18;b[K+96]=9;  /* initial board setup*/
  L=8;W(L--)b[16*L+K+8]=(K-4)*(K-4)+(L-3.5)*(L-3.5); /* center-pts table   */
 }                                                   /*(in unused half b[])*/
 N=1035;W(N-->M)T[N]=rand()>>9;

 W(1)                                                /* play loop          */
 {N=-1;W(++N<121)
   printf(" %c",N&8&&(N+=7)?10:n[b[N]&15]);          /* print board        */
  p=c;W((*p++=getchar())>10);                        /* read input line    */
  K=I;                                               /* invalid move       */
  if(*c-10)K=*c-16*c[1]+C,L=c[2]-16*c[3]+C;          /* parse entered move */
  k^=D(k,-I,I,Q,1,j++,O,8,2)-I?0:24;                 /* think or check & do*/
 }
}
