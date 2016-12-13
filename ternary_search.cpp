/*
f是傳入的函數，eps表示精準度，通常設為1e-5
l,r為邊界，所以必須先預估出極值點的位置
*/
template<typename _F>
inline double ternary_search(_F f,double l,double r,double eps){
	static double m1,m2;
	while(r-l>eps){
		m1=l+(r-l)/3;
		m2=r-(r-l)/3;
		if(f(m1)>f(m2))l=m1;/*如果對象是倒U型函數，則改成 < */
		else r=m2;
	}
	return (l+r)/2;
}
