#include<iostream>
using namespace std;

char *AlocirajNizKaraktera(const char* sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char *temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

class Vrijeme {
	int *_sati;
	int *_minuti;
	int *_sekunde;
public:
	//Za vrijeme:
	//Konstruktor bez parametara
	//Konstruktor sa 3 parametra (sati, minute i sekunde)
	//Konstruktor sa 2 parametra (sati i minute)
	Vrijeme() {
		_sati = new int(0);
		_minuti = new int(0);
		_sekunde = new int(0);
	}
	Vrijeme(int sati, int minute, int sekunde = 0) {
		_sati = new int(sati);
		_minuti = new int(minute);
		_sekunde = new int(sekunde);
	}
	~Vrijeme(){
		delete _sati; _sati = nullptr;
		delete _minuti; _minuti = nullptr;
		delete _sekunde; _sekunde = nullptr;
	}
	void Info(bool flag = false) {
		//Funkciju Info sa neobaveznim parametrom tipa bool koji određuje da li će vrijeme biti ispisano u punom formatu
		//(hh:mm:ss) ili u skraćenom formatu (hh:mm). Default-no funkcija vrši ispis u punom formatu.
		cout << *_sati << ":" << *_minuti;
		if (flag)
			cout << ":" << *_sekunde << endl;
		cout << endl;
	}
	int PretvoriUMinute() {
		return *_sati * 60 + *_minuti;
	}
	Vrijeme(const Vrijeme& vrijeme) {
		_sati = new int(*vrijeme._sati);
		_minuti = new int(*vrijeme._minuti);
		_sekunde = new int(*vrijeme._sekunde);
	}
	Vrijeme Add(Vrijeme& vrijeme) {
		//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
		//sumu vremena proslijeđenog kao parametar i instance this.
		int Dodano  = vrijeme.PretvoriUMinute() + *_sati * 60 + *_minuti;
		int noviSati = Dodano / 60;
		int noveMinute = Dodano - noviSati * 60;

		return Vrijeme(noviSati, noveMinute, *_sekunde);
	}
	Vrijeme Add(int min) {
		//Funkciju Add koja kao rezultat vraća novi objekat tipa vrijeme koji predstavlja 
		//sumu parametra izraženog u minutama i vremena instance this.
		int Dodano = *_sati * 60 + *_minuti + min;
		int noviSati = Dodano / 60;
		int noveMinute = Dodano - noviSati * 60;

		return Vrijeme (noviSati, noveMinute, *_sekunde);
	}
	int CompareTo(Vrijeme& vrijeme) {
		//Funkciju CompareTo koja vraća vrijednost tipa int u zavisnosti od toga da li
		//je vrijeme instance this prije, jednako ili poslije
		//vremena proslijeđenog kao parametar.
		//Moguće povratne vrijednosti:
		//-1 - vrijeme instance this nastupa prije vremena v2
		// 0 - vrijeme instance this je jednako vremenu v2
		// 1 - vrijeme instance this nastupa nakon vremena v2
		int temp = *_sati * 60 + *_minuti;
		if (temp < vrijeme.PretvoriUMinute())
			return -1;
		else if (temp == vrijeme.PretvoriUMinute())
			return 0;
		return -1;
	}
	void operator=(const Vrijeme& vrijeme) {
		*_sati = *vrijeme._sati;
		*_minuti = *vrijeme._minuti;
		*_sekunde = *vrijeme._sekunde;
	}
};

// -----------------------------------------------------------------------------

/*
Potrebno je kreirati aplikaciju za dijeljenje znanja putem razmjene
članaka među korisnicima.

Izdvojene su sljedeće funkcionalnosti:
- Administrator sistema je zadužen za upravljanje korisničkim nalozima
(Ime, Prezime, Email, DatumRegistracije, KorisnickoIme, Lozinka).
- Svaki članak (Naslov, Sadrzaj, Datum, Satnica, BrojPregleda)
može sadržavati više tagova, ali pripada samo jednoj oblasti.
- Članke mogu dodavati svi registrovani korisnici.
- Korisnici aplikacije također mogu ostaviti komentar
(Tekst, Datum, Popularnost) na određeni članak.
*/

/*
Na osnovu datih klasa implementirati opisane funkcionalnosti sistema.
Po potrebi dopuniti klase novim atributima i/ili funkcijama.
*/

class Datum
{
	int _dan;
	int _mjesec;
	int _godina;
public:
	//Potrebne konstruktor i destruktor funkcije
	Datum(int dan = 0, int mjesec = 0, int godina = 0) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}
	//Funkciju Info
	void Info() {
		cout << _dan << "." << _mjesec << "." << _godina<<" ";
	}
};

