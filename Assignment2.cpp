using namespace std;
#include <iostream> 
#include <string> 
#include <stdlib.h>

class Bucket{
	public:
	int value;
	int key;
	Bucket * next;
	Bucket(){
		next = NULL;
	}
	Bucket(int val, int key){
		value = val;
		this->key = key;
		next = NULL;
	}
	Bucket(int value){
		this->value = value;
		next = NULL;
	}
	Bucket(int val, Bucket bucket){
		Bucket * newBucket = new Bucket(val);
		bucket.next = newBucket;
	}
	void setValues (int value,int key){
		this->value = value;
		this->key = key;
	}
	int getValue(){
		return value;
	} 
	int multipleValues(){
		int values = 0;
		Bucket * temp = this;
	    if(temp->next!=NULL){
			while(temp->next!=NULL){
				values++;
				temp = temp->next;
			}
		} 
		return values;
	}
	int valueAt(int number){
		Bucket * temp = this;
	    if(temp->next!=NULL&& number != 0){
			for(int i=0;i<number;i++)
				temp = temp->next;
			return temp->value;
		} else {
			return temp->value;
		}
	}
	
	void printValue(){
		cout<< value<< " ";
		if(this->next != NULL){
			Bucket * temp = next;
			cout<< temp->value<< " ";
			if(temp->next!=NULL){
				while(temp->next!=NULL){
					cout<< temp->value << " ";
					temp = temp->next;
				}
			}
		}
	}
};

class HashMap{
	public:
	int size;
	Bucket * Hashmap;
	HashMap(int entries){
		size = entries;
		Hashmap = new Bucket[entries];
		for(int i=0;i<size;i++){
			Hashmap[i].setValues(0,0);
		}
	}
	void insert(int value, int key){
		int index = key % size;
		if(Hashmap[index].getValue()!=0){
			Bucket * newBucket = new Bucket(value);
			Hashmap[index].next = newBucket;
		//	Bucket(value,Hashmap[index]);	
		} else {
			Hashmap [index].setValues(value,key);	
		}
	}

	int getValue(int index){
		return Hashmap[index].getValue();
	}
	void print(){
		for(int i=0;i<size;i++)
			Hashmap[i].printValue();
	}
	int multipleValues(int index){
		return Hashmap[index].multipleValues();
	}
	int valueAt(int index,int numbers){
		return Hashmap[index].valueAt(numbers);
	}
	int getKey(int index){
		return Hashmap[index].key;
	}
};

int main() {
	int size;
	cin >> size;
	HashMap nums(size);
	for(int i=0;i<size;i++){
		int next;
		cin>>next;
		if(cin.fail()){
			return -1;
			cin.clear();
			cin.ignore();
			i--;
		} else {
			int key = rand() % 801;
			nums.insert(next,key);
		}
	}
//	nums.print();
	int result = -1;
	int prodsize = size*(size+1)/2;
	int prod[prodsize];
	int prodcount = 0;
	for(int i=0;i<size;i++){
		int val1 = nums.getValue(i);
		int count=0;
		if(val1!=0)
		while (count<=nums.multipleValues(i)){
			for(int j=i;j<size;j++){
				int count2=0;
				int val2;
				do{
					if(nums.multipleValues(j)!=0 && count2<=nums.multipleValues(j))
						val2 = nums.valueAt(j,count2);
					else
						val2 = nums.getValue(j);
					if(val2!=0 && ((nums.getKey(i)!=nums.getKey(j))||((nums.getKey(i)==nums.getKey(j))&& val2 != val1))){
						int temp = val1 * val2;
						prod[prodcount]=temp;
						prodcount++;
					}
				count2++;
			} while (count2<=nums.multipleValues(j));
			}
			count++;
			if(nums.multipleValues(i)!=0 && count<=nums.multipleValues(i)){
				val1 = nums.valueAt(i,count);
			}
		};
	}
	int count = 0;
	for(int i=0;i<prodcount;i++){
		for(int j=0;j<size;j++){
			do{
				int val = 0;
				if(nums.multipleValues(j)!=0 && count<=nums.multipleValues(j))
					val = nums.valueAt(j,count);
				else
					val = nums.getValue(j);
				if(prod[i]==val && prod[i]>result){
					result = prod[i];
				}
				count++;
			} while (count<=nums.multipleValues(j));
			count = 0;
		}
	}
	cout << result; 
	return 0;
}

