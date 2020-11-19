// I have set no. of threads to 2^no. of digits in the matrix size
// I have observed the running time is less in multiples of 4, (searching for reasons, dont know is that fully correct)
// After some certain number the increase in num of threads doesn't give significant increase or drop, so I thought take the least number
// The time kept changing, causing the analysis to be difficult and may be inacurate. 

#include<random>
#include<iostream>
#include<chrono>
#include<omp.h>
#include<math.h>

int noDigits(int N){
	int i = 0;
	while(N>0){
		N/=10;
		i++;
	}
	return i;
}

int main(int argc, char* argv[]) {
	double lbound = 0;
	double ubound = 10;
	std::uniform_real_distribution<double> urd(lbound, ubound);
	std::default_random_engine re;
	int N = atoi(argv[1]);
	float t = atof(argv[2]);

	float *mat = (float*) malloc((N+2)*(N+2)*sizeof(float));
	float *ans = (float*) malloc((N+2)*(N+2)*sizeof(float));
	float *temp;
	for(int i=0;i<=N+1;i++)
		for(int j=0;j<=N+1;j++){
			mat[i*(N+2) + j] = 0;
			ans[i*(N+2) + j] = 0;
		}
	#pragma omp parallel for collapse(2)
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			mat[i*(N+2) + j] = urd(re);
	omp_set_num_threads(pow(2, noDigits(N) - 1));
	bool cont = true;
	int iterations = 0;
	auto start = std::chrono::high_resolution_clock::now();
	while(cont) {
		cont = false;
		iterations++;
		#pragma omp parallel
		{			
		#pragma omp for collapse(2)
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++){
				float s = 5.0;
				ans[i*(N+2) + j] = mat[i*(N+2)+j] + mat[i*(N+2)+j+1] + mat[i*(N+2)+j-1] + mat[(i-1)*(N+2)+j] + mat[(i+1)*(N+2)+j];
				if(i==1||i==N)
					s--;
				if(j==1||j==N)
					s--;
				ans[i*(N+2) + j] /= s;
				if(fabs(ans[i*(N+2) + j]-mat[i*(N+2) + j]) >= t){
					cont = true;
				}
			}
		
		}
		temp = ans;
		ans = mat;
		mat = temp;
	}				
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
	std::cout<<duration.count()<<"msec "<<iterations<<" Iteartions "<<std::endl;
	return 0;
}
