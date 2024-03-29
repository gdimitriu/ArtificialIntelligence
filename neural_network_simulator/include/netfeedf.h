/*
 * netfeedf.h
 * retele feedforward total conectate
 *  Created on: Apr 4, 2022
 *      Author: Gabriel Dimitriu
 *  @Copyright
 *  Code for net taken from SNNS described in
 *  Retele neuronale artficiale by Gavril Toderean, Mircea Costeiu, Mircea Giurgiu
 *  Editura Albastra, Cluj-Napoca 1995
 */

#ifndef NETFEEDF_H_
#define NETFEEDF_H_

#include "matrixf.h"
#include <string.h>

enum ON_OFF {
	ON,
	OFF
};

class net_feedf {
public:
	net_feedf();
	net_feedf(int,int,int,int,int);
	virtual ~net_feedf();
	void set_temp(float);
	//functie friend care afiseaza informatii despre o retea
	void friend info_net(int,int,net_feedf&);
	//functii comune
	//returneaza si seteaza tipul retelei
	char type() {
		return typenet;
	}
	void set_type(char c) {
		typenet = c;
	}
	//functii care seteaza, returneaza semafoare
	ON_OFF tr_before() {
		return (nr_it_used != 0) ? ON : OFF;
	}
	ON_OFF is_created() {
		return CREATE;
	}
	ON_OFF trained() {
		return TRAINED;
	}
	void set_create() {
		CREATE = ON;
	}
	void del_crea() {
		CREATE = OFF;
	}
	void del_trained() {
		TRAINED = OFF;
	}
	void set_trained() {
		TRAINED = ON;
	}
	void set_nr_it(int value) {
		nr_it = value;
	}
	//returneaza numarul de epoci de antrenament
	int get_nr_it() {
		return nr_it;
	}
	//returneaza procentajul de test
	int* get_tab_test() {
		return tab_test;
	}
	//functii de lucru cu nume si fisiere
	char *namenet() {
		return name;
	}
	void put_name(char *s) {
		strcpy(name,s);
	}
	void load_trainning_text_File(char *path);
	void load_trainning_suite_text_file(char *path);
	void del_trainning_suite();
	void load_test_suite_text_file(char *path);
	void del_test_suite();
	int get_nr_in_test_suite() {
		return nr_in_suite_test;
	}
	int get_nr_in_trainning_suite() {
		return nr_in_suite_trainning;
	}
	//initializeaza vectorul valori de iesire
	matrixf& get_outputs();
	//introduce zgomot
	void inp_noise();
	//initializeaza ponderile cu valori aleatoare din intervalul [-0.2,+0.2]
	virtual void initweights(float offset, float multiplicator);
	//returneaza nodul de iesire cu valoarea cea mai mare
	int max();
	//utilizeaza reteaua dupa ce a fost antrenata
	void test();
	//antreneeaza reteaua
	void train();
	//update the eta if is necessary
	virtual void updateEta();
	//pune valorile tabloului de test completat in cadrul sesiunii de antrenament
	//intr-un tablou global in care se pot memora max 5 retele
	void put_perf();
	//functia de activare a neuronilor
	virtual float to(float,float);
	//preia datele de initializare
	virtual int create();
	//initializeaza inputul cu valori 0 si 1
	virtual void init_inp(matrix&);
	virtual void init_inp(matrixf&);
	matrixf& get_inp();
	matrixf& get_trainning_inp(int index);
	matrixf& get_test_inp(int index);
	matrixf& get_tp();
	matrixf& get_trainning_tp(int index);
	matrixf& get_test_tp(int index);
	//se apeleaza daca create() sa executat cu success si aloca toate matricele de valori float
	//se mai apeleaza si dupa preluarea informatiilor despre o retea dintr-un fisier
	virtual void init_net();
	//dealoca matricele de valori
	virtual void free_net();
	//pentru transmiterea fluxului de intrare catre iesire
	virtual void forward();
	//pentru ajustarea ponderilor
	virtual void backward();
	//se salveaza fisierul
	virtual int save(const char*);
	//se reface din fisier
	virtual int load_inf(const char*);
	void setEta(float value) {
		eta = value;
	}
	void setMomentum(float value) {
		mom = value;
	}
	void setDesiredMse(float value) {
		DesiredMse = value;
	}
protected:
	int nr_in_suite_trainning;
	matrixf *trainning_inp;
	matrixf *trainning_tp;
	int nr_in_suite_test;
	matrixf *test_inp;
	matrixf *test_tp;
	virtual void saveInternal_inf(int dFile);
	virtual void loadInternal_inf(int dFile);
	//caracter pentru tipul de retea feedforward necesar pentru citire de pe disk
	// % = total connectata
	// ? = local connectata
	// # = cu extractori ierarhici de trasaturi
	// * = cu extractori ierarhici de trasaturi si partajarea deplasarilor
	char typenet;
	//semafor pentru a semnala daca reteaua a fost creata sau nu
	ON_OFF CREATE;
	//semafor pentru a semnala daca reteaua a fost antrenata sau nu
	ON_OFF TRAINED;
	//semafor pentru a semnala daca reteaua a fost loaded sau nu
	ON_OFF LOADED;
	//sir de caractere pentru numele retelei
	char name[10];
	//constanta de invatare
	float eta;
	//constanta functiei de activare a neuronilor
	float temp;
	//valoare pentru momentum
	float mom;
	//numarul epocilor de antrenament
	int nr_it;
	//numarul de epoci deja parcurse in procesul de antrenament
	int nr_it_used;
	//TABLOUL VALORILOR DE TEST
	//la fiecare nr_test_epoci se completeaza o val intre 0 si 100 care e procentajul
	int *tab_test;
	//numarul de niveluri ascunse ale retelei
	int nr_hidd;
	//numarul de noduri din nivelele retelei
	//L = niveluri de intrare
	int L;
	//N = niveluri de iesire
	int N;
	//M0 = primul nivel ascuns
	int M0;
	//M1 = al doilea nivel ascuns
	int M1;
	//matricea care pastreaza valorile nodurile de intrare
	matrixf inp;
	//vectorul pentru memorarea valorilor obtinute la nodurile de la iesire
	matrixf out;
	//vectorul pentru memorarea valorilor dorite la iesire pentru antrenament
	matrixf tp;
	//valorile nodurilor primului nivel ascuns
	matrixf hid0;
	//valorile nodurilor din al doilea nivel ascuns
	matrixf hid1;
	//ponderile intre nivelul de intrare si primul nivel ascuns impreuna cu valorile delata
	matrixf whin,dwhin;
	//deplasarile de scala pentru nodurile din primul nivel ascuns plus delta
	matrixf bhin,dbhin;
	//ponderile intre primul nivel si del de-al doilea nivel ascunsuns impreuna cu delta
	matrixf wh10,dwh10;
	//deplasarile de scala pentru nodurile din al doilea nivel ascuns plus delta
	matrixf bh10,dbh10;
	//ponderile intre nivelul de iesire si cel anterior lui
	matrixf wohi,dwohi;
	//deplasrile de scala pentru nodurile din nivelul de iesire plus delta
	matrixf bohi,dbohi;

	//datele folosite pentru rata de invatare variabila
	//semafor pentru indentificare rata de invatare
	int EtaVar;
	//ultimul indice pentru rata de invatare ETA
	int LastIndEta;
	float DesiredMse;
	//ultima valoare a erorii patratice medii
	float LastMse;
	//ultima valoare pentru entropie
	float LastS;
};

#endif /* NETFEEDF_H_ */