enum TipKorisnika { Administrator, Guest };
const char* TipKorisnikaChar[2] = { "Administrator", "Guest" };
class Korisnik
{
	char _ime[30];
	char _korisnickoIme[20];
	char* _lozinka;
	TipKorisnika _tipKorisnika; //Administrator, Guest
public:
	//Potrebne konstruktor i destruktor funkcije
	Korisnik() {
		_lozinka = nullptr;
	}
	Korisnik(const char* ime, const char* korisnickoIme, const char* lozinka, TipKorisnika tip) {
		strcpy_s(_ime, ime);
		strcpy_s(_korisnickoIme, korisnickoIme);
		_lozinka = AlocirajNizKaraktera(lozinka);
		_tipKorisnika = tip;
	}
	Korisnik(const Korisnik& korisnik) {
		strcpy_s(_ime, korisnik._ime);
		strcpy_s(_korisnickoIme, korisnik._korisnickoIme);
		_lozinka = AlocirajNizKaraktera(korisnik._lozinka);
		_tipKorisnika = korisnik._tipKorisnika;
	}
	void Kopiraj(const Korisnik& korisnik) {
		//implementiran je i operator =, tako da se ne mora ova funkcija koristiti
		strcpy_s(_ime, korisnik._ime);
		strcpy_s(_korisnickoIme, korisnik._korisnickoIme);
		if (_lozinka != nullptr)
			delete[] _lozinka;
		_lozinka = AlocirajNizKaraktera(korisnik._lozinka);
		_tipKorisnika = korisnik._tipKorisnika;
	}
	void operator=(const Korisnik& korisnik) {
		strcpy_s(_ime, korisnik._ime);
		strcpy_s(_korisnickoIme, korisnik._korisnickoIme);
		if (_lozinka != nullptr)
			delete[] _lozinka;
		_lozinka = AlocirajNizKaraktera(korisnik._lozinka);
		_tipKorisnika = korisnik._tipKorisnika;
	}
	//Funkciju za promjenu korisničke lozinke
	void PromjeniSifru(const char* sifra) {

		if (_lozinka != nullptr)
			delete[] _lozinka;
		_lozinka = AlocirajNizKaraktera(sifra);

	}
	~Korisnik() {
		delete[] _lozinka;_lozinka = nullptr;
	}
	//Funkciju Info
	void Info() {
		cout << "Ime: " << _ime << endl;
		cout << "Korisnicko ime " << _korisnickoIme << endl;
		cout << "Lozinka " << _lozinka << endl;
		cout << TipKorisnikaChar[_tipKorisnika] << endl;
		cout << endl << endl;
	}
	const char *getIme() const{
		return _ime;
	}
};

class Komentar
{
	char* _tekst;
	Datum _datum;
	Vrijeme _satnica;
	int _popularnost;
	Korisnik* _autor;
public:
	//Potrebne konstruktor i destruktor funkcije
	void operator=(const Komentar& komentar) {
		if (_tekst != nullptr)
			delete[] _tekst;
		_tekst = AlocirajNizKaraktera(komentar._tekst);
		_datum = komentar._datum;
		_satnica = komentar._satnica;
		_popularnost = komentar._popularnost;
		if (_autor != nullptr)
			delete _autor;
		_autor = new Korisnik(*komentar._autor);
	}
	Komentar() {
		_tekst = nullptr;
		_popularnost = 0;
		_autor = nullptr;
	}
	Komentar(const char* tekst, const Datum& datum, const Vrijeme& vrijeme, int popularnost, const Korisnik& korisnik) {
		_tekst = AlocirajNizKaraktera(tekst);
		_datum = datum;
		_satnica = vrijeme;
		_popularnost = popularnost;
		_autor = new Korisnik(korisnik);
	}
	~Komentar() {
		delete[] _tekst; _tekst = nullptr;
		delete _autor; _autor = nullptr;

	}
	//Funkciju za izmjenu popularnosti komentara
	void IzmjeniPopularnost(int popularnost) {
		_popularnost = popularnost;
	}
	//Funkciju Info
	void Info() {
		cout << "Tekst komentara\n" << _tekst << endl;
		_datum.Info();
		_satnica.Info();
		cout << "Popularnost: " << _popularnost << endl;
		_autor->Info();
	}
};

