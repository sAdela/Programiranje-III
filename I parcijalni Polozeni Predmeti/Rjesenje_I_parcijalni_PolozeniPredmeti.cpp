#include <iostream>
using namespace std;


/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR ĆE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJEČILO GUBLJENJE URAĐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTIČNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUČAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOĆNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
6. ZA POTREBE TESTIRANJA, UNUTAR MAIN FUNKCIJE MOZETE DODAVATI NOVE TESTNE PODATKE
****************************************************************************/
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

char *AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

const char * crt = "\n----------------------------------------------------\n";
class Datum {
	int * _dan, *_mjesec, *_godina;
public:
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	Datum(const Datum &datum) {
		_dan = new int(*datum._dan);
		_mjesec = new int(*datum._mjesec);
		_godina = new int(*datum._godina);
	}

	void operator=(const Datum &datum) {
		*_dan = *datum._dan;
		*_mjesec = *datum._mjesec;
		*_godina = *datum._godina;
	}

	friend ostream & operator<<(ostream & COUT, Datum obj) {
		COUT << *obj._dan << "/" << *obj._mjesec << "/" << *obj._godina << endl;
		return COUT;
	}
};

template<class T, int velicina>
class FITArray {
	T _niz[velicina];
	int _trenutno;
	bool _dozvoliDupliciranje;
public:
	//OSTALE FUNKCIJE CLANICE DEFINISATI VAN TEMPLATE KLASE
	FITArray(bool dozvoliDupliciranje = true) { _dozvoliDupliciranje = dozvoliDupliciranje; _trenutno = 0; }
	int GetTrenutno() const { return _trenutno; }
	T * GetNiz() { return _niz; }
	//T& GetElementNiza(int i) { return _niz[i]; }
	void SetTrenutno() { _trenutno = 0; }

	friend ostream& operator<<(ostream &COUT, FITArray &fitArray) {

		for (int i = 0; i < fitArray.GetTrenutno(); i++) 
			COUT << fitArray.GetNiz()[i] << " ";
		
		return COUT;
	}

	void operator-=(const T& clan) {
		for (int i = 0; i < _trenutno; i++) {
			if (_niz[i] == clan) {
				_niz[i] = _niz[--_trenutno];
				if (_dozvoliDupliciranje == false)
					break;
			}
		}
	}

	int operator()(int OD, int DO) {

		if (OD > _trenutno)
			return -1;
		if (DO > _trenutno)   //od 2 do 7 a imaju 4 elementa [0,1,2,3]
			DO = _trenutno;
		

		for (int i = OD; i < DO; i++)
			cout << _niz[i] << " ";
		return _niz[DO];
	}

	bool operator+=(const T& noviClanNiza) {// T PolozenPredmet

		if (_trenutno == velicina)
			return false;

		if (_dozvoliDupliciranje == false)
			for (int i = 0; i < _trenutno; i++)
				if (_niz[i] == noviClanNiza)
					return false;

		_niz[_trenutno++] = noviClanNiza;
		return true;
	}

};

class PolozeniPredmet {
	char * _naziv;
	int _ocjena;
	Datum _datumPolaganja;
public:


	int GetOcjena()const {
		return _ocjena;
	}

	PolozeniPredmet(const Datum &datum, const char* naziv = nullptr, int ocjena = 0) :_datumPolaganja(datum) {
		_naziv = AlocirajNizKaraktera(naziv);
		_ocjena = ocjena;
	}
	PolozeniPredmet() :_datumPolaganja(0, 0, 0), _ocjena(0), _naziv(nullptr) {}
	~PolozeniPredmet() { delete[] _naziv; _naziv = nullptr; }

	bool operator==(const PolozeniPredmet& predmet) {
		if (strcmp(_naziv, predmet._naziv) != 0)
			return false;
		return true;
	}

	void operator=(const PolozeniPredmet& predmet) {
		delete[]_naziv;
		_naziv = AlocirajNizKaraktera(predmet._naziv);
		_ocjena = predmet._ocjena;
		_datumPolaganja = predmet._datumPolaganja;
	}


