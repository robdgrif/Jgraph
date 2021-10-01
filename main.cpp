//Robert Griffith

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <math.h>
#include <stdlib.h>

using namespace std;


struct Type{
	vector<string> names;
	vector<double> scores;
	string title;
};

void readtxt(string file, vector<Type> &type){
	ifstream fin;
	fin.open(file);

	string fname, lname;
	string combine;
	double tmpscore;

	string line;
	Type t;
	while(getline(fin, line)){
		if(line.compare("SG: Off-The-Tee") == 0){
			if(!t.title.empty()){
				type.push_back(t);
				t.title.clear();
			}
			t.title = "Off-The-Tee";
			t.names.clear();
			t.scores.clear();
		}
		else if(line.compare("SG: Approach-The-Green") == 0){
			if(!t.title.empty()){
				type.push_back(t);
				t.title.clear();
			}
			t.title = "Approach-The-Green"; 
			t.names.clear();
            t.scores.clear();
		}
		else if(line.compare("SG: Around-The-Green") == 0){
			if(!t.title.empty()){
				type.push_back(t);
				t.title.clear();
			}
			t.title = "Around-The-Green";
			t.names.clear();
            t.scores.clear();
		}
		else if(line.compare("SG: Putting") == 0){
			if(!t.title.empty()){
                type.push_back(t);
                t.title.clear();
            }
			t.title = "Putting";
			t.names.clear();
            t.scores.clear();
		}
		else if(!line.empty()){
			istringstream iss(line);
			iss >> fname >> lname >> tmpscore;
			combine = fname + " " + lname;
			t.names.push_back(combine);
			t.scores.push_back(tmpscore);
		}
		else{
			continue;
		}
	}
	type.push_back(t);

}

/*using quicksort algorithm this function sorts the input 
 * file names in alphabetical order in case user decides to 
 * order the list of names randomly
 */
int partition(Type &t, int left, int right){
	int middle = (left + right)/2;
	
	if(t.names[middle] < t.names[left]){
		swap(t.names[middle], t.names[left]);
		swap(t.scores[middle], t.scores[left]);
	}    
	if(t.names[right] < t.names[left]){
		swap(t.names[right], t.names[left]);
        swap(t.scores[right], t.scores[left]);
    }
	
	if(t.names[right] < t.names[middle]){
        swap(t.names[right], t.names[middle]);
        swap(t.scores[right], t.scores[middle]);
    }
	
	if(right-left+1 <= 3){
		return middle;
	}

	int pindex = middle;
	string pivot = t.names[pindex];

	swap(t.names[pindex], t.names[right-1]);
	swap(t.scores[pindex], t.scores[right-1]);

	int i = left;
	int j = right-1;

	while(1){
		while(t.names[++i] < pivot){}
		while(pivot < t.names[--j]){}
		if(i>=j){ break; }
		swap(t.names[i], t.names[j]);
		swap(t.scores[i], t.scores[j]);
	}

	pindex = i;
	swap(t.names[pindex], t.names[right-1]);
	swap(t.scores[pindex], t.scores[right-1]);

	return pindex;
}

//function called from main to begin sorting names alphabetically(partition())
void sortabc(Type &t, int left, int right){
    if(left < right){
		int pindex = partition(t, left, right);
		sortabc(t, left, pindex-1);
        sortabc(t, pindex+1, right);
    }
}

//total sum of each player
vector<double> sums(vector<Type> type){
	int sz = type[0].scores.size();
	vector<double> sms(sz, 0);
	for(unsigned int i = 0; i < type.size(); i++){
		for(unsigned int j = 0; j < type[i].scores.size(); j++){
			sms[j] += type[i].scores[j];
		}
	}
	return sms;
}

//using quicksort algorithm to sort players from least to greates based on sum
int partitionsum(Type &t, vector<double> &sum, int left, int right){
	int middle = (left+right)/2;

	if(sum[middle] < sum[left]){ 
		swap(sum[middle], sum[left]);
		swap(t.names[middle], t.names[left]);
		swap(t.scores[middle], t.scores[left]);
	}
	if(sum[right] < sum[left]){ 
		swap(sum[right], sum[left]);
		swap(t.names[right], t.names[left]);
		swap(t.scores[right], t.scores[left]);
	}
	if(sum[right] < sum[middle]){
		swap(sum[right], sum[middle]);
		swap(t.names[right], t.names[middle]);
		swap(t.scores[right], t.scores[middle]);
	}

	if(right-left+1 <= 3){
		return middle;
	}

	int pindex = middle;
	double pivot = sum[pindex];

	swap(sum[pindex], sum[right-1]);
	swap(t.names[pindex], t.names[right-1]);
	swap(t.scores[pindex], t.scores[right-1]);

	int i = left;
	int j = right-1;

	while(1){
		while(sum[++i] < pivot){}
		while(pivot < sum[--j]){}
		if(i >= j){ break; }
		swap(sum[i], sum[j]);
		swap(t.names[i], t.names[j]);
		swap(t.scores[i], t.scores[j]);
	}

	pindex = i;
	swap(sum[pindex], sum[right-1]);
	swap(t.names[pindex], t.names[right-1]);
	swap(t.scores[pindex], t.scores[right-1]);

	return pindex;
}

