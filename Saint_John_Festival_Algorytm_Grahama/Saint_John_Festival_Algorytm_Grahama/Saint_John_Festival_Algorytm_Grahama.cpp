//Saint John Festival - Algorytm Grahama - Kinga Wieloch
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define M_PI 3.14159265358979323846

class LampionGraham
{
	vector < pair <int, int> > duzeLampiony;
	vector < pair <int, int> > maleLampiony;

	void wpiszDane()
	{
		int iloscDuzychLampionow;
		int iloscMalychLampionow;

		for (;;) {
			cin >> iloscDuzychLampionow;

			if (iloscDuzychLampionow < 3 || iloscDuzychLampionow > 10000) {
				cout << "Nieprawidlowa ilosc duzych lampionow" << endl;
				continue;
			}

			break;
		}

		int x1, y1;
		int x2, y2;

		for (int i = 0; i < iloscDuzychLampionow; i++) {
			cin >> x1;
			cin >> y1;

			if (x1 < 0 || y1 < 0) {
				cout << "Niepoprawne koordynaty punktu" << endl;
				continue;
			}

			duzeLampiony.push_back({ x1, y1 });
		}

		for (;;) {
			cin >> iloscMalychLampionow;

			if (iloscMalychLampionow < 1 || iloscMalychLampionow > 50000) {
				cout << "Nieprawidlowa ilosc malych lampionow" << endl;
				continue;
			}

			break;
		}

		for (int i = 0; i < iloscMalychLampionow; i++) {
			cin >> x2;
			cin >> y2;

			if (x2 < 0 || y2 < 0) {
				cout << "Niepoprawne koordynaty punktu" << endl;
				continue;
			}

			maleLampiony.push_back({ x2, y2 });
		}
	}

	pair <int, int> szukajNajnizszego()
	{
		int x = duzeLampiony[0].first;
		int y = duzeLampiony[0].second;

		for (unsigned int i = 1; i < duzeLampiony.size(); i++)
		{
			if (duzeLampiony[i].second < y) {
				x = duzeLampiony[i].first;
				y = duzeLampiony[i].second;
			}
		}

		return { x,y };
	}

	void zmienPolozeniePunktow()
	{
		pair <int, int> p = this->szukajNajnizszego();

		for (auto& it : duzeLampiony) {
			it.first -= p.first;
			it.second -= p.second;
		}

		for (auto& it : maleLampiony) {
			it.first -= p.first;
			it.second -= p.second;
		}
	}

	void sortujDuzeLampiony()
	{
		sort(
			duzeLampiony.begin(),
			duzeLampiony.end(),
			[](pair <int, int>& a, pair <int, int>& b) {

				if (a.first == 0 && a.second == 0) {
					return true;
				}

				if ((a.first * b.second - b.first * a.second) == (b.first * a.second - a.first * b.second)) {
					long double z1 = sqrt(pow(a.first, 2) + pow(a.second, 2));
					long double z2 = sqrt(pow(b.first, 2) + pow(b.second, 2));

					return z1 < z2;
				}

				long double at1 = atan2(a.second, a.first) * 180 / M_PI;
				long double at2 = atan2(b.second, b.first) * 180 / M_PI;

				return (at1 - at2) < 0;
			}
		);
	}


	void znajdzOtoczke() {
		pair<int, int> ac;
		pair<int, int> ab;
		long long mn;
		size_t i = 0;

		while (i < duzeLampiony.size() - 3) {
			ac = { ((duzeLampiony[i + 3].first) - (duzeLampiony[i + 1].first)), ((duzeLampiony[i + 3].second) - (duzeLampiony[i + 1].second)) };
			ab = { ((duzeLampiony[i + 2].first) - (duzeLampiony[i + 1].first)), ((duzeLampiony[i + 2].second) - (duzeLampiony[i + 1].second)) };
			mn = ((((long long)ac.first) * ((long long)ab.second)) - (((long long)ab.first) * ((long long)ac.second)));

			if (mn >= 0) {
				duzeLampiony.erase(duzeLampiony.begin() + (i + 2));

				if (i != 0) {
					i--;
					continue;
				}
			}

			else i++;
		}
	}

	void znajdzMaleLampiony() {
		pair<int, int> a;
		pair<int, int> b;
		long long mn;
		size_t rozmiar = duzeLampiony.size();

		for (size_t i = 0; i < duzeLampiony.size(); i++) {
			for (size_t j = 0; j < maleLampiony.size(); j++) {
				a = { duzeLampiony[(i + 1) % rozmiar].first - duzeLampiony[i].first, duzeLampiony[(i + 1) % rozmiar].second - duzeLampiony[i].second };
				b = { maleLampiony[j].first - duzeLampiony[i].first, maleLampiony[j].second - duzeLampiony[i].second };
				mn = ((((long long)a.first) * ((long long)b.second)) - (((long long)b.first) * ((long long)a.second)));

				if (mn < 0) {
					maleLampiony.erase(maleLampiony.begin() + j);

					if (j != 0) {
						j--;
						continue;
					}
				}
			}
		}
	}

public:

	LampionGraham() {}

	void znajdzIloscMalychLampionowWewnatrz()
	{
		this->wpiszDane();
		this->zmienPolozeniePunktow();
		this->sortujDuzeLampiony();
		this->znajdzOtoczke();
		this->znajdzMaleLampiony();

		cout << maleLampiony.size() << endl;
	}
};

int main()
{
	LampionGraham* lampion = new LampionGraham();
	lampion->znajdzIloscMalychLampionowWewnatrz();

	delete(lampion);
	return 0;
}
