#include "hashing/hashing.h"
#include<iostream>

using std::string;


int main(int argc, char *argv[]){
	hashing h;

	h.object = "webb";

	cout<< h.get_hash();
}