//sorting players in each category based on their total sum
void sortbysum(Type &t, vector<double> &sum, int left, int right){
	if(left < right){
		int pindex = partitionsum(t, sum, left, right);
		sortbysum(t, sum, left, pindex-1);
		sortbysum(t, sum, pindex+1, right);
	}
}

double getscore(Type t, string name, double sum){
    double score = 0.0;
    for(unsigned int i = 0; i < t.names.size(); i++){
        if(t.title == "Off-The-Tee"){
            for(unsigned int j = 0; j < t.names.size(); j++){
                if(t.names[j] == name){
                    score = sum - t.scores[j];
                    return score;
                }
            }
        }
        else if(t.title == "Approach-The-Green"){
            for(unsigned int j = 0; j < t.names.size(); j++){
                if(t.names[j] == name){
                    score = sum - t.scores[j];
                    return score;
                }
            }
        }
        else if(t.title == "Around-The-Green"){
            for(unsigned int j = 0; j < t.names.size(); j++){
                if(t.names[j] == name){
                    score = sum - t.scores[j];
                    return score;
                }
            }
        }
        else if(t.title == "Putting"){
            for(unsigned int j = 0; j < t.names.size(); j++){
                if(t.names[j] == name){
                    score = sum - t.scores[j];
                    return score;
                }
            }
        }
    }
    return score;
}