class Clanak
{
	char _naslov[150];
	char* _sadrzaj;
	Datum _datum;
	Vrijeme _satnica;
	int _brojPregleda;
	char* _tagovi[10];
	char _oblast[100];
	Korisnik* _autor;
	Komentar* _komentari;
	int _brojKomentara;
public:
	Clanak(const char* naslov, const char* sadrzaj, const Datum& datum, const Vrijeme& vrijeme, const char* oblast, const Korisnik& korisnik) {
		strcpy_s(_naslov, naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
		_datum = datum;
		_satnica = vrijeme;
		strcpy_s(_oblast, oblast);
		_autor = new Korisnik(korisnik);
		_komentari = nullptr;
		_brojKomentara = 0;
		_brojPregleda = 0;
		for (int i = 0; i < 10; i++)
			_tagovi[i] = nullptr;
	}
	//Funkciju za dodavanje tagova za članak
	void setTag(const char* tag, int i) {
		int vel = strlen(tag) + 1;
		if (_tagovi[i] != nullptr)
			delete[] _tagovi[i];
		_tagovi[i] = new char[vel];
		strcpy_s(_tagovi[i], vel, tag);
	}
	void DodajTag(const char* tag) {
		for (int i = 0; i < 10; i++) {
			if (_tagovi[i] == nullptr) {
				setTag(tag, i);
				return;
			}
		}
		cout << "Maksimalan broj tagova je vec dodan!" << endl;
	}

	/*Funkciju za promjenu sadržaja i vremena promjene članka. Kao verifikaciju dozvole potrebno je proslijediti korisničko ime autora članka.
	Samo kreator članka ima permisije da mijenja njegov sadržaj.
	*/
	void SetSadrzajIVrijeme(const char*sadrzaj, const Vrijeme& vrijeme, const char* imeAutora) {
		if (strcmp(_autor->getIme(), imeAutora) != 0)
			return;
		if (_sadrzaj != nullptr)
			delete[] _sadrzaj;
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
		_satnica = vrijeme;
	}
	//Funkciju za dodavanje komentara

	void DodajKomentar(const Komentar& komentar) {

		Komentar *temp = new Komentar[_brojKomentara + 1];
		for (int i = 0; i < _brojKomentara; i++) {
			temp[i] = _komentari[i];
		}
		delete[] _komentari;
		temp[_brojKomentara] = komentar;
		_brojKomentara++;
		_komentari = temp;
		_brojPregleda++;
	}

	//Funkciju Info
	void Info() {
		cout << "CITATE CLANAK: " << endl;
		_datum.Info();
		_satnica.Info();
		for (int i = 0; i < 10; i++) {
			if (_tagovi[i] != nullptr) {
				cout << "#" << _tagovi[i] << " ";
			}
		}
		cout << endl << "Oblast: " << _oblast << endl;
		cout << endl << _naslov << endl << _sadrzaj << endl;
		cout << "Napisao/la: " << endl;
		_autor->Info();
		cout << "Broj pregleda: " << _brojPregleda << endl;
		for (int i = 0; i < _brojKomentara; i++) 
			_komentari[i].Info();

	}

};

void main()
{
	//Kreirati testni program koji demonstrira implementirane funckionalnosti
	Datum datum(20,2,2022);
	Vrijeme neko, neko1(22, 15, 47), neko2(01, 20);
	neko1.Info(true);
	neko2.Info();
	cout << endl;
	neko1.Add(neko2).Info(true);
	neko2.Add(10).Info(true);
	Korisnik korisnik("Adela", "WOLF1234", "WorstPasswordEver0101", Guest), korisnik1("neko", "neko","neko123", Guest);
	korisnik.Info();
	korisnik.PromjeniSifru("EvenWorse$!=%789");
	korisnik.Info();
	cout << endl << endl;
	korisnik1.Info();
	//korisnik1.Kopiraj(korisnik);
	korisnik1 = korisnik;
	korisnik1.Info();
	Komentar komentar("ma pusti Miljacku nek tiho tece", datum, neko1, 200, korisnik);
	komentar.Info();
	komentar.IzmjeniPopularnost(201);
	komentar.Info();
	Clanak clanak("BiH je svjetski prvak!", "Bosna i Hercegovina je postala svjetski prvak u broju zaposlenih u javnoj upravi.", datum, neko1, "Priznanja i nagrade", korisnik);
	clanak.DodajTag("sarkazam");
	clanak.DodajTag("BiH");
	clanak.DodajTag("nepotizam");
	clanak.Info();
	clanak.SetSadrzajIVrijeme("BiH je najatraktivnija turisticka drzava.", neko2, "Adela"); 
	clanak.Info();
	clanak.SetSadrzajIVrijeme("! ! ! ! ! ! ! HACKED ! ! ! ! ! !", neko2, "MrX");
	clanak.Info();
	Komentar komentar1("Jos kada bi to znali cijeniti, gdje bi nam bio kraj!!!!", datum, neko1, 101, korisnik1);
	clanak.DodajKomentar(komentar);
	clanak.DodajKomentar(komentar1);
	clanak.Info();
	system("Pause>0");
}