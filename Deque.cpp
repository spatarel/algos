#define DEQ_LEN 25000

class Deque{
	private:
		int EsteMin, EsteMax;
		int Vec0, Vec1;
		int Vec[DEQ_LEN+1];
		int Min0, Min1;
		int Min[DEQ_LEN+1];
		int MinPos[DEQ_LEN+1];
		int Max0, Max1;
		int Max[DEQ_LEN+1];
		int MaxPos[DEQ_LEN+1];
	public:
		void Init(int min, int max);
		void Add(int val);
		void Rem(void);
		int  GetMin(void);
		int  GetMax(void);
};

inline void Deque::Init(int min, int max){
	Vec0 = 1;
	Vec1 = 0;
	EsteMin = min;
	EsteMax = max;
}

inline void Deque::Add(int val){
	Vec[++Vec1] = val;
	if (Vec0 == Vec1){
		Min0 = Min1 = Max0 = Max1 = 1;
		Min[1] = Max[1] = val;
		MinPos[1] = MaxPos[1] = 1;
	}else{
		int pos;
		if (EsteMin){
			for(pos=Min1;Min[pos]>=val && pos>=Min0;pos--);
			Min[Min1=pos+1] = val ;
			MinPos[Min1   ] = Vec1;
		}
		if (EsteMax){
			for(pos=Max1;Max[pos]<=val && pos>=Max0;pos--);
			Max[Max1=pos+1] = val ;
			MaxPos[Max1   ] = Vec1;
		}
	}
}

inline void Deque::Rem(void){
	if (MinPos[Min0] == Vec0) Min0++;
	if (MaxPos[Max0] == Vec0) Max0++;
	Vec0++;
}

inline int Deque::GetMin(void){
	return Min[Min0];
}

inline int Deque::GetMax(void){
	return Max[Max0];
}