void createjgr(vector<Type> type, vector<double> sum, string file){
	string grfile = file + ".jgr";
	ofstream ofs(grfile);

	int sm = (signed)sum.size()-1;
	int c = sm-5;
	if(c < 0){
		c = -1;
	}
	//where to put score on yaxis
	int spot;
	if(sm >= 5){
		spot = 10;
	}
	else if(sm < 5){
		spot = ((sm % 5) * 2) + 2;
	}

	//loop with 5 players per page
	while(sm > 0){
	ofs << "newgraph" << "\n\n";
	
	ofs << "xaxis size 4\n" << "	min -20 max 20\n\n";
	ofs << "yaxis size 2\n" << "	min 0 max 10 nodraw draw_at 0\n\n";

	int j = spot;
	double possum = 0;
	vector<double> tmpsc(4, 0);
	
	ofs << "legend custom\n\n";

    //SET BLACK BAR AT TOTAL SUM OF EACH PLAYER
    ofs << "newcurve marktype box marksize 1 1.7\n";
    ofs << "    cfill 0 0 0\n";
	ofs << "label hjl vjb x -20 y 18.5 : Sum of Player\n";
    ofs << "    pts ";
    for(int k = sm; k > c; k--){
        ofs << sum[k] << " " << j << "  ";
        j-=2;
    }
    ofs << "\n\n";
    j=spot;

	//output into file Tee-To-Green info
	ofs << "newcurve marktype ybar cfill .29 .3 .31\n\n";
	ofs << "	marksize 1 1\n\n";
	ofs << "label hjl vjb x -20 y 16.5 : Tee to green, Positive\n";
	ofs << "	pts\n	 ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[0] > 0){
			for(unsigned int l = 0; l < tmpsc.size(); l++){
				if(tmpsc[l] > 0){
					possum += tmpsc[l];
				}
			}
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j = spot;

    ofs << "newcurve marktype ybar cfill .8 .8 .81\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x 10 y 16.5 : Tee to green, Negative\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[0] < 0){
			for(unsigned int l = 0; l < tmpsc.size(); l++){
				if(tmpsc[l] < 0){
					possum += tmpsc[l];
				}
			}
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j=spot;

	//APPROACH THE GREEN POSITIVE AND NEGATIVE
    ofs << "newcurve marktype ybar cfill 0 0 1\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x -20 y 15 : Approach the green, Positive\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[1] > 0){
			for(unsigned int l = 1; l < tmpsc.size(); l++){
				if(tmpsc[l] > 0){
					possum += tmpsc[l];
				}
			}	
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j=spot;

    ofs << "newcurve marktype ybar cfill .5 .5 1\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x 10 y 15 : Approach the green, Negative\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[1] < 0){
			for(unsigned int l = 1; l < tmpsc.size(); l++){
				if(tmpsc[l] < 0){
					possum += tmpsc[l];
				}
			}
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j=spot;

	//AROUND THE GREEN POSITIVE AND NEGATIVE
    ofs << "newcurve marktype ybar cfill 1 0 0\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x -20 y 13.5 : Around the green, Positive\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[2] > 0){
			for(unsigned int l = 2; l < tmpsc.size(); l++){
				if(tmpsc[l] > 0){
					possum += tmpsc[l];
				}
			}
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j=spot;

    ofs << "newcurve marktype ybar cfill 1 .5 .5\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x 10 y 13.5 : Around the green, Negative\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
        tmpsc[0] = type[0].scores[k];
        tmpsc[1] = type[1].scores[k];
        tmpsc[2] = type[2].scores[k];
        tmpsc[3] = type[3].scores[k];
        if(tmpsc[2] < 0){
            for(unsigned int l = 2; l < tmpsc.size(); l++){
                if(tmpsc[l] < 0){
                    possum += tmpsc[l];
                }
            }
            ofs << possum << " " << j << "  ";
            possum = 0;
        }
        j-=2;
    }
    ofs << "\n\n";
    j=spot;

	//PUTTING POSITIVE AND NEGATIVE
    ofs << "newcurve marktype ybar cfill 0 .5 0\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x -20 y 12 : Putting, Positive\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		if(tmpsc[3] > 0){
			for(unsigned int l = 3; l < tmpsc.size(); l++){
				if(tmpsc[l] > 0){
					possum += tmpsc[l];
				}
			}
			ofs << possum << " " << j << "  ";
			possum = 0;
		}
		j-=2;
	}
	ofs << "\n\n";
	j=spot;

    ofs << "newcurve marktype ybar cfill .5 1 .5\n\n";
    ofs << "    marksize 1 1\n\n";
    ofs << "label hjl vjb x 10 y 12 : Putting, Negative\n";
    ofs << "    pts\n    ";
	for(int k = sm; k > c; k--){
        tmpsc[0] = type[0].scores[k];
        tmpsc[1] = type[1].scores[k];
        tmpsc[2] = type[2].scores[k];
        tmpsc[3] = type[3].scores[k];
        if(tmpsc[3] < 0){
            for(unsigned int l = 3; l < tmpsc.size(); l++){
                if(tmpsc[l] < 0){
                    possum += tmpsc[l];
                }
            }
            ofs << possum << " " << j << "  ";
            possum = 0;
        }
        j-=2;
    }
    ofs << "\n\n";
    j=spot;

	//PRINT NAMES OF PLAYERS
	int i = 0;
	for(int k = sm; k > c; k--){
		tmpsc[0] = type[0].scores[k];
		tmpsc[1] = type[1].scores[k];
		tmpsc[2] = type[2].scores[k];
		tmpsc[3] = type[3].scores[k];
		for(unsigned int l = 0; l < tmpsc.size(); l++){
			if(tmpsc[l] > 0){
				possum += tmpsc[l];
			}
		}
		ofs << "newstring hjl vjc x " << ceil(possum)+2 << " y " << j << " : " << type[0].names[k] << "\n";
		possum = 0;
		j-=2;
		i++;
	}
	i=0;

	//subtract 5 to output remaining players
	if(c == -1){ break; }
	else if(c > 0){ 
		sm = c;
		c -= 5;
		ofs << "newpage\n";
	}
	if(c < 0){ c = -1; }
	if(sm >= 5){
		spot = 10;
	}
	else if(sm < 5){
		spot = ((sm % 5) * 2)+2;
	}
	
	}
	//./jj -P test4.jgr | ps2pdf - | convert -density 300 - -quality 100 test4.jpg 
	//cout << file << "\n";
	//string cmd = "./jj -P " + file + ".jgr | ps2pdf - | convert -density 300 - -quality 100 " + file + ".jpg";
	//system(cmd);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Error not enough arguments\n");
		return 1;
	}
	
	vector<Type> type;

	string file = argv[1];
	readtxt(file, type);
	//sort names alphabetically
	int left = 0;
	int right = type.size()-1;
	
	for(unsigned int i = 0; i < type.size(); i++){
		sortabc(type[i], left, right);
	}
	//error checking
	for(unsigned int i = 0; i < type.size(); i++){
		if(type[i].scores.size() != type[i].names.size()){
			cout << "Same names must be listed in each category.\n";
			return -1;
		}
	}
	/*for(unsigned int i = 0; i < type.size(); i++){
		if(type[0].names[i] == type[1].names[i] && type[0].names[i] == type[2].names[i] && type[0].names[i] == type[3].names[i] &&
				type[1].names[i] == type[2].names[i] && type[1].names[i] == type[3].names[i] && type[2].names[i] == type[3].names[i]){
		}
		else{
			cout << "Not all names are listed in each category\n";
			return -1;
		}
	}*/

	//obtain sum of each player
	vector<double> sms = sums(type);
	vector<double> tmpsms = sms;
	
	right = sms.size()-1;
	for(unsigned int i = 0; i < type.size(); i++){
		sms.clear();
		sms = tmpsms;
		sortbysum(type[i], sms, left, right);
	}

	string jgrfile = file.substr(0, file.size()-4);
	createjgr(type, sms, jgrfile);

	return 0;
}