	friend ostream & operator<<(ostream & COUT, PolozeniPredmet & obj) {
		COUT << obj._naziv << "(" << obj._ocjena << ")" << obj._datumPolaganja << endl;
		return COUT;
	}
};


class Student {
	static int _indeksCounter; //sluzi za odredjivanje narednog broja indeksa koji ce biti dodijeljen studentu, pocevsi od 160000
	const int _indeks;
	char * _imePrezime;
	FITArray<PolozeniPredmet, 40> _polozeniPredmeti;
public:

	void operator = (Student &student) {
		_polozeniPredmeti.SetTrenutno();
		delete[]_imePrezime; _imePrezime = AlocirajNizKaraktera(student._imePrezime);
		for (int i = 0; i < student._polozeniPredmeti.GetTrenutno(); i++)
			_polozeniPredmeti += student._polozeniPredmeti.GetNiz()[i];
	}

	float GetProsjek() {
		float suma = 0;
		for (int i = 0; i < _polozeniPredmeti.GetTrenutno(); i++) 
			suma += _polozeniPredmeti.GetNiz()[i].GetOcjena();
		
		suma /= _polozeniPredmeti.GetTrenutno();
		return suma;
	}
	void DodajPredmet(const PolozeniPredmet &predmet) {
		if (predmet.GetOcjena() < 6) return;
		_polozeniPredmeti += predmet;
	}

	Student(const char* imePrezime) :_indeks(_indeksCounter++)
	{
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	~Student() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, Student & obj) {
		COUT << obj._indeks << " " << obj._imePrezime << " " << obj._polozeniPredmeti << " ";
		return COUT;
	}
};

int Student::_indeksCounter = 160000;

void main() {
	const int max = 20;

	Datum jucer(20, 11, 2017), danas(21, 11, 2017), sutra(22, 11, 2017);
	cout << jucer << danas << sutra << endl;
	jucer = danas;
	cout << jucer << danas << sutra << endl;

	//parametar tipa bool odredjuje da li je u nizu dozvoljeno dupliciranje elemenata
	FITArray<int, max> nizIntegera(false);

	for (size_t i = 0; i < max - 1; i++)
		nizIntegera += i;//dodaje novog clana niza

	if (!(nizIntegera += 6))//pokusavamo dodati dupli clan niza
		cout << "Element nije dodan u niz" << endl;

	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza

	nizIntegera -= 9; //uklanja clan niza sa vrijednoscu 9
	nizIntegera -= 17;
	cout << crt << nizIntegera << crt; //ispisuje sve clanove niza


	FITArray<int, max> noviNizIntegera(nizIntegera); //posto nema pokazivaca, ne treba praviti konstruktor kopije, inace mora

	cout << crt << noviNizIntegera << crt;

	/*parametri odredjuju lokacije (indekse u nizu) elemenata OD - DO koje je potrebno vratiti.
	u slucaju da u nizu ne postoji trazeni broj elemenata funkcija treba da vrati sve element od
	lokacije OD pa do posljednje dostupnog elementa */
	cout << "Clanovi niza od lokacije 2 do lokacije 5 su -> " << noviNizIntegera(2, 5) << crt;

	Student adel("Adel Handzic"), jasmin("Jasmin Azemovic");

	PolozeniPredmet prII(jucer, "PRII", 8), prIII(sutra, "PRIII", 7), PRI(jucer, "PRI", 10);

	adel.DodajPredmet(prII);
	adel.DodajPredmet(prIII);
	cout << adel << endl;
	//vraca prosjecnu ocjenu studenta
	cout << "Prosjecna ocjena -> " << adel.GetProsjek() << crt;
	jasmin.DodajPredmet(PRI);
	jasmin = adel;
	cout << jasmin << endl;
	cout << "Prosjecna ocjena -> " << jasmin.GetProsjek() << crt;
	system("Pause>0");
}

