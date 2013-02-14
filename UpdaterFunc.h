//David Baird
//UpdaterFunc for the Nomekop program
//7/15/12

template<class T>
class UpdaterFunc{
    UpdaterFunc(UpdaterFunc&);
    void operator()(std::deque<T>& a){
	deque<T> b(a);
	int n = a.size();
	for(int i=0; i < n; ++i){
	    if(i == 0 || i == (n-1)){
		if(i==0){
		    if(b[i+1] >= 2)
			++a[i];
		    if(b[n-1] >= 2)
			++a[i];
		}else{
		    if(b[i-1] >= 2)
			++a[i];
		    if(b[0] >= 2)
			++a[i];
		}
	    }else{
		if(b[i+1] >= 2)
		    ++a[i];
		if(b[i-1] >= 2)
		    ++a[i];
	    }
	    if(b[i] >= 2)
		a[i] -= 2;
	}
    }
}
